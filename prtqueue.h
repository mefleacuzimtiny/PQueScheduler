#ifndef PRTQUEUE_H
#define PRTQUEUE_H

#include "queue.h"
template<class ItemType>

class PrtQueue {
public:
    // PrtQueue(const PrtQueue& other) = delete;
    // PrtQueue& operator=(const PrtQueue& other) = delete;

    PrtQueue()
        : levels(10)
        , pQ(new Queue<ItemType>[levels]) {}
    PrtQueue(int lvls)
        : levels(lvls)
        , pQ(new Queue<ItemType>[levels]) {}
    PrtQueue(int lvls, int qSize)
        : levels(lvls)
        , queSize(qSize)
        , pQ(new Queue<ItemType>[levels]) {
        for (int i = 0; i < levels; i++) {
            pQ[i] = Queue<ItemType>(queSize);
        }
    }

    PrtQueue(const PrtQueue &other);
    ~PrtQueue();
    PrtQueue &operator=(const PrtQueue &other);

    int IsFull() const;
    int IsEmpty() const;

    // Should call Que class insert() to insert item at prt priority level
    void Insert(ItemType newItem, int prt);

    // Should call Que class Remove() to remove highest priority item
    void Remove(ItemType& item);
    void Remove(ItemType& item, int prt);		// removes from a specific level

private:

    int levels;
    int queSize;
    Queue <ItemType>* pQ;
};


#include "prtqueue.cpp"

#endif // PRTQUEUE_H
