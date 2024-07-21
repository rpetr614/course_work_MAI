#include "Headers.h"
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<iomanip>
using namespace std;

// ������� ��� �������� ������������ ������� ����
bool IsValidDate(const string& date)
{
    if (date.length() != 10 || date[2] != '.' || date[5] != '.')
        return false;  // �������� �� ���������� ������ ����

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5)
            continue;  // ���������� ������� '.'

        if (!isdigit(date[i]))
            return false;  // ��������, ��� ��� ������� ����� '.' �������� �������
    }

    int days = (date[0] - 48) * 10 + date[1] - 48;
    int months = (date[3] - 48) * 10 + date[4] - 48;
    int years = (date[6] - 48) * 10 + date[7] - 48;

    // �������� �� ���������� ����, ����� � ���
    if (days < 1 || days > 31 || months < 1 || months > 12 || years < 0)
        return false;

    return true;
}

// ������� ��� ����������� �� ������� (�����������, ��������, �������, �����������)
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
        cout << "������� ��� ��� ����������� (������������� ��� �������� ������, ������������� ��� �������� �����): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardFaculty(headfacLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardFaculty(headfacLoc, -moveStep);
        }
        else {
            cout << "������������ ��� ��� �����������." << endl;
        }
        break;

    case 2:
        cout << "������� ��� ��� ����������� (������������� ��� �������� ������, ������������� ��� �������� �����): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardKafedra(headkafLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardKafedra(headkafLoc, -moveStep);
        }
        else {
            cout << "������������ ��� ��� �����������." << endl;
        }
        break;

    case 3:
        cout << "������� ��� ��� ����������� �� ������� (������������� ��� �������� ������, ������������� ��� �������� �����): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardCompClass(headclassLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardCompClass(headclassLoc, -moveStep);
        }
        else {
            cout << "������������ ��� ��� �����������." << endl;
        }
        break;

    case 4:
        cout << "������� ��� ��� ����������� �� ����������� (������������� ��� �������� ������, ������������� ��� �������� �����): ";
        cin >> moveStep;

        if (moveStep > 0) {
            MoveForwardComputer(headcompLoc, moveStep);
        }
        else if (moveStep < 0) {
            MoveBackwardComputer(headcompLoc, -moveStep);
        }
        else {
            cout << "������������ ��� ��� �����������." << endl;
        }
        break;
    }
}


//
// 

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
    Computer*& tailcompLoc)

{
    switch (comm1)
    {
    case 1:
        int facId;
        cout << "������� ID ���������� ��� ��������: ";
        cin >> facId;
        //DeleteFaculty(facId);
        DeleteFaculty2(facId,
            headfacLoc,
            tailfacLoc,

            // ���������� ��������� �� ������ � ����� ������ ������
            headkafLoc,
            tailkafLoc,

            // ���������� ��������� �� ������ � ����� ������ ������������ �������
            headclassLoc,
            tailclassLoc,

            // ���������� ��������� �� ������ � ����� ������ �����������
            headcompLoc,
            tailcompLoc);
        break;

    case 2:
        int countkafcl, countkafco;
        cout << "������� ID ������� ��� ��������: ";
        cin >> cinid;
        countkafcl = CountKafIdClass(headclassLoc, cinid);
        countkafco = CountKafIdComp(headcompLoc, cinid);

        // �������� ������� � ��������� � ��� ������� � �����������
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
        cout << "������� ID ������� � ID ������ ��� ��������: ";
        cin >> idkaf >> idcl;

        // �������� ������ � ��������� � ��� �����������
        DeleteCompClass(headclassLoc, tailclassLoc, idkaf, idcl);
        countid = CountClassIdComp(headcompLoc, idcl);
        for (int i = 0; i < countid; i++)
        {
            DeleteComputer(headcompLoc, tailcompLoc, 0, idcl, 0);
        }
        break;

    case 4:
        int sernumber;
        cout << "������� �������� ����� ��� ID ������ ��� �������� ����������: ";
        cin >> sernumber;

        // �������� ���������� �� ��������� ������ ��� ID ������
        DeleteComputer(headcompLoc, tailcompLoc, sernumber, 0, 0);
        break;
    }
}

//////////////////////////////


