#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "prtqueue.h"
// #include "process.h"
#include <vector>
#include <string>


struct Process {
    int PID;
    int timeArrival;
    int timeExecution;
    int prtLvl;

    // Calculated fields
    int timeStart();
    int timeFinish();
    int timeWaiting();
    int timeTurnaround();

    // Overload for the Priority Queue (Higher priority value = higher precedence)
    bool operator<(const Process& other) const {
        if (prtLvl == other.prtLvl) {
            return timeArrival > other.timeArrival; // Tie-breaker: First Come First Served
        }
        return prtLvl < other.prtLvl;
    }
};

//handles loading/running/reporting the scheduling simulation
class Scheduler {
public:
    //creation of scheduler with given number of priority levels
    Scheduler(int levels);

    //loading processes from input file
    void loadFromFile(const std::string& filename);

    //running the scheduling simulation
    void run();

    //print results/averages
    void printResults() const;

private:
    //[riority queue storing processes
    PrtQueue<Process> task_que;

    //stores processes after execution
    std::vector<Process> completed;

    //tracks the current time in simulation
    int currentTime = 0;

    //the total number of processes loaded
    int totalProcesses = 0;
};

#endif
