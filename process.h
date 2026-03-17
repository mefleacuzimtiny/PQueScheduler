#ifndef PROCESS_H
#define PROCESS_H

// ==========================================
// 1. Process and Gantt Structures
// ==========================================

#include <string>

struct Process {
    std::string pid;
    int timeArrival;
    int timeExecution;
    int prtLvl;
    int timeRemaining;
    int finishTime;      // Added for the table
    int turnaroundTime;
    int waitingTime;
    
    Process();
};

struct GanttEntry {
    int start;
    int end;
    std::string pid;
};

#endif // PROCESS_H
