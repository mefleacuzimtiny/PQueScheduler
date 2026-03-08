#include "queue.h"
#include "process.h"

#include <iostream>

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
void Queue<Type>::insert(const Type &newItem) {
    if (isFull()) {
        std::cout << "Queue is Full!" << '\n';
        return;
    }

    rear = (rear + 1) % maxQue;
    items[rear] = newItem;
    count++;
}

template<class Type>
void Queue<Type>::remove(Type &removedItem) {
    if (isEmpty()) {
        std::cout << "Queue is Empty!" << '\n';
        return;
    }

    removedItem = items[front];
    front = (front + 1) % maxQue;   // circular increment
    count--;
}


template class Queue<Process>;
