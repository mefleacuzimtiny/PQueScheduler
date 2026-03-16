#ifndef PQUESCHEDULER_IMPL_PRTQUEUE
#define PQUESCHEDULER_IMPL_PRTQUEUE

#include "prtqueue.h"
#include <iostream>

template <class ItemType>
PrtQueue<ItemType>::PrtQueue(const PrtQueue &other) {
    levels = other.levels;
    queSize = other.queSize;
    pQ = new Queue<ItemType>[levels];
    for (int i = 0; i < levels; i++) {
        pQ[i] = other.pQ[i];
    }
}

template<class ItemType>
PrtQueue<ItemType>::~PrtQueue() {
    delete[] pQ;
}

template <class ItemType>
PrtQueue<ItemType> &PrtQueue<ItemType>::operator=(const PrtQueue &other) {
    if (this == &other) {
        return *this;
    }

    delete[] pQ;

    levels = other.levels;
    queSize = other.queSize;
    pQ = new Queue<ItemType>[levels];
    for (int i = 0; i < levels; i++) {
        pQ[i] = other.pQ[i];
    }

    return *this;
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
void PrtQueue<ItemType>::Insert(ItemType newItem, int prt) {
    // should insert item at p priority level
    if (prt < 0 || prt >= levels) { // check bounds properly
        std::cout << "Priority out of bounds" << std::endl;
        return;
    }
    if (!pQ[prt].insert(newItem)) {

        std:: cout << "Queue size: " << pQ[prt].isFull() << std::endl;
        // exit(1);
    }
}


// ToDo: Come back to fix this later once done with implementing the low number as high priority execution first (it's easier to test)
// template<class ItemType>
// void PrtQueue<ItemType>::Remove(ItemType& item) {
//     // should remove highest priority item
//     // assuming higher index = higher priority
//     for (int i = levels - 1; i > -1; i--) {
//         if (!pQ[i].isEmpty()) {
//             pQ[i].remove(item);
//             return;
//         }
//     }
// }

template<class ItemType>
void PrtQueue<ItemType>::Remove(ItemType& item) {
    for (int i = 0; i < levels; i++) {
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

template <class ItemType>
void PrtQueue<ItemType>::Peek(ItemType& item) {
	// remember to update this too alongside the removal function
	for (int i = 0; i < levels; i++) {
		if (!pQ[i].isEmpty()) {
			pQ[i].peek(item);
			return;
		}
	}
}

template <class ItemType>
void PrtQueue<ItemType>::Serve() {				// also requires that the -- operator be overloaded for whatever datatype is passed to the class template
	// remember to update this too alongside the removal function
	for (int i = 0; i < levels; i++) {
		if (!pQ[i].isEmpty()) {
			pQ[i].serve();
			return;
		}
	}
}

template<class ItemType>
void PrtQueue<ItemType>::Push(const ItemType& newItem, int prt) {
	// should insert item at p priority level
	if (prt < 0 || prt >= levels) { // check bounds properly
		std::cout << "Priority out of bounds" << std::endl;
		return;
	}
	if (!pQ[prt].push(newItem)) {
		
		std:: cout << "Queue size: " << pQ[prt].isFull() << std::endl;
		// exit(1);
	}
}




// template class PrtQueue<Process>;

#endif