// ������� ��� �������� ���������� ����������� �� ��������� �������������� �������
int CountKafIdComp(Computer* head, int idkaf)
{
    int count = 0;
    Computer* curr = head;

    // ���� �� ������ �����������
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

// ������� ��� �������� ���������� ������������ ������� �� ��������� �������������� �������
int CountKafIdClass(CompClass* head, int idkaf)
{
    int count = 0;
    CompClass* curr = head;

    // ���� �� ������ ������������ �������
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

// ������� ��� �������� ���������� ����������� �� ��������� �������������� ������
int CountClassIdComp(Computer* head, int idcl)
{
    int count = 0;
    Computer* curr = head;

    // ���� �� ������ �����������
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


// ������� �������� ���������� �� ��������� ��������������
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
        cout << "������ ����������� ����." << endl;
        return;
    }

    // �������� �� �����������
    Faculty* currFac = headfacLoc;

    // ���������� ����������
    do
    {
        if (currFac->id == id)
        {
            // �������� ��������� ������
            Kafedra* currKaf = headkafLoc;
            while (currKaf != nullptr)
            {
                if (currKaf->idfac == id)
                {
                    // �������� ��������� �������
                    CompClass* currClass = headclassLoc;
                    while (currClass != nullptr)
                    {
                        if (currClass->idfacult == id)
                        {
                            // �������� ��������� �����������
                            Computer* currComp = headcompLoc;
                            while (currComp != nullptr)
                            {
                                if (currComp->idfaculty == id)
                                {
                                    Computer* tempComp = currComp->next; // ��������� ��������� ��������� ����� ���������
                                    DeleteComputer(headcompLoc, tailcompLoc, currComp->snumber, 0, 0);
                                    currComp = tempComp; // �������� ����� � ���������� ���������� ����� ��������
                                }
                                else
                                {
                                    currComp = currComp->next;
                                    break;
                                }
                            }

                            DeleteCompClass(headclassLoc, tailclassLoc, currClass->idkafed, currClass->idcla);
                            currClass = headclassLoc; // �������� ����� � ������ ����� ��������
                        }
                        else
                        {
                            currClass = currClass->next;
                            break;
                        }
                    }

                    DeleteKafedra(headkafLoc, tailkafLoc, currKaf->idkaf);
                    currKaf = headkafLoc; // �������� ����� � ������ ����� ��������
                }
                else
                {
                    currKaf = currKaf->next;
                    break;
                }
            }

            // �������� ����������
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
            cout << "��������� � ID " << id << " ������� ������." << endl;
            return;
        }

        currFac = currFac->next;
    } while (currFac != headfacLoc);

    cout << "��������� � ID " << id << " �� ������." << endl;
}

// ������� �������� ������� �� ��������� ��������������
void DeleteKafedra(Kafedra*& head, Kafedra*& tail, int id)
{
    if (head == nullptr)
    {
        cout << "������ ������ ����." << endl;
        return;
    }

    Kafedra* curr = head;

    // ���������� �������
    do
    {
        if (curr->idkaf == id)
        {
            // �������� �������� ������
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
            cout << "������� � ID " << id << " ������� �������." << endl;
            return;
        }
        curr = curr->next;
    } while (curr != head);

    cout << "������� � ID " << id << " �� �������." << endl;
}

// ������� �������� ������������� ������ �� �������� ��������������� ������� � ������
void DeleteCompClass(CompClass*& head, CompClass*& tail, int idkaf, int idcl)
{
    if (head == nullptr)
    {
        cout << "������ ������� ����." << endl;
        return;
    }

    CompClass* curr = head;

    // ���������� ������������ ������
    do
    {
        if ((curr->idcla == idcl && curr->idkafed == idkaf) || (curr->idkafed == idkaf && idcl == 0))
        {
            // �������� �������� ������
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
            cout << "����� � ID " << idcl << " �� ������� � ID " << idkaf << " ������� ������." << endl;
            return;
        }

        curr = curr->next;
    } while (curr != head);

    cout << "����� � ID " << idcl << " �� ������� � ID " << idkaf << " �� ������." << endl;
}

// ������� �������� ���������� �� �������� ����������
void DeleteComputer(Computer*& head, Computer*& tail, int sernumber, int cl, int kaf)
{
    if (head == nullptr)
    {
        cout << "������ ����������� ����." << endl;
        return;
    }

    Computer* curr = head;

    // ���������� ����������
    do
    {
        if (curr->snumber == sernumber || curr->idclass == cl || curr->idkafedra == kaf)
        {
            // �������� �������� ������
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
            cout << "��������� � �������� �������/ID " << sernumber << " ������� ������." << endl;
            return;
        }
        curr = curr->next;
    } while (curr != head);

    cout << "��������� � �������� �������/ID " << sernumber << " �� ������." << endl;
}

// ������� ��������� ����������� �������������� ��� ����������
int GenerateIdFac(Faculty* head)
{
    if (head == nullptr)
        return 1;

    Faculty* current = head;
    int maxId = current->id;

    // ���������� ����������
    do
    {
        if (current->id > maxId)
            maxId = current->id;

        current = current->next;
    } while (current != head);

    return maxId + 1;
}

// ������� ��������� ����������� �������������� ��� �������
int GenerateIdkaf(Kafedra* head)
{
    if (head == nullptr)
        return 1;

    Kafedra* current = head;
    int maxId = current->idkaf;

    // ���������� �������
    do
    {
        if (current->idkaf > maxId)
            maxId = current->idkaf;

        current = current->next;
    } while (current != head);

    return maxId + 1;
}

// ������� ��������� ����������� �������������� ��� ������������� ������
int GenerateIdcl(CompClass* head)
{
    if (head == nullptr)
        return 1;

    CompClass* current = head;
    int maxId = current->idcla;

    // ���������� ������������ ������
    do
    {
        if (current->idcla > maxId)
            maxId = current->idcla;

        current = current->next;
    } while (current != head);

    return maxId + 1;
}

// ������� ���������� ������ ����������
void AddFaculty(const string& facultyName, int& fac, Faculty*& headfacLoc, Faculty*& tailfacLoc)
{
    int newId = GenerateIdFac(headfacLoc);
    Faculty* facPtr = headfacLoc;

    // ����� ���������� �� �����
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

    // �������� ������ ����������
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

// ������� ���������� ����� �������
void AddKafedra(const string& kafedraName, int& kaf, int fac, Kafedra*& headkafLoc, Kafedra*& tailkafLoc, Faculty*& headfacLoc, Faculty*& tailfacLoc)
{
    int newId = GenerateIdkaf(headkafLoc);
    Kafedra* kafPtr = headkafLoc;

    // ����� ������� �� ����� � �������� ����������
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

    // ����� ���������� �� ID
    Faculty* targetFac = headfacLoc;
    while (targetFac != nullptr)
    {
        if (targetFac->id == fac)
            break;

        targetFac = targetFac->next;

        if (targetFac == headfacLoc)
            break;
    }

    // �������� ������������� ����������
    if (targetFac == nullptr)
    {
        cout << "��������� � ID " << fac << " �� ������." << endl;
        return;
    }

    // �������� ����� �������
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
// ������� ���������� ������ ������������� ������
void AddCompClass(const string& compClassName, int& kaf, int& cl, int fac, Faculty*& headfacLoc, Faculty*& tailfacLoc, CompClass*& headclassLoc,
    CompClass*& tailclassLoc)
{
    int newId = GenerateIdcl(headclassLoc);  // ��������� ������ ID ��� ������
    CompClass* clPtr = headclassLoc;

    // ����� ������ �� ����� � ��������� ����������
    while (clPtr != nullptr)
    {
        if (kaf != 0 && clPtr->idkafed == kaf && clPtr->comp_class == compClassName)
        {
            cl = clPtr->idcla;  // ���� ����� ��� ����������, ���������� ��� ID
            return;
        }

        clPtr = clPtr->next;

        if (clPtr == headclassLoc)
            break;
    }

    // ����� ���������� �� ID
    Faculty* targetFac = headfacLoc;
    while (targetFac != nullptr)
    {
        if (targetFac->id == fac)
            break;

        targetFac = targetFac->next;

        if (targetFac == headfacLoc)
            break;
    }

    // �������� ������� ����������
    if (targetFac == nullptr)
    {
        cout << "��������� � ID " << fac << " �� ������." << endl;
        return;
    }

    // �������� ������ ������������� ������
    CompClass* newNode = new CompClass();
    newNode->idfacult = fac;
    newNode->idkafed = kaf;
    newNode->idcla = newId;
    cl = newId;
    newNode->comp_class = compClassName;

    // ���������� ������ ���� � ������
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

// ������� ���������� ������ ����������
void AddComputer(struct AddComputer* computer, int fac, int kaf, int cl, Faculty*& headfacLoc,
    Faculty*& tailfacLoc,

    Kafedra*& headkafLoc,
    Kafedra*& tailkafLoc,

    CompClass*& headclassLoc,
    CompClass*& tailclassLoc,

    Computer*& headcompLoc,
    Computer*& tailcompLoc)
{
    // �������� ���������� ID ����������
    Faculty* targetFac = headfacLoc;
    while (targetFac != nullptr)
    {
        if (targetFac->id == fac)
            break;

        targetFac = targetFac->next;

        if (targetFac == headfacLoc)
        {
            cout << "��������� � ��������� ID �� ������." << endl;
            return;
        }
    }

    // �������� ���������� ID �������
    Kafedra* targetKaf = headkafLoc;
    while (targetKaf != nullptr)
    {
        if (targetKaf->idkaf == kaf)
            break;

        targetKaf = targetKaf->next;

        if (targetKaf == headkafLoc)
        {
            cout << "������� � ��������� ID �� �������." << endl;
            return;
        }
    }

    // �������� ���������� ID ������
    CompClass* targetClass = headclassLoc;
    while (targetClass != nullptr)
    {
        if (targetClass->idcla == cl)
            break;

        targetClass = targetClass->next;

        if (targetClass == headclassLoc)
        {
            cout << "����� � ��������� ID �� ������." << endl;
            return;
        }
    }

    // �������� ������ ����������
    Computer* newNode = new Computer();

    // �������� � ������ ��������� ������
    if (computer->snumber < 1000 || computer->snumber > 9999)
    {
        cerr << "������: �������� �������� ����� ��� ����������." << endl;
        return;
    }

    // �������� � ������ ���� �������
    if (computer->year < 1000 || computer->year > 2024)
    {
        cerr << "������: �������� ��� ������� ��� ����������." << endl;
        return;
    }

    // �������� ���������� ���� ������������
    if (!IsValidDate(computer->maintence))
    {
        cerr << "������: �������� ���� ������������ ��� ����������." << endl;
        delete newNode;  // ������������ ������ ��� ����������������� ����
        return;  // ������� ���������� ����������������� ���� � ������
    }

    // ���������� ������ � ����������
    newNode->idfaculty = fac;
    newNode->idkafedra = kaf;
    newNode->idclass = cl;
    newNode->type = computer->type;
    newNode->snumber = computer->snumber;
    newNode->year = computer->year;
    newNode->status = computer->status;
    newNode->maintence = computer->maintence;

    // ���������� ������ ���� � ������
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
    // ���������� ������ ���������� � ������������ ���������, ������� � �����
}
// ������� �������� ������ ����������� �� �����
Faculty* CreateFaculty(const char* filename, Faculty*& head, Faculty*& tail)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "������ �������� �����: " << filename << endl;
        return nullptr;
    }

    // ������ ������ �� �����
    while (!file.eof())
    {
        Faculty* newNode = new Faculty();
        file >> newNode->id >> newNode->faculty;

        // ���������� �������� � ������
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

    // ��������� ���������� ������
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    file.close();
    return head;
}

// ������� �������� ������ ������ �� �����
Kafedra* CreateKafedra(const char* filename, Kafedra*& head, Kafedra*& tail)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "������ �������� �����: " << filename << endl;
        return nullptr;
    }

    // ������ ������ �� �����
    while (!file.eof())
    {
        Kafedra* newNode = new Kafedra();
        file >> newNode->idfac >> newNode->idkaf >> newNode->kafedra;

        // ���������� �������� � ������
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

    // ��������� ���������� ������
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    file.close();
    return head;
}

// ������� �������� ������ ������������ ������� �� �����
CompClass* CreateCompClass(const char* filename, CompClass*& head, CompClass*& tail)
{
    // ��������� ����
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "������ �������� �����: " << filename << endl;
        return nullptr;
    }

    // ������ ������ �� �����
    while (!file.eof())
    {
        // ������� ����� ���� ������
        CompClass* newNode = new CompClass();
        file >> newNode->idfacult >> newNode->idkafed >> newNode->idcla >> newNode->comp_class;

        // ���������� �������� � ������
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

    // ��������� ����� ������ � �������
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    // ��������� ���� � ���������� ��������� �� ������ ������
    file.close();
    return head;
}
// ������� �������� ������ ����������� �� �����
Computer* CreateComputerList(const char* filename, Computer*& head, Computer*& tail)
{
    // ��������� ����
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "������ �������� �����: " << filename << endl;
        return nullptr;
    }
    // ������ ������ �� �����
    while (!file.eof())
    {
        // ������� ����� ���� ����������
        Computer* newNode = new Computer();
        file >> newNode->idfaculty >> newNode->idkafedra >> newNode->idclass >> newNode->type;

        // �������� � ������ ��������� ������
        int snumber;
        file >> snumber;
        if (snumber >= 1000 && snumber <= 9999)
        {
            newNode->snumber = snumber;
        }
        else
        {
            cerr << "������: �������� �������� ����� ��� ����������." << endl;
            return nullptr;        // ������� ���������� ����������������� ���� � ������
        }
        // �������� � ������ ���� �������
        int year;
        file >> year;
        if (year > 1000 && year < 2024)
        {
            newNode->year = year;
        }
        else
        {
            cerr << "������: �������� ��� ������� ��� ����������." << endl;
            delete newNode;  // ������������ ������ ��� ����������������� ����
            return nullptr;        // ������� ���������� ����������������� ���� � ������
        }

        file >> newNode->status;
        string maintence;
        file >> maintence;

        // �������� ���������� ���� ������������
        if (!IsValidDate(maintence))
        {
            cerr << "������: �������� ���� ������������ ��� ����������." << endl;
            delete newNode;  // ������������ ������ ��� ����������������� ����
            return nullptr;  // ������� ���������� ����������������� ���� � ������
        }

        newNode->maintence = maintence;

        // ���������� �������� � ������
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

    // ��������� ����� ������ � �������
    if (head != nullptr && tail != nullptr)
    {
        tail->next = head;
        head->prev = tail;
    }

    // ��������� ���� � ���������� ��������� �� ������ ������
    file.close();
    return head;
}
// ������� ������ ������ ����������� � �������
void PrintFacultyList(Faculty* head) {
    Faculty* curr = head;

    cout << "\n\t\t\t������ �����������\n\n";
    cout << "+---------------+------------------------------+\n";
    cout << "| ID ���������� |          ���������           |\n";
    cout << "+---------------+------------------------------+\n";

    do {
        cout << "| " << setw(13) << left << curr->id << " | " << setw(28) << left << curr->faculty << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+------------------------------+\n";
}

// ������� ������ ������ ������ � �������
void PrintKafList(Kafedra* head)
{
    Kafedra* curr = head;

    cout << "\n\t\t\t������ ������\n\n";
    cout << "+---------------+---------------+------------------------------+\n";
    cout << "| ID ���������� |   ID �������  |           �������            |\n";
    cout << "+---------------+---------------+------------------------------+\n";

    do
    {
        cout << "| " << setw(13) << left << curr->idfac << " | " << setw(13) << left << curr->idkaf << " | " << setw(28) << left << curr->kafedra << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+---------------+------------------------------+\n";
}

// ������� ������ ������ ������������ ������� � �������
void PrintCompClassList(CompClass* head)
{
    CompClass* curr = head;

    cout << "\n\t\t\t������ ������������ �������\n\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
    cout << "| ID ���������� |   ID �������  |   ID ������   |     ������������ �����       |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";

    do
    {
        cout << "| " << setw(13) << left << curr->idfacult << " | " << setw(13) << left << curr->idkafed << " | " << setw(13) << left << curr->idcla << " | " << setw(28) << left << curr->comp_class << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+---------------+---------------+------------------------------+\n";
}

// ������� ������ ������ ����������� � �������
void PrintComputerList(Computer* head)
{
    Computer* curr = head;

    cout << "\n\t\t\t������ �����������\n\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout << "| ID ���������� |   ID �������  |   ID ������   |      ���      | �������� �����|  ��� �������  |     ������    |  ������������ |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

    do
    {
        cout << "| " << setw(13) << left << curr->idfaculty << " | " << setw(13) << left << curr->idkafedra << " | " << setw(13) << left << curr->idclass << " | " << setw(13) << left << curr->type << " | " << setw(13) << left << curr->snumber << " | " << setw(13) << left << curr->year << " | " << setw(13) << left << curr->status << " | " << setw(13) << left << curr->maintence << " |\n";
        curr = curr->next;
    } while (curr != head);

    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
}


// ������� ������ � ������ ���������� �� �������� ���������
void Search(const SearchCriteria& criteria, Faculty*& headfacLoc, Kafedra*& headkafLoc, CompClass*& headclassLoc, Computer*& headcompLoc)
{
    Faculty* facPtr = headfacLoc;
    while (facPtr != nullptr)
    {
        // ����� ���������� �� ID
        if (facPtr->id == criteria.facultyid)
        {
            cout << "������ ���������: " << facPtr->faculty << endl;

            // ����� ������ ������ ��� ���������� ����������
            Kafedra* kafPtr = headkafLoc;
            do
            {
                // �������� ������� ������ ��� �������
                if (kafPtr->idfac == facPtr->id && (criteria.kafedraid == 0 || kafPtr->idkaf == criteria.kafedraid))
                {
                    cout << " - �������: " << kafPtr->kafedra << endl;
                    // ����� ������ ������� ��� ��������� �������
                    CompClass* clPtr = headclassLoc;
                    do
                    {
                        // �������� ������� ������ ��� ������
                        if (clPtr->idkafed == kafPtr->idkaf && (criteria.classid == 0 || clPtr->idcla == criteria.classid))
                        {
                            cout << "   - �����: " << clPtr->comp_class << endl;

                            // ����� ������ ����������� ��� ���������� ������
                            Computer* compPtr = headcompLoc;
                            do
                            {
                                // �������� ������� ������ ��� ����������
                                if (compPtr->idclass == clPtr->idcla &&
                                    (criteria.type.empty() || compPtr->type == criteria.type) &&
                                    (criteria.snumber == 0 || compPtr->snumber == criteria.snumber) &&
                                    (criteria.year == 0 || compPtr->year == criteria.year) &&
                                    (criteria.status.empty() || compPtr->status == criteria.status) &&
                                    (criteria.maintence.empty() || compPtr->maintence == criteria.maintence))
                                {
                                    cout << "      - ���������: ���: " << compPtr->type << ", �������� �����: " << compPtr->snumber
                                        << ", ��� �������: " << compPtr->year << ", ������: " << compPtr->status
                                        << ", ������������: " << compPtr->maintence << endl;
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
    cout << "��������� � ID " << criteria.facultyid << " �� ������." << endl;
}

// ������� ����������� ����� �� ������ �����������
void MoveForwardFaculty(Faculty* head, int step)
{
    // �������� ������� ��������� � ������ �����������
    if (head == nullptr)
    {
        cout << "������ ����������� ����." << endl;
        return;
    }

    Faculty* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // �������� ���������� ����� ������
        if (current == head)
        {
            cout << "��������� ����� ������. ���������� ������������� ������." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t\t������ �����������\n\n";
    cout << "+---------------+------------------------------+\n";
    cout << "| ID ���������� |          ���������           |\n";
    cout << "+---------------+------------------------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->id << " | " << setw(28) << current->faculty << " |\n";
    cout << "+---------------+------------------------------+\n";
}

// ������� ����������� ����� �� ������ �����������
void MoveBackwardFaculty(Faculty* head, int step)
{
    // �������� ������� ��������� � ������ �����������
    if (head == nullptr)
    {
        cout << "������ ����������� ����." << endl;
        return;
    }

    Faculty* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // �������� ���������� ������ ������
        if (current == head)
        {
            cout << "��������� ������ ������. ���������� ������������� �����." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t\t������ �����������\n\n";
    cout << "+---------------+------------------------------+\n";
    cout << "| ID ���������� |          ���������           |\n";
    cout << "+---------------+------------------------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->id << " | " << setw(28) << current->faculty << " |\n";
    cout << "+---------------+------------------------------+\n";
}

// ������� ����������� ����� �� ������ ������
void MoveForwardKafedra(Kafedra* head, int step)
{
    // �������� ������� ��������� � ������ ������
    if (head == nullptr)
    {
        cout << "������ ������ ����." << endl;
        return;
    }

    Kafedra* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // �������� ���������� ����� ������
        if (current == head)
        {
            cout << "��������� ����� ������. ���������� ������������� ������." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t\t������ ������\n\n";
    cout << "+---------------+---------------+------------------------------+\n";
    cout << "| ID ���������� | ID �������    | �������                      |\n";
    cout << "+---------------+---------------+------------------------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->idfac << " | " << setw(13) << current->idkaf << " | " << setw(28) << current->kafedra << " |\n";
    cout << "+---------------+---------------+------------------------------+\n";
}

// ������� ����������� ����� �� ������ ������
void MoveBackwardKafedra(Kafedra* head, int step)
{
    // �������� ������� ��������� � ������ ������
    if (head == nullptr)
    {
        cout << "������ ������ ����." << endl;
        return;
    }

    Kafedra* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // �������� ���������� ������ ������
        if (current == head)
        {
            cout << "��������� ������ ������. ���������� ������������� �����." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t\t������ ������\n\n";
    cout << "+---------------+---------------+------------------------------+\n";
    cout << "| ID ���������� | ID �������    | �������                      |\n";
    cout << "+---------------+---------------+------------------------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->idfac << " | " << setw(13) << current->idkaf << " | " << setw(28) << current->kafedra << " |\n";
    cout << "+---------------+---------------+------------------------------+\n";
}

// ������� ����������� ����� �� ������ ������������ �������
void MoveForwardCompClass(CompClass* head, int step)
{
    // �������� ������� ��������� � ������ �������
    if (head == nullptr)
    {
        cout << "������ ������� ����." << endl;
        return;
    }

    CompClass* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // �������� ���������� ����� ������
        if (current == head)
        {
            cout << "��������� ����� ������. ���������� ������������� ������." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t������ ������������ �������\n\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
    cout << "| ID ���������� | ID �������    | ID ������     | ������������ �����           |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->idfacult << " | " << setw(13) << current->idkafed << " | " << setw(13) << current->idcla << " | " << setw(28) << current->comp_class << " |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
}

// ������� ����������� ����� �� ������ ������������ �������
void MoveBackwardCompClass(CompClass* head, int step)
{
    // �������� ������� ��������� � ������ �������
    if (head == nullptr)
    {
        cout << "������ ������� ����." << endl;
        return;
    }

    CompClass* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // �������� ���������� ������ ������
        if (current == head)
        {
            cout << "��������� ������ ������. ���������� ������������� �����." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t������ ������������ �������\n\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
    cout << "| ID ���������� | ID �������    | ID ������     | ������������ �����           |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->idfacult << " | " << setw(13) << current->idkafed << " | " << setw(13) << current->idcla << " | " << setw(28) << current->comp_class << " |\n";
    cout << "+---------------+---------------+---------------+------------------------------+\n";
}

// ������� ����������� ����� �� ������ �����������
void MoveForwardComputer(Computer* head, int step)
{
    // �������� ������� ��������� � ������ �����������
    if (head == nullptr)
    {
        cout << "������ ����������� ����." << endl;
        return;
    }

    Computer* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->next;

        // �������� ���������� ����� ������
        if (current == head)
        {
            cout << "��������� ����� ������. ���������� ������������� ������." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t\t������ �����������\n\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout << "| ID ���������� | ID �������    | ID ������     | ���           | �������� �����| ��� �������   | ������        | ������������  |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->idfaculty << " | " << setw(13) << current->idkafedra << " | " << setw(13) << current->idclass << " | "
        << setw(13) << current->type << " | " << setw(13) << current->snumber << " | " << setw(13) << current->year << " | "
        << setw(13) << current->status << " | " << setw(13) << current->maintence << " |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
}

// ������� ����������� ����� �� ������ �����������
void MoveBackwardComputer(Computer* head, int step)
{
    // �������� ������� ��������� � ������ �����������
    if (head == nullptr)
    {
        cout << "������ ����������� ����." << endl;
        return;
    }

    Computer* current = head;

    // ����������� ��������� ����� �� �������� ���������� �����
    for (int i = 0; i < step; ++i)
    {
        current = current->prev;

        // �������� ���������� ������ ������
        if (current == head)
        {
            cout << "��������� ������ ������. ���������� ������������� �����." << endl;
            return;
        }
    }

    // ����� ��������� �������
    cout << "\n\t\t\t������ �����������\n\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout << "| ID ���������� | ID �������    | ID ������     | ���           | �������� �����| ��� �������   | ������        | ������������  |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";

    // ����� ������ �������� ���� ������ � ���� ������ �������
    cout << "| " << setw(13) << current->idfaculty << " | " << setw(13) << current->idkafedra << " | " << setw(13) << current->idclass << " | "
        << setw(13) << current->type << " | " << setw(13) << current->snumber << " | " << setw(13) << current->year << " | "
        << setw(13) << current->status << " | " << setw(13) << current->maintence << " |\n";
    cout << "+---------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n";
}
