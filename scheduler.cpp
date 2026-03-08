#include "scheduler.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Scheduler::Scheduler(int levels, int queSize) {}


void Scheduler::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string header;
    std::getline(file, header); // skip CSV header

    Process prc;

    while (file >> prc) {
        enQueProcess(prc);
        totalProcesses++;
    }

    file.close();
}

// Enqueue a process into the priority queue
void Scheduler::enQueProcess(Process prc) {
    // insert into task_que at the process's priority level
    task_que.Insert(prc, prc.getPrtLvl());
}

// Run the simulation
void Scheduler::run() {
    currentTime = 0;
    completed.clear();

    Process prc;

    while (!task_que.IsEmpty()) {
        // remove the highest priority process
        task_que.Remove(prc);

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
    double totalWT = 0;
    double totalTAT = 0;

    std::cout << std::setw(5) << "PID"
              << std::setw(10) << "AT"
              << std::setw(10) << "BT"
              << std::setw(10) << "PRT"
              << std::setw(10) << "ST"
              << std::setw(10) << "CT"
              << std::setw(10) << "WT"
              << std::setw(10) << "TAT"
              << "\n";

    for (const auto& prc : completed) {
        int st = prc.timeStart();
        int ct = prc.timeFinish();
        int wt = prc.timeWaiting();
        int tat = prc.timeTurnaround();

        totalWT += wt;
        totalTAT += tat;

        std::cout << std::setw(5) << "P" + std::to_string(prc.getPID())
                  << std::setw(10) << prc.getTimeArrival()
                  << std::setw(10) << prc.getTimeExecution()
                  << std::setw(10) << prc.getPrtLvl()
                  << std::setw(10) << st
                  << std::setw(10) << ct
                  << std::setw(10) << wt
                  << std::setw(10) << tat
                  << "\n";
    }

    if (!completed.empty()) {
        std::cout << "\nAverage Waiting Time: " << (totalWT / completed.size()) << "\n";
        std::cout << "Average Turnaround Time: " << (totalTAT / completed.size()) << "\n";
    }
}
