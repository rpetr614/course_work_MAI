#pragma once

#include<iostream>
using namespace std;
/********************************************************************
*             СТРУКТУРЫ                                             *
*********************************************************************/

// Структура для представления факультета
struct Faculty
{
    int id;             // Идентификатор факультета
    string faculty;     // Название факультета
    Faculty* next;      // Указатель на следующий факультет в списке
    Faculty* prev;      // Указатель на предыдущий факультет в списке
};

// Структура для представления кафедры
struct Kafedra
{
    int idfac;           // Идентификатор факультета
    int idkaf;           // Идентификатор кафедры
    string kafedra;      // Название кафедры
    Kafedra* next;       // Указатель на следующую кафедру в списке
    Kafedra* prev;       // Указатель на предыдущую кафедру в списке
};

// Структура для представления компьютерного класса
struct CompClass
{
    int idfacult;        // Идентификатор факультета
    int idkafed;         // Идентификатор кафедры, к которой относится класс
    int idcla;           // Идентификатор компьютерного класса
    string comp_class;   // Название компьютерного класса
    CompClass* next;     // Указатель на следующий класс в списке
    CompClass* prev;     // Указатель на предыдущий класс в списке
};

// Структура для представления компьютера
struct Computer
{
    int idfaculty;       // Идентификатор факультета
    int idkafedra;       // Идентификатор кафедры, к которой относится компьютер
    int idclass;         // Идентификатор класса, к которому относится компьютер
    string type;         // Тип компьютера
    int snumber;         // Серийный номер компьютера
    int year;            // Год выпуска компьютера
    string status;       // Статус компьютера
    string maintence;    // Статус обслуживания компьютера
    Computer* next;      // Указатель на следующий компьютер в списке
    Computer* prev;      // Указатель на предыдущий компьютер в списке
};

// Структура для хранения критериев поиска
struct SearchCriteria
{
    int facultyid;      // Идентификатор факультета
    int kafedraid;      // Идентификатор кафедры для поиска
    int classid;        // Идентификатор класса для поиска
    string type;        // Тип компьютера для поиска
    int snumber;        // Серийный номер компьютера для поиска
    int year;           // Год выпуска компьютера для поиска
    string status;      // Статус компьютера для поиска
    string maintence;   // Статус обслуживания компьютера для поиска
};

// Структура для добавления компьютера
struct AddComputer
{
    string type;        // Определяет тип компьютера
    int snumber;        // Серийный номер компьютера
    int year;           // Год выпуска компьютера
    string status;      // Статус компьютера
    string maintence;   // Дата последнего обслуживания компьютера
};
/********************************************************************
*                      ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ                        *
*********************************************************************/

//// Глобальные указатели на начало и конец списка факультетов
//extern Faculty* headfac;
//extern Faculty* tailfac;
//
//// Глобальные указатели на начало и конец списка кафедр
//extern Kafedra* headkaf;
//extern Kafedra* tailkaf;
//
//// Глобальные указатели на начало и конец списка компьютерных классов
//extern CompClass* headclass;
//extern CompClass* tailclass;
//
//// Глобальные указатели на начало и конец списка компьютеров
//extern Computer* headcomp;
//extern Computer* tailcomp;
/********************************************************************
*             ПРОТОТИПЫ ФУНКЦИЙ                                                                          *
*********************************************************************/
// Функция удаляет компьютер из списка по указанным критериям.
void DeleteComputer(Computer*& head, Computer*& tail, int sernumber, int cl, int kaf);
// Функция удаляет компьютерный класс из списка по указанным критериям.
void DeleteCompClass(CompClass*& head, CompClass*& tail, int idkaf, int idcl);
// Функция удаляет кафедру из списка по указанному идентификатору.
void DeleteKafedra(Kafedra*& head, Kafedra*& tail, int id);
// Функция удаляет факультет из списка по указанному идентификатору.

// Функция удаления факультета по заданному идентификатору
void DeleteFaculty2(int id,
    Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    // Глобальные указатели на начало и конец списка кафедр
    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    // Глобальные указатели на начало и конец списка компьютерных классов
    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    // Глобальные указатели на начало и конец списка компьютеров
    Computer*& headcompLoc,
    Computer*& tailcompLoc);

