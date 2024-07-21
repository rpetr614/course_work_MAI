#include "Headers.h"
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

// Функция для проверки корректности формата даты
bool IsValidDate(const string& date)
{
    if (date.length() != 10 || date[2] != '.' || date[5] != '.')
        return false;  // Проверка на корректный формат даты

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5)
            continue;  // Пропускаем символы '.'

        if (!isdigit(date[i]))
            return false;  // Проверка, что все символы между '.' являются цифрами
    }

    int days = (date[0] - 48) * 10 + date[1] - 48;
    int months = (date[3] - 48) * 10 + date[4] - 48;
    int years = (date[6] - 48) * 10 + date[7] - 48;

    // Проверка на корректный день, месяц и год
    if (days < 1 || days > 31 || months < 1 || months > 12 || years < 0)
        return false;

    return true;
}

// Функция для перемещения по спискам (факультетам, кафедрам, классам, компьютерам)
void MoveFunc(int comm2, int moveStep, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc)
{
    switch (comm2)
    {
    case 1:
        cout << "Введите шаг для перемещения (положительное для движения вперед, отрицательное для движения назад): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardFaculty(headfacLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardFaculty(headfacLoc, -moveStep);
        }
        else {
            cout << "Некорректный шаг для перемещения." << endl;
        }
        break;

    case 2:
        cout << "Введите шаг для перемещения (положительное для движения вперед, отрицательное для движения назад): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardKafedra(headkafLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardKafedra(headkafLoc, -moveStep);
        }
        else {
            cout << "Некорректный шаг для перемещения." << endl;
        }
        break;

    case 3:
        cout << "Введите шаг для перемещения по классам (положительное для движения вперед, отрицательное для движения назад): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardCompClass(headclassLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardCompClass(headclassLoc, -moveStep);
        }
        else {
            cout << "Некорректный шаг для перемещения." << endl;
        }
        break;

    case 4:
        cout << "Введите шаг для перемещения по компьютерам (положительное для движения вперед, отрицательное для движения назад): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardComputer(headcompLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardComputer(headcompLoc, -moveStep);
        }
        else {
            cout << "Некорректный шаг для перемещения." << endl;
        }
        break;
    }
}


//
// 

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
    Computer*& tailcompLoc)

{
    switch (comm1)
    {
    case 1:
        int facId;
        cout << "Введите ID факультета для удаления: ";
        cin >> facId;
        //DeleteFaculty(facId);
        DeleteFaculty2(facId,
            headfacLoc,
            tailfacLoc,

            // Глобальные указатели на начало и конец списка кафедр
            headkafLoc,
            tailkafLoc,

            // Глобальные указатели на начало и конец списка компьютерных классов
            headclassLoc,
            tailclassLoc,

            // Глобальные указатели на начало и конец списка компьютеров
            headcompLoc,
            tailcompLoc);
        break;

    case 2:
        int countkafcl, countkafco;
        cout << "Введите ID кафедры для удаления: ";
        cin >> cinid;
        countkafcl = CountKafIdClass(headclassLoc, cinid);
        countkafco = CountKafIdComp(headcompLoc, cinid);

        // Удаление кафедры и связанных с ней классов и компьютеров
        DeleteKafedra(headkafLoc, tailkafLoc, cinid);
        for (int i = 0; i < countkafcl; i++)
        {
            DeleteCompClass(headclassLoc, tailclassLoc, cinid, 0);
        }
        for (int i = 0; i < countkafco; i++)
        {
            DeleteComputer(headcompLoc, tailcompLoc, 0, 0, cinid);
        }
        break;

    case 3:
        int idkaf, idcl, countid;
        cout << "Введите ID кафедры и ID класса для удаления: ";
        cin >> idkaf >> idcl;

        // Удаление класса и связанных с ним компьютеров
        DeleteCompClass(headclassLoc, tailclassLoc, idkaf, idcl);
        countid = CountClassIdComp(headcompLoc, idcl);
        for (int i = 0; i < countid; i++)
        {
            DeleteComputer(headcompLoc, tailcompLoc, 0, idcl, 0);
        }
        break;

    case 4:
        int sernumber;
        cout << "Введите серийный номер или ID класса для удаления компьютера: ";
        cin >> sernumber;

        // Удаление компьютера по серийному номеру или ID класса
        DeleteComputer(headcompLoc, tailcompLoc, sernumber, 0, 0);
        break;
    }
}

//////////////////////////////


