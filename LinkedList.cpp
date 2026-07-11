#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

LinkedList::LinkedList()
{
    head = NULL;
}

// add new student at the end of list
void LinkedList::addStudent(Student s)
{
    Node *newNode = new Node;
    newNode->data = s;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

// print all students in table format
void LinkedList::displayAll()
{
    if (head == NULL)
    {
        cout << "No records found." << endl;
        return;
    }

    cout << "-------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) << "RegNo" << setw(20) << "Name" << setw(15) << "Program"
         << setw(8) << "Sem" << setw(10) << "Section" << setw(8) << "CGPA" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;

    Node *temp = head;
    while (temp != NULL)
    {
        cout << left << setw(10) << temp->data.regNo << setw(20) << temp->data.name
             << setw(15) << temp->data.program << setw(8) << temp->data.sem
             << setw(10) << temp->data.section << setw(8) << temp->data.cgpa << endl;
        temp = temp->next;
    }
    cout << "-------------------------------------------------------------------------------------" << endl;
}

// linear search by reg no
Node *LinkedList::searchStudent(int regNo)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data.regNo == regNo)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// find student and replace its data
bool LinkedList::updateStudent(int regNo, Student newData)
{
    Node *temp = searchStudent(regNo);
    if (temp == NULL)
        return false;

    temp->data = newData;
    return true;
}

// delete a node and give back the deleted student (for undo)
bool LinkedList::deleteStudent(int regNo, Student &deletedStudent)
{
    Node *temp = head;
    Node *prev = NULL;

    while (temp != NULL && temp->data.regNo != regNo)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return false; // student not found

    deletedStudent = temp->data;

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    delete temp;
    return true;
}

// bubble sort on linked list using reg no
void LinkedList::sortByRegNo()
{
    if (head == NULL)
        return;

    bool swapped;
    Node *ptr;
    Node *lastSorted = NULL;

    do
    {
        swapped = false;
        ptr = head;

        while (ptr->next != lastSorted)
        {
            if (ptr->data.regNo > ptr->next->data.regNo)
            {
                // swap the data, not the nodes
                Student temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = true;
            }
            ptr = ptr->next;
        }
        lastSorted = ptr;
    } while (swapped);
}

// load records from students.txt when program starts
void LinkedList::loadFromFile(string filename)
{
    ifstream fin(filename.c_str());
    if (!fin)
        return; // file may not exist on first run

    string line;
    while (getline(fin, line))
    {
        if (line.length() == 0)
            continue;

        stringstream ss(line);
        string part;
        Student s;

        getline(ss, part, ',');
        s.regNo = stoi(part);

        getline(ss, s.name, ',');
        getline(ss, s.program, ',');

        getline(ss, part, ',');
        s.sem = stoi(part);

        getline(ss, s.section, ',');

        getline(ss, part, ',');
        s.cgpa = stof(part);

        addStudent(s);
    }
    fin.close();
}

// save all records back to students.txt
void LinkedList::saveToFile(string filename)
{
    ofstream fout(filename.c_str());

    Node *temp = head;
    while (temp != NULL)
    {
        fout << temp->data.regNo << "," << temp->data.name << "," << temp->data.program << ","
             << temp->data.sem << "," << temp->data.section << "," << temp->data.cgpa << endl;
        temp = temp->next;
    }
    fout.close();
}
