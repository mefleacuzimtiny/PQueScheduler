#ifndef QUEUE_H
#define QUEUE_H

template <class Type>
class Queue {
private:
    int front;
    int rear;
    int maxQue;
    int count;
    Type* items;


public:
    // Queue& operator=(const Queue& other) = delete;  // explicitly prohibit = operator

    Queue();

    Queue(int max);

    Queue(const Queue& other);             // explicitly prohibit copy constructor

    Queue& operator=(const Queue& other);

    ~Queue();

    bool isFull() const;

    bool isEmpty() const;

    int insert(const Type& newItem);

    int remove(Type& removedItem);
};

#include "queue.cpp"

#endif // QUEUE_H