// Функция для подсчета количества компьютеров по заданному идентификатору кафедры
int CountKafIdComp(Computer* head, int idkaf)
{
    int count = 0;
    Computer* curr = head;

    // Цикл по списку компьютеров
    do
    {
        if (curr->idkafedra == idkaf)
        {
            count++;
        }
        curr = curr->next;
    } while (curr != head);

    return count;
}

// Функция для подсчета количества компьютерных классов по заданному идентификатору кафедры
int CountKafIdClass(CompClass* head, int idkaf)
{
    int count = 0;
    CompClass* curr = head;

    // Цикл по списку компьютерных классов
    do
    {
        if (curr->idkafed == idkaf)
        {
            count++;
        }
        curr = curr->next;
    } while (curr != head);

    return count;
}

// Функция для подсчета количества компьютеров по заданному идентификатору класса
int CountClassIdComp(Computer* head, int idcl)
{
    int count = 0;
    Computer* curr = head;

    // Цикл по списку компьютеров
    do
    {
        if (curr->idclass == idcl)
        {
            count++;
        }
        curr = curr->next;
    } while (curr != head);

    return count;
}


// Функция удаления факультета по заданному идентификатору
void DeleteFaculty2(int id, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc)
{
    if (headfacLoc == nullptr)
    {
        cout << "Список факультетов пуст." << endl;
        return;
    }

    // Итератор по факультетам
    Faculty* currFac = headfacLoc;

    // Перебираем факультеты
    do
    {
        if (currFac->id == id)
        {
            // Удаление связанных кафедр
            Kafedra* currKaf = headkafLoc;
            while (currKaf != nullptr)
            {
                if (currKaf->idfac == id)
                {
                    // Удаление связанных классов
                    CompClass* currClass = headclassLoc;
                    while (currClass != nullptr)
                    {
                        if (currClass->idfacult == id)
                        {
                            // Удаление связанных компьютеров
                            Computer* currComp = headcompLoc;
                            while (currComp != nullptr)
                            {
                                if (currComp->idfaculty == id)
                                {
                                    Computer* tempComp = currComp->next; // Сохраняем следующий компьютер перед удалением
                                    DeleteComputer(headcompLoc, tailcompLoc, currComp->snumber, 0, 0);
                                    currComp = tempComp; // Начинаем снова с следующего компьютера после удаления
                                }
                                else
                                {
                                    currComp = currComp->next;
                                    break;
                                }
                            }

                            DeleteCompClass(headclassLoc, tailclassLoc, currClass->idkafed, currClass->idcla);
                            currClass = headclassLoc; // Начинаем снова с начала после удаления
                        }
                        else
                        {
                            currClass = currClass->next;
                            break;
                        }
                    }

                    DeleteKafedra(headkafLoc, tailkafLoc, currKaf->idkaf);
                    currKaf = headkafLoc; // Начинаем снова с начала после удаления
                }
                else
                {
                    currKaf = currKaf->next;
                    break;
                }
            }

            // Удаление факультета
            if (currFac == headfacLoc)
            {
                headfacLoc = currFac->next;
                tailfacLoc->next = headfacLoc;
                headfacLoc->prev = tailfacLoc;

                if (currFac == currFac->next)
                {
                    headfacLoc = nullptr;
                    tailfacLoc = nullptr;
                }
            }
            else if (currFac == tailfacLoc)
            {
                tailfacLoc = tailfacLoc->prev;
                tailfacLoc->next = headfacLoc;
                headfacLoc->prev = tailfacLoc;
            }
            else
            {
                currFac->prev->next = currFac->next;
                currFac->next->prev = currFac->prev;
            }

            delete currFac;
            cout << "Факультет с ID " << id << " успешно удален." << endl;
            return;
        }

        currFac = currFac->next;
    } while (currFac != headfacLoc);

    cout << "Факультет с ID " << id << " не найден." << endl;
}

// Функция удаления кафедры по заданному идентификатору
void DeleteKafedra(Kafedra*& head, Kafedra*& tail, int id)
{
    if (head == nullptr)
    {
        cout << "Список кафедр пуст." << endl;
        return;
    }

    Kafedra* curr = head;

    // Перебираем кафедры
    do
    {
        if (curr->idkaf == id)
        {
            // Удаление элемента списка
            if (curr == head)
            {
                head = curr->next;
                tail->next = head;
                head->prev = tail;

                if (curr == curr->next)
                {
                    head = nullptr;
                    tail = nullptr;
                }
            }
            else if (curr == tail)
            {
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
            }
            else
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            delete curr;
            cout << "Кафедра с ID " << id << " успешно удалена." << endl;
            return;
        }
        curr = curr->next;
    } while (curr != head);

    cout << "Кафедра с ID " << id << " не найдена." << endl;
}

