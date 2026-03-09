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

    friend std::istream& operator>>(std::istream& in, Process& p);
    friend std::ostream& operator<<(std::ostream& out, const Process& p);

    int getPID() const;
    void setPID(int newPID);
    int getTimeArrival() const;
    void setTimeArrival(int newTimeArrival);
    int getTimeExecution() const;
    void execQuantums(int quantums);
    int getPrtLvl() const;
    void setPrtLvl(int newPrtLvl);
};


#endif // PROCESS_H
