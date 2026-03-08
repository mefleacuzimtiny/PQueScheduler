#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "prtqueue.h"
#include "process.h"
#include <vector>
#include <string>

//handles loading/running/reporting the scheduling simulation
class Scheduler {
public:
    //creation of scheduler with given number of priority levels
    Scheduler(int levels, int queSize);

    //loading processes from input file
    void loadFromFile(const std::string& filename);     // relies on enQueProcess()

    //running the scheduling simulation
    void run();

    //print results/averages
    void printResults() const;

private:

    // priority-based insertion
    void enQueProcess(Process prc);

    // priority queue storing processes
    PrtQueue<Process> task_que;

    // stores processes after execution
    std::vector<Process> completed;

    // tracks the current time in simulation
    int currentTime = 0;

    // the total number of processes loaded
    int totalProcesses = 0;
};

#endif
