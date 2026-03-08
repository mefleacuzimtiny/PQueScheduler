#include "scheduler.h"

void genTestFile(int n) {
    // create a file "input" + str(n) + ".txt"
    // if the file already exists, just return
    // and don't proceed or regenerate.

    // it is a comma separated value file with the columns
    // PID, timeArrival, timeExecution, prtLvl
    // the PID is P0, P1, P2, P3... and so on. This part
    // isn't random; the PID must be in a sequence
    // to avoid collisions since it's the primary key
}

void test10() {
    //creation of schedular with x amount of priortiy levels
    //ill take 10 for now, do change it later if
    Scheduler scheduler(10);

    //load the process data from the file
    scheduler.loadFromFile("input.txt");

    //run scheduling simulation
    scheduler.run();

    //print resultttttttert7gd8ifywg
    scheduler.printResults();
}

void test100();
void test500();
void test1000();
void test10000();

int main() {

    genTestFile(10);
    genTestFile(100);
    genTestFile(500);
    genTestFile(1000);
    genTestFile(10000);


    // test10();

    // test100();

    // test500();

    // test1000();

    // test10000();

    return 0;
}
