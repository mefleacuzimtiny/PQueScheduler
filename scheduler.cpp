#include "scheduler.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Scheduler::Scheduler(int levels, int queSize)
    : processQueue(levels, queSize)
    , totalProcesses(0)
    , currentTime(0) {
}

void Scheduler::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Failed to open file: " << filename << std::endl;
        exit(1);
    }

    std::string header;
    std::getline(file, header); // skip CSV header

    Process prc;
    while (file >> prc) {
        enQueProcess(prc);
        std::cout << "Loaded: " << prc << std::endl;
        totalProcesses++;
    }

    file.close();
}

// void Scheduler::run() {

// }



void Scheduler::enQueProcess(Process prc) {
    // insert arriving task into task_que at the process's priority level
    processQueue.Insert(prc, prc.getPrtLvl());
}


void Scheduler::execute(Process &prc) {
    prc.execQuantums(1);
}

void Scheduler::run() {
    currentTime = 0;
    completed.clear();

    Process prc;

    while (!processQueue.IsEmpty()) {
        // remove the highest priority process
        processQueue.Remove(prc);

        // calculate start time
        int startTime = std::max(currentTime, prc.getTimeArrival());

        // For our current Process class, we don’t have a member to store startTime
        // We'll assume we calculate it on the fly in timeStart() using AT + WT
        int waitingTime = startTime - prc.getTimeArrival();

        currentTime = startTime + prc.getTimeExecution(); // finish time

        // push process into completed
        completed.push_back(prc);
    }
}

// Print results & averages
void Scheduler::printResults() const {
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    std::cout << std::setw(5) << "Process ID"
              << std::setw(20) << "Arrival Time"
              << std::setw(20) << "Burst Time"
              << std::setw(20) << "Priority Level"
              << std::setw(20) << "Start Time"
              << std::setw(20) << "Completion Time"
              << std::setw(20) << "Waiting Time"
              << std::setw(20) << "Turnaround Time"
              << "\n";

    for (const Process& process : completed) {
        int startTime = process.timeStart();
        int completionTime = process.timeFinish();
        int waitingTime = process.timeWaiting();
        int turnaroundTime = process.timeTurnaround();

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;

        std::cout << std::setw(5) << "P" + std::to_string(process.getPID())
                  << std::setw(20) << process.getTimeArrival()
                  << std::setw(20) << process.getTimeExecution()
                  << std::setw(20) << process.getPrtLvl()
                  << std::setw(20) << startTime
                  << std::setw(20) << completionTime
                  << std::setw(20) << waitingTime
                  << std::setw(20) << turnaroundTime
                  << "\n";
    }

    if (!completed.empty()) {
        std::cout << "\nAverage Waiting Time: " << (totalWaitingTime / completed.size()) << "\n";
        std::cout << "Average Turnaround Time: " << (totalTurnaroundTime / completed.size()) << "\n";
    }
}
