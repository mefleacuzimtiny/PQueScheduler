#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "prtqueue.h"
#include "process.h"
#include <vector>
#include <string>


class Scheduler {
public:
    Scheduler(int levels, int queSize);                     // creation of scheduler with given number of priority levels

    void loadFromFile(const std::string& filename);         // loading processes from input file (relies on enQueProcess())

    void run();                                              // running the scheduling simulation

    void printResults() const;                              // print results/averages



private:

    void enQueProcess(Process prc);                         // priority-based insertion

    void execute(Process& prc);                             // execute one process

    PrtQueue<Process> processQueue;                         // priority queue storing processes

    std::vector<Process> completed;                         // stores processes after execution
	
	std::vector<Process> gantt;

    int totalProcesses = 0;                                 // the total number of processes loaded

    int currentTime = 0;                                    // tracks the current time in simulation
};

#include "scheduler.cpp"

#endif