// Функция удаления компьютерного класса по заданным идентификаторам кафедры и класса
void DeleteCompClass(CompClass*& head, CompClass*& tail, int idkaf, int idcl)
{
    if (head == nullptr)
    {
        cout << "Список классов пуст." << endl;
        return;
    }

    CompClass* curr = head;

    // Перебираем компьютерные классы
    do
    {
        if ((curr->idcla == idcl && curr->idkafed == idkaf) || (curr->idkafed == idkaf && idcl == 0))
        {
            // Удаление элемента списка
            if (curr == head)
            {
                head = curr->next;
                tail->next = head;
                head->prev = tail;
                if (curr == curr->next)
                {
                    head = nullptr;
                    tail = nullptr;
                }
            }
            else if (curr == tail)
            {
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
            }
            else
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            delete curr;
            cout << "Класс с ID " << idcl << " на кафедре с ID " << idkaf << " успешно удален." << endl;
            return;
        }

        curr = curr->next;
    } while (curr != head);

    cout << "Класс с ID " << idcl << " на кафедре с ID " << idkaf << " не найден." << endl;
}

// Функция удаления компьютера по заданным параметрам
void DeleteComputer(Computer*& head, Computer*& tail, int sernumber, int cl, int kaf)
{
    if (head == nullptr)
    {
        cout << "Список компьютеров пуст." << endl;
        return;
    }

    Computer* curr = head;

    // Перебираем компьютеры
    do
    {
        if (curr->snumber == sernumber || curr->idclass == cl || curr->idkafedra == kaf)
        {
            // Удаление элемента списка
            if (curr == head)
            {
                head = curr->next;
                tail->next = head;
                head->prev = tail;

                if (curr == curr->next)
                {
                    head = nullptr;
                    tail = nullptr;
                }
            }
            else if (curr == tail)
            {
                tail = tail->prev;
                tail->next = head;
                head->prev = tail;
            }
            else
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }

            delete curr;
            cout << "Компьютер с серийным номером/ID " << sernumber << " успешно удален." << endl;
            return;
        }
        curr = curr->next;
    } while (curr != head);

    cout << "Компьютер с серийным номером/ID " << sernumber << " не найден." << endl;
}

// Функция генерации уникального идентификатора для факультета
int GenerateIdFac(Faculty* head)
{
    if (head == nullptr)
        return 1;

    Faculty* current = head;
    int maxId = current->id;

    // Перебираем факультеты
    do
    {
        if (current->id > maxId)
            maxId = current->id;

        current = current->next;
    } while (current != head);

    return maxId + 1;
}

// Функция генерации уникального идентификатора для кафедры
int GenerateIdkaf(Kafedra* head)
{
    if (head == nullptr)
        return 1;

    Kafedra* current = head;
    int maxId = current->idkaf;

    // Перебираем кафедры
    do
    {
        if (current->idkaf > maxId)
            maxId = current->idkaf;

        current = current->next;
    } while (current != head);

    return maxId + 1;
}

// Функция генерации уникального идентификатора для компьютерного класса
int GenerateIdcl(CompClass* head)
{
    if (head == nullptr)
        return 1;

    CompClass* current = head;
    int maxId = current->idcla;

    // Перебираем компьютерные классы
    do
    {
        if (current->idcla > maxId)
            maxId = current->idcla;

        current = current->next;
    } while (current != head);

    return maxId + 1;
}

// Функция добавления нового факультета
void AddFaculty(const string& facultyName, int& fac, Faculty*& headfacLoc, Faculty*& tailfacLoc)
{
    int newId = GenerateIdFac(headfacLoc);
    Faculty* facPtr = headfacLoc;

    // Поиск факультета по имени
    while (facPtr != nullptr)
    {
        if (facPtr->faculty == facultyName)
        {
            fac = facPtr->id;
            return;
        }
        facPtr = facPtr->next;
        if (facPtr == headfacLoc)
            break;
    }

    // Создание нового факультета
    Faculty* newNode = new Faculty();
    newNode->id = newId;
    fac = newId;
    newNode->faculty = facultyName;

    if (headfacLoc == nullptr)
    {
        headfacLoc = newNode;
        tailfacLoc = newNode;
        newNode->next = headfacLoc;
        newNode->prev = tailfacLoc;
    }
    else
    {
        tailfacLoc->next = newNode;
        newNode->prev = tailfacLoc;
        tailfacLoc = newNode;
        tailfacLoc->next = headfacLoc;
        headfacLoc->prev = tailfacLoc;
    }
}

