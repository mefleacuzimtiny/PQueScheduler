#ifndef SEMIDEQUE_H
#define SEMIDEQUE_H


// ==========================================
// 2. SemiDeque Implementation
// ==========================================

template <typename T>
class SemiDeque {
private:
    T* arr;
    int capacity;
    int head;
    int tail;
    int count;
    
    void resize(int newCap);
    
public:
    SemiDeque();
    
    ~SemiDeque();
    
    void push(T val);
    
    void pushBack(T val);
    
    T pop();
    
    bool empty() const;
};

#include "semideque.cpp"

#endif // SEMIDEQUE_H