// Функция генерирует уникальный идентификатор для факультета.
int GenerateIdFac(Faculty* head);
// Функция генерирует уникальный идентификатор для кафедры.
int GenerateIdkaf(Kafedra* head);
// Функция генерирует уникальный идентификатор для компьютерного класса.
int GenerateIdcl(CompClass* head);
// Функция добавляет новый факультет в список.
void AddFaculty(const string& facultyName, int& fac, Faculty*& headfacLoc, Faculty*& tailfacLoc);
// Функция добавляет новую кафедру в список.
void AddKafedra(const string& kafedraName, int& kaf, int fac, Kafedra*& headkafLoc, Kafedra*& tailkafLoc, Faculty*& headfacLoc, Faculty*& tailfacLoc);
// Функция добавляет новый компьютерный класс в список.
void AddCompClass(const string& compClassName, int& kaf, int& cl, int fac, Faculty*& headfacLoc, Faculty*& tailfacLoc, CompClass*& headclassLoc,
    CompClass*& tailclassLoc);
// Функция добавляет новый компьютер в список.
void AddComputer(struct AddComputer* computer, int fac, int kaf, int cl, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc);
// Функция создает список факультетов из файла.
Faculty* CreateFaculty(const char* filename, Faculty*& head, Faculty*& tail);
// Функция создает список кафедр из файла.
Kafedra* CreateKafedra(const char* filename, Kafedra*& head, Kafedra*& tail);
// Функция создает список компьютерных классов из файла.
CompClass* CreateCompClass(const char* filename, CompClass*& head, CompClass*& tail);
// Функция создает список компьютеров из файла.
Computer* CreateComputerList(const char* filename, Computer*& head, Computer*& tail);
// Функция выводит на экран список факультетов.
void PrintFacultyList(Faculty* head);
// Функция выводит на экран список кафедр.
void PrintKafList(Kafedra* head);
// Функция выводит на экран список компьютерных классов.
void PrintCompClassList(CompClass* head);
// Функция выводит на экран список компьютеров.
void PrintComputerList(Computer* head);
// Функция выполняет поиск по заданным критериям.
void Search(const SearchCriteria& criteria, Faculty*& headfacLoc, Kafedra*& headkafLoc, CompClass*& headclassLoc, Computer*& headcompLoc);
// Функция перемещает указатель на факультет вперед на заданное количество шагов.
void MoveForwardFaculty(Faculty* head, int step);
// Функция перемещает указатель на факультет назад на заданное количество шагов.
void MoveBackwardFaculty(Faculty* head, int step);
// Функция перемещает указатель на кафедру вперед на заданное количество шагов.
void MoveForwardKafedra(Kafedra* head, int step);
// Функция перемещает указатель на кафедру назад на заданное количество шагов.
void MoveBackwardKafedra(Kafedra* head, int step);
// Функция перемещает указатель на компьютерный класс вперед на заданное количество шагов.
void MoveForwardCompClass(CompClass* head, int step);
// Функция перемещает указатель на компьютерный класс назад на заданное количество шагов.
void MoveBackwardCompClass(CompClass* head, int step);
// Функция перемещает указатель на компьютер вперед на заданное количество шагов.
void MoveForwardComputer(Computer* head, int step);
// Функция перемещает указатель на компьютер назад на заданное количество шагов.
void MoveBackwardComputer(Computer* head, int step);
// Функция подсчитывает количество компьютеров в заданном классе.
int CountClassIdComp(Computer* head, int idcl);
// Функция подсчитывает количество кафедр, связанных с заданным классом.
int CountKafIdClass(CompClass* head, int idkaf);
// Функция подсчитывает количество компьютеров, связанных с заданной кафедрой.
int CountKafIdComp(Computer* head, int idkaf);
// Функция выполняет удаление элемента в зависимости от команды и идентификатора.
// Функция для удаления элементов (факультетов, кафедр, классов, компьютеров)
void DelFunc(int comm1, int cinid,
    Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    // Глобальные указатели на начало и конец списка кафедр
    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    // Глобальные указатели на начало и конец списка компьютерных классов
    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    // Глобальные указатели на начало и конец списка компьютеров
    Computer*& headcompLoc,
    Computer*& tailcompLoc);

// Функция выполняет перемещение элемента в зависимости от команды и шага.
void MoveFunc(int comm2, int moveStep, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc);
// Функция проверяет корректность ввода даты.
bool IsValidDate(const string& date);
