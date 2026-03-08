#include "scheduler.h"

#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

void genTestFile(int n) {
    std::string filename = "input" + std::to_string(n) + ".csv";

    // Check if file already exists
    std::ifstream checkFile(filename);
    if (checkFile.good()) {
        return; // File exists, do nothing
    }
    checkFile.close();

    std::ofstream outFile(filename);

    // CSV header
    outFile << "PID,timeArrival,timeExecution,prtLvl\n";

    std::srand(std::time(nullptr));

    for (int i = 0; i < n; i++) {
        std::string pid = "P" + std::to_string(i);

        int timeArrival = std::rand() % 20;     // 0–19
        int timeExecution = 1 + std::rand() % 10; // 1–10
        int prtLvl = 1 + std::rand() % 5;        // 1–5

        outFile << pid << ","
                << timeArrival << ","
                << timeExecution << ","
                << prtLvl << "\n";
    }

    outFile.close();
}

void test(int n) {
    //creation of schedular with x amount of priortiy levels
    //ill take 10 for now, do change it later if
    Scheduler scheduler(10, n);

    //load the process data from the file
    scheduler.loadFromFile("input" + std::to_string(n) + ".csv");

    //run scheduling simulation
    scheduler.run();

    //print resultttttttert7gd8ifywg
    scheduler.printResults();
}

int main() {

    genTestFile(10);
    genTestFile(100);
    genTestFile(500);
    genTestFile(1000);
    genTestFile(10000);

    test(10);
    // test(100);
    // test(500);
    // test(1000);
    // test(10000);

    return 0;
}
