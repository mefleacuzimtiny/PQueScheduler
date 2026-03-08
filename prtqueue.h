#ifndef PRTQUEUE_H
#define PRTQUEUE_H

#include "queue.h"
template<class ItemType>

class PrtQueue {
public:
    PrtQueue()
        : levels(10)
        , pQ(new Queue<ItemType>[levels]) {}
    PrtQueue(int lvls)
        : levels(lvls)
        , pQ(new Queue<ItemType>[levels]) {}
    ~PrtQueue();

    int IsFull() const;
    int IsEmpty() const;

    // Should call Que class insert() to insert item at p priority level
    void Insert(ItemType newItem, int p);

    // Should call Que class Remove() to remove highest priority item
    void Remove(ItemType& item);
    void Remove(ItemType& item, int prt);		// removes from a specific level

private:
    int levels;
    Queue <ItemType>* pQ;
};

#endif // PRTQUEUE_H
