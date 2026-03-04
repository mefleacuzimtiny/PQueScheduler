#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "prtqueue.h"

class Scheduler
{
public:
    Scheduler();
private:
    PrtQueue<Process> task_que;
};

#endif // SCHEDULER_H
