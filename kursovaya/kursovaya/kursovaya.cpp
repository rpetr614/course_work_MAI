/********************************************************************
*               Информатика и вычислительная техника                *
*-------------------------------------------------------------------*
* Project Type : Win32 Console Application                          *
* Project Name : kursovaya                                          *
* File Name : kursovaya.cpp                                         *
* Language : C/C++                                                  *
* Programmer(s) : М3О-209Б-22                                       *
*                 Романов П.А                                       *
* Modifyed By :                                                     *
* Created : 30.11.2023                                              *
* Comment(s) : ПЕРВАЯ ПРОГРАММА                                     *
*                                                                   *
*                                                                   *
*********************************************************************/
#include <iostream>
#include <fstream>
#include"Headers.h"
#include<string>
using namespace std;

// Файловые константы для имен файлов с данными
const char* fkafedra = "Kafedra.txt";
const char* fcompclass = "CompClass.txt";
const char* fcomputer = "Technique.txt";
const char* ffaculty = "Faculties.txt";

//// Глобальные указатели на начало и конец списка факультетов
//Faculty* headfac = nullptr;
//Faculty* tailfac = nullptr;
//
//// Глобальные указатели на начало и конец списка кафедр
//Kafedra* headkaf = nullptr;
//Kafedra* tailkaf = nullptr;
//
//// Глобальные указатели на начало и конец списка компьютерных классов
//CompClass* headclass = nullptr;
//CompClass* tailclass = nullptr;
//
//// Глобальные указатели на начало и конец списка компьютеров
//Computer* headcomp = nullptr;
//Computer* tailcomp = nullptr;
/******************************************************************
*             ОСНОВНАЯ ПРОГРАММА                                  *
*******************************************************************/
int main()
{
    setlocale(LC_ALL, "Russian");
    bool flag = false; // Флаг, указывающий, был ли создан список
    int comm = 0; // Переменная для хранения выбранной команды
    int kafedraid = 0; // Идентификатор кафедры
    int classid = 0; // Идентификатор класса
    int kaf = 0; // Вспомогательная переменная для создания новой кафедры
    string newKafName, newFacName; // Название новой кафедры
    int cl = 0;
    int fac = 0; // Вспомогательная переменная для создания нового класса
    string newClassName; // Название нового класса
    SearchCriteria criteria; // Структура для хранения критериев поиска
    int comm2 = 0; // Переменная для второго уровня команд
    int comm1 = 0; // Переменная для первого уровня команд
    int cinid = 0; // Вспомогательная переменная для ввода идентификаторов
    int moveStep = 0; // Переменная для ввода шага перемещения
    ///////////////////////////////////////////////////////////////////////
        // Глобальные указатели на начало и конец списка факультетов
        Faculty* headfac2 = nullptr;
        Faculty* tailfac2 = nullptr;

        //// Глобальные указатели на начало и конец списка кафедр
        Kafedra* headkaf2 = nullptr;
        Kafedra* tailkaf2 = nullptr;

        //// Глобальные указатели на начало и конец списка компьютерных классов
        CompClass* headclass2 = nullptr;
        CompClass* tailclass2 = nullptr;

        //// Глобальные указатели на начало и конец списка компьютеров
        Computer* headcomp2 = nullptr;
        Computer* tailcomp2 = nullptr;


    ///////////////////////////////////////////////////////////////////

        // Бесконечный цикл для взаимодействия с пользователем
    while (true)
    {
        // Вывод списка команд
        cout << "\n\nСистема учета средств вычислительной техники института";
        cout << "\n\nСписок командpenis: \n1. Создание списка\n2. Печать списка\n3. Добавление новых элементов\n4. Удаление элемента\n5. Поиск\n6. Перемещение\n7. Вывод техники факультетов\n8. Вывод техники кафедры\n0. Выход из программы" << endl;
        cout << "\nВведите номер команды:\n";
        cin >> comm;
        // Проверка наличия списка перед выполнением операций, кроме создания списка и выхода
        if (comm != 1 && flag == false && comm != 0)
        {
            cout << "\nСписка не существует, сначала создайте его.";
        }
        else
        {
            switch (comm)
            {
            case 0:
                return 0; // Выход из программы

            case 1:
                // Создание списков кафедр, классов и компьютеров из файлов
                CreateFaculty(ffaculty, headfac2, tailfac2);
                CreateKafedra(fkafedra, headkaf2, tailkaf2);
                CreateCompClass(fcompclass, headclass2, tailclass2);
                CreateComputerList(fcomputer, headcomp2, tailcomp2);
                flag = true; // Установка флага создания списка
                break;
            case 2:
                // Печать списков факультетов, кафедр, классов и компьютеров
                if (!headfac2)
                {
                    cout << "Список пуст" << endl;
                    break;
                }
                PrintFacultyList(headfac2);
                if (!headkaf2)
                {
                    cout << "Список пуст" << endl;
                    break;
                }
                PrintKafList(headkaf2);
                if (!headclass2)
                {
                    cout << "Список пуст" << endl;
                    break;
                }
                PrintCompClassList(headclass2);
                if (!headcomp2)
                {
                    cout << "Список пуст" << endl;
                    break;
                }
                PrintComputerList(headcomp2);
                break;
            case 3:
            {
                // Добавление новой кафедры, класса и компьютера
                PrintFacultyList(headfac2);
                cout << endl << "Введите название нового факультета: ";
                cin >> newFacName;
                AddFaculty(newFacName, fac, headfac2, tailfac2);
                PrintKafList(headkaf2);
                cout << endl << "Введите название новой кафедры: ";
                cin >> newKafName;
                AddKafedra(newKafName, kaf, fac, headkaf2, tailkaf2, headfac2, tailfac2);
                PrintCompClassList(headclass2);
                cout << endl << "Введите название нового класса: ";
                cin >> newClassName;
                AddCompClass(newClassName, kaf, cl, fac, headfac2, tailfac2, headclass2, tailclass2);
                PrintComputerList(headcomp2);
                cout << endl << "Введите тип, серийный номер, год выпуска, статус и обслуживание нового компьютера: ";
                struct AddComputer computer;
                cin >> computer.type >> computer.snumber >> computer.year >> computer.status >> computer.maintence;
                AddComputer(&computer, fac, kaf, cl, headfac2, tailfac2, headkaf2, tailkaf2, headclass2, tailclass2, headcomp2, tailcomp2);
                break;
            }
            case 4:
                // Удаление элементов: факультета, кафедры, класса, компьютера
                cout << "1. О факультете\n2. О кафедре\n3. О классе\n4. О компьютерах";
                cin >> comm1;
                //DelFunc(comm1, cinid);

                // Функция для удаления элементов (факультетов, кафедр, классов, компьютеров)
                DelFunc(comm1, cinid, headfac2, tailfac2, headkaf2, tailkaf2, headclass2, tailclass2, headcomp2, tailcomp2);
                break;
            case 5:
            {
                // Поиск элементов по заданным критериям
                PrintFacultyList(headfac2);
                cout << endl << "Введите ID факультета: ";
                cin >> criteria.facultyid;
                PrintKafList(headkaf2);
                cout << endl << "Введите ID кафедры (или 0 для игнорирования): ";
                cin >> criteria.kafedraid;
                PrintCompClassList(headclass2);
                cout << endl << "Введите ID класса (или 0 для игнорирования): ";
                cin >> criteria.classid;
                PrintComputerList(headcomp2);
                cout << endl << "Введите тип компьютера (или оставьте пустым для игнорирования): ";
                cin.ignore();
                getline(cin, criteria.type);

                cout << "Введите серийный номер компьютера (или 0 для игнорирования): ";
                cin >> criteria.snumber;

                cout << "Введите год выпуска компьютера (или 0 для игнорирования): ";
                cin >> criteria.year;

                cout << "Введите статус компьютера (или оставьте пустым для игнорирования): ";
                cin.ignore();
                getline(cin, criteria.status);

                cout << "Введите статус обслуживания компьютера (или оставьте пустым для игнорирования): ";
                getline(cin, criteria.maintence);

                // Вызов функции поиска
                Search(criteria, headfac2, headkaf2, headclass2, headcomp2);
                break;
            }
            case 6:
                // Перемещение по спискам: факультетам, кафедрам, классам, компьютерам
                cout << "\n1. По факультетам\n2. По кафедрам\n3. По классам\n4. По компьютерам\nВведите по какому списку будет перемещение: ";
                cin >> comm2;

                MoveFunc(comm2, moveStep, headfac2, tailfac2, headkaf2, tailkaf2, headclass2, tailclass2, headcomp2, tailcomp2);
                break;
            case 7:
                PrintFacultyList(headfac2);
                cout << endl << "Введите ID факультета: ";
                cin >> criteria.facultyid;
                criteria.kafedraid = 0;
                criteria.classid = 0;
                criteria.snumber = 0;
                criteria.year = 0;
                Search(criteria, headfac2, headkaf2, headclass2, headcomp2);
                break;
            case 8:
                PrintFacultyList(headfac2);
                cout << endl << "Введите ID факультета: ";
                cin >> criteria.facultyid;
                PrintKafList(headkaf2);
                cout << endl << "Введите ID кафедры: ";
                cin >> criteria.kafedraid;
                criteria.classid = 0;
                criteria.snumber = 0;
                criteria.year = 0;
                Search(criteria, headfac2, headkaf2, headclass2, headcomp2);
                break;
            }
        }
    }
}
