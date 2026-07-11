#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "Student.h"

#define MAX_STACK 50
#define MAX_QUEUE 5

// stack to undo deleted students
class Stack
{
private:
    Student arr[MAX_STACK];
    int top;

public:
    Stack();
    void push(Student s);
    Student pop();
    bool isEmpty();
};

// queue to keep track of last 5 added students
class Queue
{
private:
    Student arr[MAX_QUEUE];
    int count;

public:
    Queue();
    void enqueue(Student s);
    void display();
};

#endif
