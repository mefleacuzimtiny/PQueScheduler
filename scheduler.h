#ifndef SCHEDULER_H
#define SCHEDULER_H


// ==========================================
// 4. Scheduler Implementation
// ==========================================


#include "process.h"
#include "prtqueue.h"

class Scheduler {
private:
    int levels;
    int maxProcesses;
    Process* loadedProcesses;
    PrtQueue<Process> readyQueue;
    
    GanttEntry* gantt;
    int ganttCapacity;
    unsigned int ganttCount;
    
    void addGanttEntry(int start, int end, const std::string& pid);
    
public:
    Scheduler(int lvl, int n);
    
    ~Scheduler();
    
    void loadFromFile(const std::string& filename);
    
    void run();
    
    void genGantt();
    
    // NEW: Method to print the requested table
    void printTable();
    
    void printSummary();
    
    void printResults();
};

#endif // SCHEDULER_H
