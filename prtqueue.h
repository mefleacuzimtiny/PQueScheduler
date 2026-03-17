#ifndef PRTQUEUE_H
#define PRTQUEUE_H

// ==========================================
// 3. PrtQueue Implementation
// ==========================================

#include "semideque.h"


template <typename T>
class PrtQueue {
private:
    int levels;
    SemiDeque<T>* queues;
    
public:
    PrtQueue(int lvl = 10);
    
    PrtQueue(const PrtQueue &) = delete;
    PrtQueue(PrtQueue &&) = delete;
    PrtQueue &operator=(const PrtQueue &) = delete;
    PrtQueue &operator=(PrtQueue &&) = delete;
    
    ~PrtQueue();
    
    void push(int priority, T value);
    
    T popHighest();
    
    bool empty();
    
    bool hasHigher(int priority);
};

#include "prtqueue.cpp"

#endif // PRTQUEUE_H
