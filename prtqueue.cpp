#include "prtqueue.h"
#include <iostream>

template<class ItemType>
PrtQueue<ItemType>::~PrtQueue() {
    delete[] pQ;
}

template<class ItemType>
int PrtQueue<ItemType>::IsFull() const {
    // The priority queue is full only if all sub-queues are full.
    for (int i = 0; i < levels; i++) {
        if (!pQ[i].isFull()) {  // if any sub-queue is not full, the whole p-queue is not full
            return false;
        }
    }
    return true;
}

template<class ItemType>
int PrtQueue<ItemType>::IsEmpty() const {
    // if all sub-queues are empty, the whole p-queue is empty
    for (int i = 0; i < levels; i++) {
        if (!pQ[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

template<class ItemType>
void PrtQueue<ItemType>::Insert(ItemType newItem, int p) {
    // should insert item at p priority level
    if (p < 0 || p >= levels) { // check bounds properly
        std::cout << "Priority out of bounds" << std::endl;
        return;
    }
    pQ[p].insert(newItem);
}

template<class ItemType>
void PrtQueue<ItemType>::Remove(ItemType& item) {
    // should remove highest priority item
    // assuming higher index = higher priority
    for (int i = levels - 1; i >= 0; i--) {
        if (!pQ[i].isEmpty()) {
            pQ[i].remove(item);
            return;
        }
    }
}

template<class ItemType>
void PrtQueue<ItemType>::Remove(ItemType& item, int prt) {
    // removal overloaded for specific priority level
    if (prt < 0 || prt >= levels) {
        std::cout << "Priority out of bounds" << std::endl;
        return;
    }
    pQ[prt].remove(item);
}
