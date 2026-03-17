
#include "scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Scheduler::addGanttEntry(int start, int end, const std::string &pid) {
    if (ganttCount == ganttCapacity) {
        int newCap = ganttCapacity * 2;
        GanttEntry* newArr = new GanttEntry[newCap];
        for (int i = 0; i < ganttCount; i++) newArr[i] = gantt[i];
        delete[] gantt;
        gantt = newArr;
        ganttCapacity = newCap;
    }
    gantt[ganttCount++] = {start, end, pid};
}

Scheduler::Scheduler(int lvl, int n) : levels(lvl), maxProcesses(n), readyQueue(lvl) {
    // honestly, I'm too lazy to think of anything else so I'm just mimicking vector behavior by doubling the size
    loadedProcesses = new Process[n];
    ganttCapacity = n * 2;
    gantt = new GanttEntry[ganttCapacity];
    ganttCount = 0;
}

Scheduler::~Scheduler() {
    delete[] loadedProcesses;
    delete[] gantt;
}

void Scheduler::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line);

    int idx = 0;
    while (std::getline(file, line) && idx < maxProcesses) {
        std::stringstream ss(line);
        std::string pid, ta, te, prt;

        std::getline(ss, pid, ',');
        std::getline(ss, ta, ',');
        std::getline(ss, te, ',');
        std::getline(ss, prt, ',');

        loadedProcesses[idx].pid = pid;
        loadedProcesses[idx].timeArrival = std::stoi(ta);
        loadedProcesses[idx].timeExecution = std::stoi(te);
        loadedProcesses[idx].timeRemaining = std::stoi(te);
        loadedProcesses[idx].prtLvl = std::stoi(prt);
        idx++;
    }
    file.close();
}

void Scheduler::run() {
    int currentTime = 0;
    int completed = 0;
    int nextArrivalIdx = 0;
    Process* currentRunning = nullptr;
    std::string ganttPid = "IDLE";
    int ganttStart = 0;

    while (completed < maxProcesses) {
        while (nextArrivalIdx < maxProcesses && loadedProcesses[nextArrivalIdx].timeArrival == currentTime) {
            readyQueue.push(loadedProcesses[nextArrivalIdx].prtLvl, loadedProcesses[nextArrivalIdx]);
            nextArrivalIdx++;
        }

        if (currentRunning != nullptr) {
            if (readyQueue.hasHigher(currentRunning->prtLvl)) {
                readyQueue.push(currentRunning->prtLvl, *currentRunning);
                delete currentRunning;
                currentRunning = nullptr;
            }
        }

        if (currentRunning == nullptr && !readyQueue.empty()) {
            currentRunning = new Process(readyQueue.popHighest());
        }

        std::string activePid = (currentRunning != nullptr) ? currentRunning->pid : "IDLE";
        if (activePid != ganttPid) {
            if (currentTime > ganttStart) {
                addGanttEntry(ganttStart, currentTime, ganttPid);
            }
            ganttStart = currentTime;
            ganttPid = activePid;
        }

        if (currentRunning != nullptr) {
            currentRunning->timeRemaining--;

            if (currentRunning->timeRemaining == 0) {
                completed++;
                int finish = currentTime + 1; // Calculate finish time

                for (int i = 0; i < maxProcesses; i++) {
                    if (loadedProcesses[i].pid == currentRunning->pid) {
                        loadedProcesses[i].finishTime = finish;
                        loadedProcesses[i].turnaroundTime = finish - loadedProcesses[i].timeArrival;
                        loadedProcesses[i].waitingTime = loadedProcesses[i].turnaroundTime - loadedProcesses[i].timeExecution;
                        break;
                    }
                }

                delete currentRunning;
                currentRunning = nullptr;
            }
        }
        currentTime++;
    }

    if (currentTime > ganttStart) {
        addGanttEntry(ganttStart, currentTime, ganttPid);
    }
}

void Scheduler::genGantt() {
    std::cout << "\n--- Gantt Chart ---\n";
    for (int i = 0; i < ganttCount; i++) {
        std::cout << gantt[i].start << " - " << gantt[i].end << " : " << gantt[i].pid << "\n";
    }
}

void Scheduler::printTable() {
    std::cout << "\n--- Process Details ---\n";
    std::cout << "PID\tArrival\tBurst\tPriority\tFinish\tWaiting\tTurnaround\n";
    std::cout << "-------------------------------------------------------------------\n";
    for (int i = 0; i < maxProcesses; i++) {
        Process& p = loadedProcesses[i];
        std::cout << p.pid << "\t"
                  << p.timeArrival << "\t"
                  << p.timeExecution << "\t"
                  << p.prtLvl << "\t\t"
                  << p.finishTime << "\t"
                  << p.waitingTime << "\t"
                  << p.turnaroundTime << "\n";
    }
}

void Scheduler::printSummary() {
    long long totalWait = 0;
    long long totalTurn = 0;

    for (int i = 0; i < maxProcesses; i++) {
        totalTurn += loadedProcesses[i].turnaroundTime;
        totalWait += loadedProcesses[i].waitingTime;
    }

    std::cout << "\n--- Execution Summary ---\n";
    std::cout << "Average Turnaround Time: " << (double)totalTurn / maxProcesses << "\n";
    std::cout << "Average Waiting Time:    " << (double)totalWait / maxProcesses << "\n";
    std::cout << "-------------------------\n";
}

void Scheduler::printResults() {
    run();
    genGantt();
    printTable();   // Added to output flow
    printSummary();
}
