#include "scheduler.h"

#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

void genTestFile(int n) {
    std::string filename = "input" + std::to_string(n) + ".csv";

    std::ifstream checkFile(filename);
    if (checkFile.good()) return;
    checkFile.close();

    std::ofstream outFile(filename);
    outFile << "PID,timeArrival,timeExecution,prtLvl\n";

    std::srand(std::time(nullptr));

    int lastArrival = 0; // Start at time 0

    for (int i = 0; i < n; i++) {
        std::string pid = "P" + std::to_string(i);

        // Instead of a random number from 0-19,
        // we add a small random gap (0 to 10 units) to the last arrival.
        int gap = std::rand() % 10;
        lastArrival += gap;

        int timeExecution = 1 + std::rand() % 10;
        int prtLvl = std::rand() % 10;

        outFile << pid << ","
                << lastArrival << ","
                << timeExecution << ","
                << prtLvl << "\n";
    }

    outFile.close();
}

void test(int n) {
    Scheduler scheduler(10, n);

    scheduler.loadFromFile("input" + std::to_string(n) + ".csv");

    scheduler.run();

    scheduler.printResults();
}

int main() {

    genTestFile(7);
    genTestFile(10);
    genTestFile(100);
    genTestFile(500);
    genTestFile(1000);
    genTestFile(10000);

    test(7);
    // test(10);
    // test(100);
    // test(500);
    // test(1000);
    // test(10000);

    return 0;
}
