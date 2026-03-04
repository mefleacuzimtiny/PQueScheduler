#include "queue.h"

#include <iostream>
using namespace std;

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
        cout << "Queue is Full!" << endl;
        return;
    }

    rear = (rear + 1) % maxQue;
    items[rear] = newItem;
    count++;
}

template<class Type>
void Queue<Type>::remove(Type &removedItem) {
    if (isEmpty()) {
        cout << "Queue is Empty!" << endl;
        return;
    }

    removedItem = items[front];
    front = (front + 1) % maxQue;   // circular increment
    count--;
}
