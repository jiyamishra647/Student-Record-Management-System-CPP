#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Student.h"
#include <string>
using namespace std;

// linked list to store all student records
class LinkedList
{
private:
    Node *head;

public:
    LinkedList();

    void addStudent(Student s);
    void displayAll();
    Node *searchStudent(int regNo);
    bool updateStudent(int regNo, Student newData);
    bool deleteStudent(int regNo, Student &deletedStudent);
    void sortByRegNo();

    void loadFromFile(string filename);
    void saveToFile(string filename);
};

#endif
