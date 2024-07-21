#pragma once

#include<iostream>
using namespace std;
/********************************************************************
*             ���������                                             *
*********************************************************************/

// ��������� ��� ������������� ����������
struct Faculty
{
    int id;             // ������������� ����������
    string faculty;     // �������� ����������
    Faculty* next;      // ��������� �� ��������� ��������� � ������
    Faculty* prev;      // ��������� �� ���������� ��������� � ������
};

// ��������� ��� ������������� �������
struct Kafedra
{
    int idfac;           // ������������� ����������
    int idkaf;           // ������������� �������
    string kafedra;      // �������� �������
    Kafedra* next;       // ��������� �� ��������� ������� � ������
    Kafedra* prev;       // ��������� �� ���������� ������� � ������
};

// ��������� ��� ������������� ������������� ������
struct CompClass
{
    int idfacult;        // ������������� ����������
    int idkafed;         // ������������� �������, � ������� ��������� �����
    int idcla;           // ������������� ������������� ������
    string comp_class;   // �������� ������������� ������
    CompClass* next;     // ��������� �� ��������� ����� � ������
    CompClass* prev;     // ��������� �� ���������� ����� � ������
};

// ��������� ��� ������������� ����������
struct Computer
{
    int idfaculty;       // ������������� ����������
    int idkafedra;       // ������������� �������, � ������� ��������� ���������
    int idclass;         // ������������� ������, � �������� ��������� ���������
    string type;         // ��� ����������
    int snumber;         // �������� ����� ����������
    int year;            // ��� ������� ����������
    string status;       // ������ ����������
    string maintence;    // ������ ������������ ����������
    Computer* next;      // ��������� �� ��������� ��������� � ������
    Computer* prev;      // ��������� �� ���������� ��������� � ������
};

// ��������� ��� �������� ��������� ������
struct SearchCriteria
{
    int facultyid;      // ������������� ����������
    int kafedraid;      // ������������� ������� ��� ������
    int classid;        // ������������� ������ ��� ������
    string type;        // ��� ���������� ��� ������
    int snumber;        // �������� ����� ���������� ��� ������
    int year;           // ��� ������� ���������� ��� ������
    string status;      // ������ ���������� ��� ������
    string maintence;   // ������ ������������ ���������� ��� ������
};

// ��������� ��� ���������� ����������
struct AddComputer
{
    string type;        // ���������� ��� ����������
    int snumber;        // �������� ����� ����������
    int year;           // ��� ������� ����������
    string status;      // ������ ����������
    string maintence;   // ���� ���������� ������������ ����������
};
/********************************************************************
*                      ���������� ����������                        *
*********************************************************************/

//// ���������� ��������� �� ������ � ����� ������ �����������
//extern Faculty* headfac;
//extern Faculty* tailfac;
//
//// ���������� ��������� �� ������ � ����� ������ ������
//extern Kafedra* headkaf;
//extern Kafedra* tailkaf;
//
//// ���������� ��������� �� ������ � ����� ������ ������������ �������
//extern CompClass* headclass;
//extern CompClass* tailclass;
//
//// ���������� ��������� �� ������ � ����� ������ �����������
//extern Computer* headcomp;
//extern Computer* tailcomp;
/********************************************************************
*             ��������� �������                                                                          *
*********************************************************************/
// ������� ������� ��������� �� ������ �� ��������� ���������.
void DeleteComputer(Computer*& head, Computer*& tail, int sernumber, int cl, int kaf);
// ������� ������� ������������ ����� �� ������ �� ��������� ���������.
void DeleteCompClass(CompClass*& head, CompClass*& tail, int idkaf, int idcl);
// ������� ������� ������� �� ������ �� ���������� ��������������.
void DeleteKafedra(Kafedra*& head, Kafedra*& tail, int id);
// ������� ������� ��������� �� ������ �� ���������� ��������������.

// ������� �������� ���������� �� ��������� ��������������
void DeleteFaculty2(int id,
    Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    // ���������� ��������� �� ������ � ����� ������ ������
    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    // ���������� ��������� �� ������ � ����� ������ ������������ �������
    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    // ���������� ��������� �� ������ � ����� ������ �����������
    Computer*& headcompLoc,
    Computer*& tailcompLoc);

