#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process {
    int PID = -1;
    int timeArrival = -1;
    int timeExecution = -1;
    int prtLvl = -1;

public:
    // Calculated fields
    int timeStart() const;
    int timeFinish() const;
    int timeWaiting() const;
    int timeTurnaround() const;

    friend std::istream& operator>>(std::istream& in, Process& p);
    friend std::ostream& operator<<(std::ostream& out, const Process& p);
	
	Process& operator=(const Process& b) {
		if (this != &b) {
			PID = b.PID;
			timeArrival = b.timeArrival;
			timeExecution = b.timeExecution;
			prtLvl = b.prtLvl;
		}
		return *this;
	}
	
	Process& operator--();      // prefix
	Process operator--(int);    // postfix
	
	bool isCompleted() {
		return timeExecution == 0;
	}
	bool isNULL() {
		return (PID == -1) && (timeArrival == -1) && (timeExecution ==-1) && (prtLvl == -1);
	}
	bool operator !() {
		return isNULL();
	}

    int getPID() const;
    void setPID(int newPID);
    int getTimeArrival() const;
    void setTimeArrival(int newTimeArrival);
    int getTimeExecution() const;
    void setTimeExecution(int newTimeExecution);
//    void execQuantums(int quantums);
    int getPrtLvl() const;
    void setPrtLvl(int newPrtLvl);
};

#include "process.cpp"
#endif // PROCESS_H