// Функция добавления новой кафедры
void AddKafedra(const string& kafedraName, int& kaf, int fac, Kafedra*& headkafLoc, Kafedra*& tailkafLoc, Faculty*& headfacLoc, Faculty*& tailfacLoc)
{
    int newId = GenerateIdkaf(headkafLoc);
    Kafedra* kafPtr = headkafLoc;

    // Поиск кафедры по имени в заданном факультете
    while (kafPtr != nullptr)
    {
        if (kafPtr->kafedra == kafedraName && kafPtr->idfac == fac)
        {
            kaf = kafPtr->idkaf;
            return;
        }
        kafPtr = kafPtr->next;
        if (kafPtr == headkafLoc)
            break;
    }

    // Поиск факультета по ID
    Faculty* targetFac = headfacLoc;
    while (targetFac != nullptr)
    {
        if (targetFac->id == fac)
            break;

        targetFac = targetFac->next;

        if (targetFac == headfacLoc)
            break;
    }

    // Проверка существования факультета
    if (targetFac == nullptr)
    {
        cout << "Факультет с ID " << fac << " не найден." << endl;
        return;
    }

    // Создание новой кафедры
    Kafedra* newNode = new Kafedra();
    newNode->idfac = fac;
    newNode->idkaf = newId;
    kaf = newId;
    newNode->kafedra = kafedraName;

    if (headkafLoc == nullptr)
    {
        headkafLoc = newNode;
        tailkafLoc = newNode;
        newNode->next = headkafLoc;
        newNode->prev = tailkafLoc;
    }
    else
    {
        tailkafLoc->next = newNode;
        newNode->prev = tailkafLoc;
        tailkafLoc = newNode;
        tailkafLoc->next = headkafLoc;
        headkafLoc->prev = tailkafLoc;
    }
}
// Функция добавления нового компьютерного класса
void AddCompClass(const string& compClassName, int& kaf, int& cl, int fac, Faculty*& headfacLoc, Faculty*& tailfacLoc, CompClass*& headclassLoc,
    CompClass*& tailclassLoc)
{
    int newId = GenerateIdcl(headclassLoc);  // Генерация нового ID для класса
    CompClass* clPtr = headclassLoc;

    // Поиск класса по имени в указанном факультете
    while (clPtr != nullptr)
    {
        if (kaf != 0 && clPtr->idkafed == kaf && clPtr->comp_class == compClassName)
        {
            cl = clPtr->idcla;  // Если класс уже существует, возвращаем его ID
            return;
        }

        clPtr = clPtr->next;

        if (clPtr == headclassLoc)
            break;
    }

    // Поиск факультета по ID
    Faculty* targetFac = headfacLoc;
    while (targetFac != nullptr)
    {
        if (targetFac->id == fac)
            break;

        targetFac = targetFac->next;

        if (targetFac == headfacLoc)
            break;
    }

    // Проверка наличия факультета
    if (targetFac == nullptr)
    {
        cout << "Факультет с ID " << fac << " не найден." << endl;
        return;
    }

    // Создание нового компьютерного класса
    CompClass* newNode = new CompClass();
    newNode->idfacult = fac;
    newNode->idkafed = kaf;
    newNode->idcla = newId;
    cl = newId;
    newNode->comp_class = compClassName;

    // Добавление нового узла в список
    if (headclassLoc == nullptr)
    {
        headclassLoc = newNode;
        tailclassLoc = newNode;
        newNode->next = headclassLoc;
        newNode->prev = tailclassLoc;
    }
    else
    {
        tailclassLoc->next = newNode;
        newNode->prev = tailclassLoc;
        tailclassLoc = newNode;
        tailclassLoc->next = headclassLoc;
        headclassLoc->prev = tailclassLoc;
    }
}

