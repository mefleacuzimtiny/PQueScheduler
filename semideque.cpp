
#ifndef SEMIDEQUE_CPP
#define SEMIDEQUE_CPP

#include "semideque.h"

template<typename T>
void SemiDeque<T>::resize(int newCap) {
    T* newArr = new T[newCap];
    for (int i = 0; i < count; i++) {
        newArr[i] = arr[(head + i) % capacity];
    }
    delete[] arr;
    arr = newArr;
    head = 0;
    tail = count;
    capacity = newCap;
}

template<typename T>
SemiDeque<T>::SemiDeque() : capacity(10), head(0), tail(0), count(0) {
    arr = new T[capacity];
}

template<typename T>
SemiDeque<T>::~SemiDeque() {
    delete[] arr;
}

template<typename T>
void SemiDeque<T>::push(T val) {
    if (count == capacity) resize(capacity * 2);
    arr[tail] = val;
    tail = (tail + 1) % capacity;
    count++;
}

template<typename T>
void SemiDeque<T>::pushBack(T val) {
    push(val);
}

template<typename T>
T SemiDeque<T>::pop() {
    if (count == 0) return T();
    T val = arr[head];
    head = (head + 1) % capacity;
    count--;
    return val;
}

template<typename T>
bool SemiDeque<T>::empty() const {
    return count == 0;
}


#endif
