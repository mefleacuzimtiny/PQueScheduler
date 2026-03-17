#ifndef PRTQUEUE_CPP
#define PRTQUEUE_CPP

#include "prtqueue.h"
#include "semideque.h"

template<typename T>
PrtQueue<T>::PrtQueue(int lvl) : levels(lvl) {
    queues = new SemiDeque<T>[levels];
}

template<typename T>
PrtQueue<T>::~PrtQueue() {
    delete[] queues;
}

template<typename T>
void PrtQueue<T>::push(int priority, T value) {
    if (priority >= 0 && priority < levels) {
        queues[priority].push(value);
    }
}

template<typename T>
T PrtQueue<T>::popHighest() {
    // for (int i = 0; i < levels; i++) {        // lower index = higher priority
    for (int i = levels - 1; i >= 0; i--) {      // higher index = higher priority
        if (!queues[i].empty()) {
            return queues[i].pop();
        }
    }
    return T();
}

template<typename T>
bool PrtQueue<T>::empty() {
    for (int i = 0; i < levels; ++i) {
        if (!queues[i].empty()) return false;
    }
    return true;
}

template<typename T>
bool PrtQueue<T>::hasHigher(int priority) {
    // for (int i = 0; i < priority; i++) {        // lower index = higher priority
    for (int i = levels - 1; i > priority; i--) {    // higher index = higher priority
        if (!queues[i].empty()) return true;
    }
    return false;
}


#endif
