#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

// struct to hold one student record
struct Student
{
    int regNo;
    string name;
    string program;
    int sem;
    string section;
    float cgpa;
};

// node for our linked list
struct Node
{
    Student data;
    Node *next;
};

#endif
