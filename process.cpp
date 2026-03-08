#include "process.h"
#include <sstream>

int Process::timeStart() const {
    return timeArrival; // assuming no stored waiting time
}

int Process::timeFinish() const {
    return timeStart() + timeExecution; // CT = ST + BT
}

int Process::timeWaiting() const {
    return timeStart() - timeArrival; // WT = ST - AT
}

int Process::timeTurnaround() const {
    return timeFinish() - timeArrival; // TAT = CT - AT
}



std::istream& operator>>(std::istream& in, Process& p) {
    std::string line;

    if (!std::getline(in, line))
        return in;

    std::stringstream ss(line);
    std::string token;

    // PID (P<number>)
    std::getline(ss, token, ',');
    if (!token.empty() && token[0] == 'P')
        p.PID = std::stoi(token.substr(1));

    // timeArrival
    std::getline(ss, token, ',');
    p.timeArrival = std::stoi(token);

    // timeExecution
    std::getline(ss, token, ',');
    p.timeExecution = std::stoi(token);

    // prtLvl
    std::getline(ss, token, ',');
    p.prtLvl = std::stoi(token);

    return in;
}



int Process::getPID() const {
    return PID;
}

void Process::setPID(int newPID) {
    PID = newPID;
}

int Process::getTimeArrival() const {
    return timeArrival;
}

void Process::setTimeArrival(int newTimeArrival) {
    timeArrival = newTimeArrival;
}

int Process::getTimeExecution() const {
    return timeExecution;
}

void Process::setTimeExecution(int newTimeExecution) {
    timeExecution = newTimeExecution;
}

int Process::getPrtLvl() const {
    return prtLvl;
}

void Process::setPrtLvl(int newPrtLvl) {
    prtLvl = newPrtLvl;
}