// Функция добавления нового компьютера
void AddComputer(struct AddComputer* computer, int fac, int kaf, int cl, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc)
{
    // Проверка валидности ID факультета
    Faculty* targetFac = headfacLoc;
    while (targetFac != nullptr)
    {
        if (targetFac->id == fac)
            break;

        targetFac = targetFac->next;

        if (targetFac == headfacLoc)
        {
            cout << "Факультет с указанным ID не найден." << endl;
            return;
        }
    }

    // Проверка валидности ID кафедры
    Kafedra* targetKaf = headkafLoc;
    while (targetKaf != nullptr)
    {
        if (targetKaf->idkaf == kaf)
            break;

        targetKaf = targetKaf->next;

        if (targetKaf == headkafLoc)
        {
            cout << "Кафедра с указанным ID не найдена." << endl;
            return;
        }
    }

    // Проверка валидности ID класса
    CompClass* targetClass = headclassLoc;
    while (targetClass != nullptr)
    {
        if (targetClass->idcla == cl)
            break;

        targetClass = targetClass->next;

        if (targetClass == headclassLoc)
        {
            cout << "Класс с указанным ID не найден." << endl;
            return;
        }
    }

    // Создание нового компьютера
    Computer* newNode = new Computer();

    // Проверка и чтение серийного номера
    if (computer->snumber < 1000 || computer->snumber > 9999)
    {
        cerr << "Ошибка: Неверный серийный номер для компьютера." << endl;
        return;
    }

    // Проверка и чтение года выпуска
    if (computer->year < 1000 || computer->year > 2024)
    {
        cerr << "Ошибка: Неверный год выпуска для компьютера." << endl;
        return;
    }

    // Проверка валидности даты обслуживания
    if (!IsValidDate(computer->maintence))
    {
        cerr << "Ошибка: Неверная дата обслуживания для компьютера." << endl;
        delete newNode;  // Освобождение памяти для недействительного узла
        return;  // Пропуск добавления недействительного узла в список
    }

    // Заполнение данных о компьютере
    newNode->idfaculty = fac;
    newNode->idkafedra = kaf;
    newNode->idclass = cl;
    newNode->type = computer->type;
    newNode->snumber = computer->snumber;
    newNode->year = computer->year;
    newNode->status = computer->status;
    newNode->maintence = computer->maintence;

    // Добавление нового узла в список
    if (headcompLoc == nullptr)
    {
        headcompLoc = newNode;
        tailcompLoc = newNode;
        newNode->next = headcompLoc;
        newNode->prev = tailcompLoc;
    }
    else
    {
        tailcompLoc->next = newNode;
        newNode->prev = tailcompLoc;
        tailcompLoc = newNode;
        tailcompLoc->next = headcompLoc;
        headcompLoc->prev = tailcompLoc;
    }
    // Добавление нового компьютера в существующий факультет, кафедру и класс
}
// Функция создания списка факультетов из файла
Faculty* CreateFaculty(const char* filename, Faculty*& head, Faculty*& tail)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return nullptr;
    }

    // Чтение данных из файла
    while (!file.eof())
    {
        Faculty* newNode = new Faculty();
        file >> newNode->id >> newNode->faculty;

        // Добавление элемента в список
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Замыкание кольцевого списка
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    file.close();
    return head;
}

// Функция создания списка кафедр из файла
Kafedra* CreateKafedra(const char* filename, Kafedra*& head, Kafedra*& tail)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return nullptr;
    }

    // Чтение данных из файла
    while (!file.eof())
    {
        Kafedra* newNode = new Kafedra();
        file >> newNode->idfac >> newNode->idkaf >> newNode->kafedra;

        // Добавление элемента в список
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Замыкание кольцевого списка
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    file.close();
    return head;
}

