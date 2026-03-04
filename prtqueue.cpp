#include "prtqueue.h"

#include <iostream>
using namespace std;

template<class ItemType>
PrtQueue<ItemType>::~PrtQueue() {
    delete[] pQ;
}

template<class ItemType>
int PrtQueue<ItemType>::IsFull() const {
    // The priority queue is full only if all sub-queues are full.
    for (int i=0; i < levels; i++) {
        if (pQ[i].isFull()) {
            return false;
        }
    }
    return true;
}

template<class ItemType>
int PrtQueue<ItemType>::IsEmpty() const {
    // if all sub-queues are empty, the whole p-queue is empty
    for (int i=0; i < levels; i++) {
        if(!pQ[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

template<class ItemType>
void PrtQueue<ItemType>::Insert(ItemType newItem, int p) {
    // Should insert item at p priority level
    if(p > levels){
        cout << "Maximum ten priority levels" << endl;
        return;
    }
    pQ[p].insert(newItem);
}


template<class ItemType>
void PrtQueue<ItemType>::Remove(ItemType& item) {
    // Should remove highest priority item
    for (int i=0; i < levels; i++) {
        if(!pQ[i].isEmpty()) {
            pQ[i].remove(item);
            return;
        }
    }
}

// removal overloaded for specific priority level
template<class ItemType>
void PrtQueue<ItemType>::Remove(ItemType& item, int prt) {
    if(prt > levels - 1){
        cout << "Maximum ten priority levels" << endl;
        return;
    }
    pQ[prt].remove(item);
}
