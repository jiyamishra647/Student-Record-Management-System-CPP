#include <iostream>
#include "Student.h"
#include "LinkedList.h"
#include "StackQueue.h"
using namespace std;

LinkedList list1;
Stack undoStack;
Queue recentQueue;

string fileName = "students.txt";

void showMenu()
{
    cout << "\n========================================" << endl;
    cout << "      STUDENT RECORD MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display Students" << endl;
    cout << "3. Search Student" << endl;
    cout << "4. Update Student" << endl;
    cout << "5. Delete Student" << endl;
    cout << "6. Sort Students" << endl;
    cout << "7. Undo Delete" << endl;
    cout << "8. Recently Added Students" << endl;
    cout << "9. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

// takes student details from user
Student getStudentInput()
{
    Student s;
    cout << "Enter Registration Number: ";
    cin >> s.regNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Program: ";
    getline(cin, s.program);
    cout << "Enter Semester: ";
    cin >> s.sem;
    cout << "Enter Section: ";
    cin.ignore();
    getline(cin, s.section);
    cout << "Enter CGPA: ";
    cin >> s.cgpa;
    return s;
}

void addStudentMenu()
{
    cout << "\n--- Add Student ---" << endl;
    Student s = getStudentInput();

    if (list1.searchStudent(s.regNo) != NULL)
    {
        cout << "Student with this reg no already exists!" << endl;
        return;
    }

    list1.addStudent(s);
    recentQueue.enqueue(s);
    list1.saveToFile(fileName);
    cout << "Student added successfully." << endl;
}

void searchStudentMenu()
{
    int regNo;
    cout << "\nEnter Registration Number to search: ";
    cin >> regNo;

    Node *found = list1.searchStudent(regNo);
    if (found == NULL)
    {
        cout << "Student not found." << endl;
        return;
    }

    cout << "\n--- Student Found ---" << endl;
    cout << "Reg No   : " << found->data.regNo << endl;
    cout << "Name     : " << found->data.name << endl;
    cout << "Program  : " << found->data.program << endl;
    cout << "Semester : " << found->data.sem << endl;
    cout << "Section  : " << found->data.section << endl;
    cout << "CGPA     : " << found->data.cgpa << endl;
}

void updateStudentMenu()
{
    int regNo;
    cout << "\nEnter Registration Number to update: ";
    cin >> regNo;

    Node *found = list1.searchStudent(regNo);
    if (found == NULL)
    {
        cout << "Student not found." << endl;
        return;
    }

    cout << "Enter new details below:" << endl;
    Student s = getStudentInput();
    s.regNo = regNo; // reg no should not change

    list1.updateStudent(regNo, s);
    list1.saveToFile(fileName);
    cout << "Student updated successfully." << endl;
}

void deleteStudentMenu()
{
    int regNo;
    cout << "\nEnter Registration Number to delete: ";
    cin >> regNo;

    Student deletedStudent;
    bool ok = list1.deleteStudent(regNo, deletedStudent);

    if (!ok)
    {
        cout << "Student not found." << endl;
        return;
    }

    undoStack.push(deletedStudent);
    list1.saveToFile(fileName);
    cout << "Student deleted. You can undo this if needed." << endl;
}

void undoDeleteMenu()
{
    if (undoStack.isEmpty())
    {
        cout << "\nNothing to undo." << endl;
        return;
    }

    Student s = undoStack.pop();
    list1.addStudent(s);
    list1.saveToFile(fileName);
    cout << "\nUndo successful. Student " << s.name << " restored." << endl;
}

int main()
{
    list1.loadFromFile(fileName);

    int choice;
    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudentMenu();
            break;
        case 2:
            cout << "\n--- All Students ---" << endl;
            list1.displayAll();
            break;
        case 3:
            searchStudentMenu();
            break;
        case 4:
            updateStudentMenu();
            break;
        case 5:
            deleteStudentMenu();
            break;
        case 6:
            list1.sortByRegNo();
            list1.saveToFile(fileName);
            cout << "\nStudents sorted by Registration Number." << endl;
            break;
        case 7:
            undoDeleteMenu();
            break;
        case 8:
            cout << "\n--- Recently Added Students ---" << endl;
            recentQueue.display();
            break;
        case 9:
            cout << "\nExiting program. Data saved. Bye!" << endl;
            break;
        default:
            cout << "\nInvalid choice, try again." << endl;
        }

    } while (choice != 9);

    return 0;
}