// ������� ���������� ���������� ������������� ��� ����������.
int GenerateIdFac(Faculty* head);
// ������� ���������� ���������� ������������� ��� �������.
int GenerateIdkaf(Kafedra* head);
// ������� ���������� ���������� ������������� ��� ������������� ������.
int GenerateIdcl(CompClass* head);
// ������� ��������� ����� ��������� � ������.
void AddFaculty(const string& facultyName, int& fac, Faculty*& headfacLoc, Faculty*& tailfacLoc);
// ������� ��������� ����� ������� � ������.
void AddKafedra(const string& kafedraName, int& kaf, int fac, Kafedra*& headkafLoc, Kafedra*& tailkafLoc, Faculty*& headfacLoc, Faculty*& tailfacLoc);
// ������� ��������� ����� ������������ ����� � ������.
void AddCompClass(const string& compClassName, int& kaf, int& cl, int fac, Faculty*& headfacLoc, Faculty*& tailfacLoc, CompClass*& headclassLoc,
    CompClass*& tailclassLoc);
// ������� ��������� ����� ��������� � ������.
void AddComputer(struct AddComputer* computer, int fac, int kaf, int cl, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc);
// ������� ������� ������ ����������� �� �����.
Faculty* CreateFaculty(const char* filename, Faculty*& head, Faculty*& tail);
// ������� ������� ������ ������ �� �����.
Kafedra* CreateKafedra(const char* filename, Kafedra*& head, Kafedra*& tail);
// ������� ������� ������ ������������ ������� �� �����.
CompClass* CreateCompClass(const char* filename, CompClass*& head, CompClass*& tail);
// ������� ������� ������ ����������� �� �����.
Computer* CreateComputerList(const char* filename, Computer*& head, Computer*& tail);
// ������� ������� �� ����� ������ �����������.
void PrintFacultyList(Faculty* head);
// ������� ������� �� ����� ������ ������.
void PrintKafList(Kafedra* head);
// ������� ������� �� ����� ������ ������������ �������.
void PrintCompClassList(CompClass* head);
// ������� ������� �� ����� ������ �����������.
void PrintComputerList(Computer* head);
// ������� ��������� ����� �� �������� ���������.
void Search(const SearchCriteria& criteria, Faculty*& headfacLoc, Kafedra*& headkafLoc, CompClass*& headclassLoc, Computer*& headcompLoc);
// ������� ���������� ��������� �� ��������� ������ �� �������� ���������� �����.
void MoveForwardFaculty(Faculty* head, int step);
// ������� ���������� ��������� �� ��������� ����� �� �������� ���������� �����.
void MoveBackwardFaculty(Faculty* head, int step);
// ������� ���������� ��������� �� ������� ������ �� �������� ���������� �����.
void MoveForwardKafedra(Kafedra* head, int step);
// ������� ���������� ��������� �� ������� ����� �� �������� ���������� �����.
void MoveBackwardKafedra(Kafedra* head, int step);
// ������� ���������� ��������� �� ������������ ����� ������ �� �������� ���������� �����.
void MoveForwardCompClass(CompClass* head, int step);
// ������� ���������� ��������� �� ������������ ����� ����� �� �������� ���������� �����.
void MoveBackwardCompClass(CompClass* head, int step);
// ������� ���������� ��������� �� ��������� ������ �� �������� ���������� �����.
void MoveForwardComputer(Computer* head, int step);
// ������� ���������� ��������� �� ��������� ����� �� �������� ���������� �����.
void MoveBackwardComputer(Computer* head, int step);
// ������� ������������ ���������� ����������� � �������� ������.
int CountClassIdComp(Computer* head, int idcl);
// ������� ������������ ���������� ������, ��������� � �������� �������.
int CountKafIdClass(CompClass* head, int idkaf);
// ������� ������������ ���������� �����������, ��������� � �������� ��������.
int CountKafIdComp(Computer* head, int idkaf);
// ������� ��������� �������� �������� � ����������� �� ������� � ��������������.
// ������� ��� �������� ��������� (�����������, ������, �������, �����������)
void DelFunc(int comm1, int cinid,
    Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    // ���������� ��������� �� ������ � ����� ������ ������
    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    // ���������� ��������� �� ������ � ����� ������ ������������ �������
    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    // ���������� ��������� �� ������ � ����� ������ �����������
    Computer*& headcompLoc,
    Computer*& tailcompLoc);

// ������� ��������� ����������� �������� � ����������� �� ������� � ����.
void MoveFunc(int comm2, int moveStep, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc);
// ������� ��������� ������������ ����� ����.
bool IsValidDate(const string& date);
