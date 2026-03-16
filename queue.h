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
	
	int push(const Type& newItem );

    int remove(Type& removedItem);
	
	int peek(Type& retrievedItem);
	
	int serve();				// this function requires that the -- operator is overloaded on whatever datatype is passed to the template
};

#include "queue.cpp"

#endif // QUEUE_H
