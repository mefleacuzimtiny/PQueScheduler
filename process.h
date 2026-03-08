#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process {
    int PID;
    int timeArrival;
    int timeExecution;
    int prtLvl;

public:
    // Calculated fields
    int timeStart() const;
    int timeFinish() const;
    int timeWaiting() const;
    int timeTurnaround() const;

    // // Overload for the Priority Queue (Higher priority value = higher precedence)
    // bool operator<(const Process& other) const {
    //     if (prtLvl == other.prtLvl) {
    //         return timeArrival > other.timeArrival; // Tie-breaker: First Come First Served
    //     }
    //     return prtLvl < other.prtLvl;
    // }

    friend std::istream& operator>>(std::istream& in, Process& p);


    int getPID() const;
    void setPID(int newPID);
    int getTimeArrival() const;
    void setTimeArrival(int newTimeArrival);
    int getTimeExecution() const;
    void setTimeExecution(int newTimeExecution);
    int getPrtLvl() const;
    void setPrtLvl(int newPrtLvl);
};


#endif // PROCESS_H
