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

    Queue();

    Queue(int max);

    ~Queue();

    bool isFull() const;

    bool isEmpty() const;

    void insert(const Type& newItem);

    void remove(Type& removedItem);
};

#endif // QUEUE_H
