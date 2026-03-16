#ifndef PQUESCHEDULER_IMPL_QUEUE
#define PQUESCHEDULER_IMPL_QUEUE


#include "queue.h"
#include "process.h"

#include <iostream>

template<class Type>
Queue<Type>::Queue(const Queue& other) {
    // 1. Copy the primitive metadata
    maxQue = other.maxQue;
    count = other.count;
    front = other.front;
    rear = other.rear;

    // 2. Allocate NEW memory for this instance
    items = new Type[maxQue];

    // 3. Deep copy the actual data from the other queue
    // We copy the entire underlying array so the front/rear indices stay valid
    for (int i = 0; i < maxQue; i++) {
        items[i] = other.items[i];
    }
}

template<class Type>
Queue<Type>& Queue<Type>::operator=(const Queue<Type>& other) {
    // 1. Self-assignment check
    // If we try to assign a queue to itself, do nothing.
    if (this == &other) {
        return *this;
    }

    // 2. Clean up existing resources
    // Prevent memory leaks by deleting the old 'items' array.
    delete[] items;

    // 3. Copy primitive metadata
    maxQue = other.maxQue;
    count = other.count;
    front = other.front;
    rear = other.rear;

    // 4. Allocate NEW memory and deep copy
    items = new Type[maxQue];
    for (int i = 0; i < maxQue; i++) {
        items[i] = other.items[i];
    }

    return *this;
}

template<class Type>
Queue<Type>::Queue() {
    maxQue = 10;
    items = new Type[maxQue];
    front = 0;
    rear = -1;
    count = 0;
}

template<class Type>
Queue<Type>::Queue(int max) {
    maxQue = max;
    items = new Type[maxQue];
    front = 0;
    rear = -1;
    count = 0;
}

template<class Type>
Queue<Type>::~Queue() {
    delete[] items;
}

template<class Type>
bool Queue<Type>::isFull() const {
    return (count == maxQue);
}

template<class Type>
bool Queue<Type>::isEmpty() const {
    return (count == 0);
}

template<class Type>
int Queue<Type>::insert(const Type &newItem) {
    if (isFull()) {
        std::cout << "Queue is Full!" << '\n';
        return 0;
    }

    rear = (rear + 1) % maxQue;
    items[rear] = newItem;
    count++;
    return 1;
}


template<class Type>
int Queue<Type>::push(const Type& newItem ) {
	if (isFull()) {
		std::cout << "Queue is Full!" << '\n';
		return 0;
	}
	
	front = (front - 1) % maxQue;
	items[front] = newItem;
	count++;
	return 1;
}

template<class Type>
int Queue<Type>::remove(Type &removedItem) {
    if (isEmpty()) {
        std::cout << "Queue is Empty!" << '\n';
        return 0;
    }

    removedItem = items[front];
    front = (front + 1) % maxQue;   // circular increment
    count--;
    return 1;
}

template<class Type>
int Queue<Type>::peek(Type &retrievedItem) {
	if (isEmpty()) {
		std::cout << "Queue is Empty!" << '\n';
		return 0;
	}
	
	retrievedItem = items[front];
	return 1;
}

template<class Type>
int Queue<Type>::serve() {
	if (isEmpty()) {
		std::cout << "Queue is Empty!" << '\n';
		return 0;
	}
	
	items[front]--;
	return 1;
}


// template class Queue<Process>;
#endif
