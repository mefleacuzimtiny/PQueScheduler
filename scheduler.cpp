#include "scheduler.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Scheduler::Scheduler(int levels, int queSize)
    : processQueue(levels, queSize)
    , totalProcesses(0)
    , currentTime(0) {
}



void serve(Process& runningPrc, int& t, std::vector<Process>& completed, PrtQueue<Process>& processQueue) {
	std::cout << "At t = " << t << ": \n";
	std::cout << "P" << runningPrc.getPID() << " (burst time: " << runningPrc.getTimeExecution() << ")" << '\n';
	
	processQueue.Peek(runningPrc);
	
	processQueue.Serve();
//	runningPrc.execQuantums(1);
	
	if (runningPrc.isCompleted())
	{
		processQueue.Remove(runningPrc);
		completed.push_back(runningPrc);
	}
}

bool aProcessArrived(int& t, Process& incomingPrc) {
	return t == incomingPrc.getTimeArrival();
	// alternatively, return incoming.arrivaltime + incomingbursttime > runningarrivaltime
}

//bool readProcesses(Process& runningPrc, Process& incomingPrc, PrtQueue<Process>& processQueue, std::ifstream& file, bool all_prcs_arrived) {
//	
//	file >> incomingPrc;							//read next: read next incoming process (to check for arrived processes)
//	processQueue.Insert(incomingPrc, incomingPrc.getPrtLvl()); //save: to be revisited by the pque later or to be accessed immediately in the following line:
//	processQueue.Peek(runningPrc);				//are we still on the highest priority level? Get the top level process. It'll remain on the same process if that process is at the highest priority
//	return false;
//}

bool readProcesses(Process& runningPrc, Process& incomingPrc, PrtQueue<Process>& processQueue, std::ifstream& file) {
	if (file >> incomingPrc) {
		processQueue.Push(incomingPrc, incomingPrc.getPrtLvl());
		
		processQueue.Peek(runningPrc);
		
		return true;
	}
	
	if (!processQueue.IsEmpty()) {
		processQueue.Peek(runningPrc);
	}
	
	return false;
}

void Scheduler::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Failed to open file: " << filename << std::endl;
        exit(1);
    }

    std::string header;
    std::getline(file, header); // skip CSV header

//    Process prc;
//    while (file >> prc) {
//        enQueProcess(prc);
//        std::cout << "Loaded: " << prc << std::endl;
//        totalProcesses++;
//    }
	bool all_prcs_arrived = false;
	Process incomingPrc, runningPrc;
	
	all_prcs_arrived = readProcesses(runningPrc, incomingPrc, processQueue, file);
	file >> incomingPrc;

	
	int t = runningPrc.getTimeArrival();
	std::cout << "Execution started ";
	while (!all_prcs_arrived) {
		
		serve(runningPrc, t, completed, processQueue);		// prints process and decrements burst time. removes the process if it's incomplete
		
		t++;
		if (aProcessArrived(t, incomingPrc)) {				// in a real world situation, this would be replaced with a check for if there's a new process in a register in general
			
			gantt.push_back(runningPrc);					//pause: backup the current state of the running process so far into the gantt chart
			
			all_prcs_arrived = readProcesses(runningPrc, incomingPrc, processQueue, file);	// update the state of the processes. the running process will change if priority changed, else it'll stay the same, and the incoming process will be "ignored", i.e. kept at a lower priority level for later execution
		}
	}
	
	std::cout << "Execution ended at t = " << t << "\n";
    file.close();
}

 void Scheduler::run() {
	// processes the Gantt chart and calculates the waiting times
	
}



void Scheduler::enQueProcess(Process prc) {
    // insert arriving task into task_que at the process's priority level
    processQueue.Insert(prc, prc.getPrtLvl());
}


void Scheduler::execute(Process &prc) {
//    prc.execQuantums(1);
	prc--;
}


/*
currentTime = time of first
repeated call to processQueue.serve(p1) will print a <PID>,<number>_<PID>,<number>_<PID>,<number>_....
it'll also decrement p1.burst and increment currentTime
*/

//void Scheduler::run() {
//    currentTime = 0;
//    completed.clear();
//
//    Process prc;
//
//    while (!processQueue.IsEmpty()) {
//        // remove the highest priority process
//        processQueue.Remove(prc);
//
//        // calculate start time
//        int startTime = std::max(currentTime, prc.getTimeArrival());
//
//        // For our current Process class, we don’t have a member to store startTime
//        // We'll assume we calculate it on the fly in timeStart() using AT + WT
//        int waitingTime = startTime - prc.getTimeArrival();
//
//        currentTime = startTime + prc.getTimeExecution(); // finish time
//
//        // push process into completed
//        completed.push_back(prc);
//    }
//}

// Print results & averages
void Scheduler::printResults() const {
    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;

    std::cout << std::setw(5) << "Process ID"
              << std::setw(20) << "Arrival Time"
              << std::setw(20) << "Burst Time"
              << std::setw(20) << "Priority Level"
              << std::setw(20) << "Start Time"
              << std::setw(20) << "Completion Time"
              << std::setw(20) << "Waiting Time"
              << std::setw(20) << "Turnaround Time"
              << "\n";

    for (const Process& process : completed) {
        int startTime = process.timeStart();
        int completionTime = process.timeFinish();
        int waitingTime = process.timeWaiting();
        int turnaroundTime = process.timeTurnaround();

        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;

        std::cout << std::setw(5) << "P" + std::to_string(process.getPID())
                  << std::setw(20) << process.getTimeArrival()
                  << std::setw(20) << process.getTimeExecution()
                  << std::setw(20) << process.getPrtLvl()
                  << std::setw(20) << startTime
                  << std::setw(20) << completionTime
                  << std::setw(20) << waitingTime
                  << std::setw(20) << turnaroundTime
                  << "\n";
    }

    if (!completed.empty()) {
        std::cout << "\nAverage Waiting Time: " << (totalWaitingTime / completed.size()) << "\n";
        std::cout << "Average Turnaround Time: " << (totalTurnaroundTime / completed.size()) << "\n";
    }
}