// Функция создания списка компьютерных классов из файла
CompClass* CreateCompClass(const char* filename, CompClass*& head, CompClass*& tail)
{
    // Открываем файл
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return nullptr;
    }

    // Чтение данных из файла
    while (!file.eof())
    {
        // Создаем новый узел класса
        CompClass* newNode = new CompClass();
        file >> newNode->idfacult >> newNode->idkafed >> newNode->idcla >> newNode->comp_class;

        // Добавление элемента в список
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Связываем конец списка с началом
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    // Закрываем файл и возвращаем указатель на начало списка
    file.close();
    return head;
}
// Функция создания списка компьютеров из файла
Computer* CreateComputerList(const char* filename, Computer*& head, Computer*& tail)
{
    // Открываем файл
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return nullptr;
    }
    // Чтение данных из файла
    while (!file.eof())
    {
        // Создаем новый узел компьютера
        Computer* newNode = new Computer();
        file >> newNode->idfaculty >> newNode->idkafedra >> newNode->idclass >> newNode->type;

        // Проверка и чтение серийного номера
        int snumber;
        file >> snumber;
        if (snumber >= 1000 && snumber <= 9999)
        {
            newNode->snumber = snumber;
        }
        else
        {
            cerr << "Ошибка: Неверный серийный номер для компьютера." << endl;
            return nullptr;        // Пропуск добавления недействительного узла в список
        }
        // Проверка и чтение года выпуска
        int year;
        file >> year;
        if (year > 1000 && year < 2024)
        {
            newNode->year = year;
        }
        else
        {
            cerr << "Ошибка: Неверный год выпуска для компьютера." << endl;
            delete newNode;  // Освобождение памяти для недействительного узла
            return nullptr;        // Пропуск добавления недействительного узла в список
        }

        file >> newNode->status;
        string maintence;
        file >> maintence;

        // Проверка валидности даты обслуживания
        if (!IsValidDate(maintence))
        {
            cerr << "Ошибка: Неверная дата обслуживания для компьютера." << endl;
            delete newNode;  // Освобождение памяти для недействительного узла
            return nullptr;  // Пропуск добавления недействительного узла в список
        }

        newNode->maintence = maintence;

        // Добавление элемента в список
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Связываем конец списка с началом
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    // Закрываем файл и возвращаем указатель на начало списка
    file.close();
    return head;
}
// Функция вывода списка факультетов в консоль
void PrintFacultyList(Faculty* head) {
    Faculty* curr = head;

    cout << "\n\t\t\tСПИСОК ФАКУЛЬТЕТОВ\n\n";
    cout << "+---------------+------------------------------+\n";
    cout << "| ID Факультета |          Факультет           |\n";
    cout << "+---------------+------------------------------+\n";

    do {
        cout << "| " << setw(13) << left << curr->id << " | " << setw(28) << left << curr->faculty << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+------------------------------+\n";
}

// Функция вывода списка кафедр в консоль
void PrintKafList(Kafedra* head)
{
    Kafedra* curr = head;

    cout << "\n\t\t\tСПИСОК КАФЕДР\n\n";
    cout << "+---------------+---------------+------------------------------+\n";
    cout << "| ID Факультета |   ID Кафедры  |           Кафедра            |\n";
    cout << "+---------------+---------------+------------------------------+\n";

    do
    {
        cout << "| " << setw(13) << left << curr->idfac << " | " << setw(13) << left << curr->idkaf << " | " << setw(28) << left << curr->kafedra << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+---------------+------------------------------+\n";
}

// Функция вывода списка компьютерных классов в консоль
void PrintCompClassList(CompClass* head)
{
    CompClass* curr = head;

    cout << "\n\t\t\tСПИСОК КОМПЬЮТЕРНЫХ КЛАССОВ\n\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
    cout << "| ID Факультета |   ID Кафедры  |   ID Класса   |     Компьютерный класс       |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";

    do
    {
        cout << "| " << setw(13) << left << curr->idfacult << " | " << setw(13) << left << curr->idkafed << " | " << setw(13) << left << curr->idcla << " | " << setw(28) << left << curr->comp_class << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+---------------+---------------+------------------------------+\n";
}

// Функция вывода списка компьютеров в консоль
void PrintComputerList(Computer* head)
{
    Computer* curr = head;

    cout << "\n\t\t\tСПИСОК КОМПЬЮТЕРОВ\n\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout << "| ID Факультета |   ID Кафедры  |   ID Класса   |      Тип      | Серийный номер|  Год выпуска  |     Статус    |  Обслуживание |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

    do
    {
        cout << "| " << setw(13) << left << curr->idfaculty << " | " << setw(13) << left << curr->idkafedra << " | " << setw(13) << left << curr->idclass << " | " << setw(13) << left << curr->type << " | " << setw(13) << left << curr->snumber << " | " << setw(13) << left << curr->year << " | " << setw(13) << left << curr->status << " | " << setw(13) << left << curr->maintence << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
}


// Функция поиска и вывода информации по заданным критериям
void Search(const SearchCriteria& criteria, Faculty*& headfacLoc, Kafedra*& headkafLoc, CompClass*& headclassLoc, Computer*& headcompLoc)
{
    Faculty* facPtr = headfacLoc;
    while (facPtr != nullptr)
    {
        // Поиск факультета по ID
        if (facPtr->id == criteria.facultyid)
        {
            cout << "Найден факультет: " << facPtr->faculty << endl;

            // Вывод списка кафедр для найденного факультета
            Kafedra* kafPtr = headkafLoc;
            do
            {
                // Проверка условий поиска для кафедры
                if (kafPtr->idfac == facPtr->id && (criteria.kafedraid == 0 || kafPtr->idkaf == criteria.kafedraid))
                {
                    cout << " - Кафедра: " << kafPtr->kafedra << endl;
                    // Вывод списка классов для найденной кафедры
                    CompClass* clPtr = headclassLoc;
                    do
                    {
                        // Проверка условий поиска для класса
                        if (clPtr->idkafed == kafPtr->idkaf && (criteria.classid == 0 || clPtr->idcla == criteria.classid))
                        {
                            cout << "   - Класс: " << clPtr->comp_class << endl;

                            // Вывод списка компьютеров для найденного класса
                            Computer* compPtr = headcompLoc;
                            do
                            {
                                // Проверка условий поиска для компьютера
                                if (compPtr->idclass == clPtr->idcla &&
                                    (criteria.type.empty() || compPtr->type == criteria.type) &&
                                    (criteria.snumber == 0 || compPtr->snumber == criteria.snumber) &&
                                    (criteria.year == 0 || compPtr->year == criteria.year) &&
                                    (criteria.status.empty() || compPtr->status == criteria.status) &&
                                    (criteria.maintence.empty() || compPtr->maintence == criteria.maintence))
                                {
                                    cout << "      - Компьютер: Тип: " << compPtr->type << ", Серийный номер: " << compPtr->snumber
                                        << ", Год выпуска: " << compPtr->year << ", Статус: " << compPtr->status
                                        << ", Обслуживание: " << compPtr->maintence << endl;
                                }
                                compPtr = compPtr->next;
                            } while (compPtr != headcompLoc);
                        }
                        clPtr = clPtr->next;
                    } while (clPtr != headclassLoc);
                }
                kafPtr = kafPtr->next;
            } while (kafPtr != headkafLoc);

            return;
        }
        facPtr = facPtr->next;
    }
    cout << "Факультет с ID " << criteria.facultyid << " не найден." << endl;
}

// Функция перемещения вперёд по списку факультетов
void MoveForwardFaculty(Faculty* head, int step)
{
    // Проверка наличия элементов в списке факультетов
    if (head == nullptr)
    {
        cout << "Список факультетов пуст." << endl;
        return;
    }

    Faculty* current = head;

    // Перемещение указателя вперёд на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // Проверка достижения конца списка
        if (current == head)
        {
            cout << "Достигнут конец списка. Невозможно переместиться дальше." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\t\tСПИСОК ФАКУЛЬТЕТОВ\n\n";
    cout << "+---------------+------------------------------+\n";
    cout << "| ID Факультета |          Факультет           |\n";
    cout << "+---------------+------------------------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->id << " | " << setw(28) << current->faculty << " |\n";
    cout << "+---------------+------------------------------+\n";
}

// Функция перемещения назад по списку факультетов
void MoveBackwardFaculty(Faculty* head, int step)
{
    // Проверка наличия элементов в списке факультетов
    if (head == nullptr)
    {
        cout << "Список факультетов пуст." << endl;
        return;
    }

    Faculty* current = head;

    // Перемещение указателя назад на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // Проверка достижения начала списка
        if (current == head)
        {
            cout << "Достигнут начало списка. Невозможно переместиться назад." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\t\tСПИСОК ФАКУЛЬТЕТОВ\n\n";
    cout << "+---------------+------------------------------+\n";
    cout << "| ID Факультета |          Факультет           |\n";
    cout << "+---------------+------------------------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->id << " | " << setw(28) << current->faculty << " |\n";
    cout << "+---------------+------------------------------+\n";
}

// Функция перемещения вперёд по списку кафедр
void MoveForwardKafedra(Kafedra* head, int step)
{
    // Проверка наличия элементов в списке кафедр
    if (head == nullptr)
    {
        cout << "Список кафедр пуст." << endl;
        return;
    }

    Kafedra* current = head;

    // Перемещение указателя вперёд на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // Проверка достижения конца списка
        if (current == head)
        {
            cout << "Достигнут конец списка. Невозможно переместиться дальше." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\t\tСПИСОК КАФЕДР\n\n";
    cout << "+---------------+---------------+------------------------------+\n";
    cout << "| ID Факультета | ID Кафедры    | Кафедра                      |\n";
    cout << "+---------------+---------------+------------------------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->idfac << " | " << setw(13) << current->idkaf << " | " << setw(28) << current->kafedra << " |\n";
    cout << "+---------------+---------------+------------------------------+\n";
}

// Функция перемещения назад по списку кафедр
void MoveBackwardKafedra(Kafedra* head, int step)
{
    // Проверка наличия элементов в списке кафедр
    if (head == nullptr)
    {
        cout << "Список кафедр пуст." << endl;
        return;
    }

    Kafedra* current = head;

    // Перемещение указателя назад на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // Проверка достижения начала списка
        if (current == head)
        {
            cout << "Достигнут начало списка. Невозможно переместиться назад." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\t\tСПИСОК КАФЕДР\n\n";
    cout << "+---------------+---------------+------------------------------+\n";
    cout << "| ID Факультета | ID Кафедры    | Кафедра                      |\n";
    cout << "+---------------+---------------+------------------------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->idfac << " | " << setw(13) << current->idkaf << " | " << setw(28) << current->kafedra << " |\n";
    cout << "+---------------+---------------+------------------------------+\n";
}

// Функция перемещения вперёд по списку компьютерных классов
void MoveForwardCompClass(CompClass* head, int step)
{
    // Проверка наличия элементов в списке классов
    if (head == nullptr)
    {
        cout << "Список классов пуст." << endl;
        return;
    }

    CompClass* current = head;

    // Перемещение указателя вперёд на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // Проверка достижения конца списка
        if (current == head)
        {
            cout << "Достигнут конец списка. Невозможно переместиться дальше." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\tСПИСОК КОМПЬЮТЕРНЫХ КЛАССОВ\n\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
    cout << "| ID Факультета | ID Кафедры    | ID Класса     | Компьютерный класс           |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->idfacult << " | " << setw(13) << current->idkafed << " | " << setw(13) << current->idcla << " | " << setw(28) << current->comp_class << " |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
}

// Функция перемещения назад по списку компьютерных классов
void MoveBackwardCompClass(CompClass* head, int step)
{
    // Проверка наличия элементов в списке классов
    if (head == nullptr)
    {
        cout << "Список классов пуст." << endl;
        return;
    }

    CompClass* current = head;

    // Перемещение указателя назад на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // Проверка достижения начала списка
        if (current == head)
        {
            cout << "Достигнут начало списка. Невозможно переместиться назад." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\tСПИСОК КОМПЬЮТЕРНЫХ КЛАССОВ\n\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
    cout << "| ID Факультета | ID Кафедры    | ID Класса     | Компьютерный класс           |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->idfacult << " | " << setw(13) << current->idkafed << " | " << setw(13) << current->idcla << " | " << setw(28) << current->comp_class << " |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
}

// Функция перемещения вперёд по списку компьютеров
void MoveForwardComputer(Computer* head, int step)
{
    // Проверка наличия элементов в списке компьютеров
    if (head == nullptr)
    {
        cout << "Список компьютеров пуст." << endl;
        return;
    }

    Computer* current = head;

    // Перемещение указателя вперёд на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // Проверка достижения конца списка
        if (current == head)
        {
            cout << "Достигнут конец списка. Невозможно переместиться дальше." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\t\tСПИСОК КОМПЬЮТЕРОВ\n\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout << "| ID Факультета | ID Кафедры    | ID Класса     | Тип           | Серийный номер| Год выпуска   | Статус        | Обслуживание  |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->idfaculty << " | " << setw(13) << current->idkafedra << " | " << setw(13) << current->idclass << " | "
        << setw(13) << current->type << " | " << setw(13) << current->snumber << " | " << setw(13) << current->year << " | "
        << setw(13) << current->status << " | " << setw(13) << current->maintence << " |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
}

// Функция перемещения назад по списку компьютеров
void MoveBackwardComputer(Computer* head, int step)
{
    // Проверка наличия элементов в списке компьютеров
    if (head == nullptr)
    {
        cout << "Список компьютеров пуст." << endl;
        return;
    }

    Computer* current = head;

    // Перемещение указателя назад на заданное количество шагов
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // Проверка достижения начала списка
        if (current == head)
        {
            cout << "Достигнут начало списка. Невозможно переместиться назад." << endl;
            return;
        }
    }

    // Вывод заголовка таблицы
    cout << "\n\t\t\tСПИСОК КОМПЬЮТЕРОВ\n\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout << "| ID Факультета | ID Кафедры    | ID Класса     | Тип           | Серийный номер| Год выпуска   | Статус        | Обслуживание  |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

    // Вывод данных текущего узла списка в виде строки таблицы
    cout << "| " << setw(13) << current->idfaculty << " | " << setw(13) << current->idkafedra << " | " << setw(13) << current->idclass << " | "
        << setw(13) << current->type << " | " << setw(13) << current->snumber << " | " << setw(13) << current->year << " | "
        << setw(13) << current->status << " | " << setw(13) << current->maintence << " |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
}
