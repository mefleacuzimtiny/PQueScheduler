#include "scheduler.h"

#include <iostream>
#include <fstream>
#include <string>


// ------------------ PROVIDED MAIN.CPP (UNCHANGED) ------------------
void genTestFile(int n) {
    std::string filename = "input" + std::to_string(n) + ".csv";
    std::ifstream checkFile(filename);
    if (checkFile.good()) return;
    checkFile.close();

    std::ofstream outFile(filename);
    outFile << "PID,timeArrival,timeExecution,prtLvl\n";
    std::srand(time(nullptr));
    int lastArrival = 0;

    for (int i = 0; i < n; i++) {
        std::string pid = "P" + std::to_string(i);
        int gap = std::rand() % 10;
        lastArrival += gap;
        int timeExecution = 1 + std::rand() % 10;
        int prtLvl = std::rand() % 10;
        outFile << pid << "," << lastArrival << "," << timeExecution << "," << prtLvl << "\n";
    }
    outFile.close();
}

void test(int n) {
    Scheduler scheduler(10, n);
    scheduler.loadFromFile("input" + std::to_string(n) + ".csv");
    scheduler.printResults();
}



int main() {
    genTestFile(7);
    genTestFile(10);
    genTestFile(100);
    genTestFile(500);
    genTestFile(1000);
    genTestFile(10000);

    test(7); // Example test
//	 test(10);
//	 test(100);
//	 test(500);
//	 test(1000);
    // test(10000);

    return 0;
}
