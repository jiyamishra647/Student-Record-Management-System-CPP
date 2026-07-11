#include "StackQueue.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ---------------- STACK ----------------

Stack::Stack()
{
    top = -1;
}

// push a deleted student onto stack
void Stack::push(Student s)
{
    if (top == MAX_STACK - 1)
    {
        cout << "Undo stack is full, cannot store more." << endl;
        return;
    }
    top++;
    arr[top] = s;
}

// pop last deleted student (used for undo)
Student Stack::pop()
{
    Student s = arr[top];
    top--;
    return s;
}

bool Stack::isEmpty()
{
    return top == -1;
}

// ---------------- QUEUE ----------------

Queue::Queue()
{
    count = 0;
}

// add student, keep only last 5
void Queue::enqueue(Student s)
{
    if (count < MAX_QUEUE)
    {
        arr[count] = s;
        count++;
    }
    else
    {
        // queue full, shift everything left by one and drop oldest
        for (int i = 0; i < MAX_QUEUE - 1; i++)
            arr[i] = arr[i + 1];
        arr[MAX_QUEUE - 1] = s;
    }
}

// show recently added students
void Queue::display()
{
    if (count == 0)
    {
        cout << "No students added yet." << endl;
        return;
    }

    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) << "RegNo" << setw(20) << "Name" << setw(15) << "Program"
         << setw(8) << "Sem" << setw(10) << "Section" << setw(8) << "CGPA" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(10) << arr[i].regNo << setw(20) << arr[i].name
             << setw(15) << arr[i].program << setw(8) << arr[i].sem
             << setw(10) << arr[i].section << setw(8) << arr[i].cgpa << endl;
    }
    cout << "-------------------------------------------------------------------------------------" << endl;
}
