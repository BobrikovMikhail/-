// 11 лаба гг.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
using namespace std;

// Структура узла списка
struct Node {
    int data;     // Данные узла - строка символов
    Node* next;     // Указатель на следующий элемент
};

// Функция для создания узла списка
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}

// Функция для создания списка
Node* createList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int n;
    cout << "Введите число узлов: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        //Вариант 1: ручное заполнение списка
        //int data;
        //cout << "Введите значение узла " << i << ": ";
        //cin >> data;
        //Node* newNode = createNode(data); // значение для элемента вводится с клав-ры

        //Вариант 2: автоматическое заполнение списка
        Node* newNode = createNode(i); // значение для элемента берется из i

        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }
    return head;
}

// Функция для печати списка
void printList(Node* head) {
    if (head == nullptr) {
        cout << "Список пуст" << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Функция для удаления заданного количества элементов, начиная с заданного номера
void deleteNodes(Node*& head, int index, int number) {
    Node* current = head;
    for (int i = 1; i < index - 1; i++) {
        current = current->next;
        if (current->next == nullptr) {
            cout << "Элемента с таким номером нет в списке" << endl;
            return;
        }
    }
    if (index != 1) { // Если заданный номер не равен 1
        Node* next = current;
        for (int i = 1; i <= number; i++) {
            if (current->next != nullptr) {
                next = current->next;
            }
            current->next = next->next;
            delete next;
        }
    }
    else {
        for (int i = 1; i <= number; i++) {
            if (current != nullptr) {
                current = current->next;
                head = current;
            }
        }
    }
}

// Функция для добавления элемента перед элементом с заданным ключом
void addNode(Node*& head, int key) {
    Node* current = head;
    Node* prev = NULL;
    while (current != nullptr) {
        if (current->data == key) {
            int NewKey;
            cout << "Введите значение нового элемента: ";
            cin >> NewKey;
            Node* newNode = createNode(NewKey);
            if (prev != NULL) {
                prev->next = newNode;
            }
            else {
                head = newNode;
            }
            newNode->next = current;
        }
        prev = current;
        current = current->next;
    }
}

// Функция для уничтожения списка
void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция для сохранения списка в файл
void SaveList(Node* head) {
    Node* current = head;
    char FName[] = "list.txt"; //Путь к файлу
    ofstream f1(FName, ios_base::out | ios_base::binary);   // открываем файл для записи
    while (current != nullptr) {
        f1.write((char*)current, sizeof(Node));   /*записываем структуру в файл*/
        current = current->next;
    }
    f1.close();     // закрываем файл
}

// Функция для чтения списка из файла
Node* LoadList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    Node current;
    char FName[] = "list.txt"; //Путь к файлу
    ifstream f2(FName);  // открываю файл для чтения
    if (!f2) {
        cout << "Файл не существует\n\n";
        f2.close();
        return nullptr;
    }
    f2.seekg(0, ios::end);      //функция перехода в конец файла
    long NumBytes = (long)f2.tellg();  //выяснение кол-ва байтов в файле
    float NumStruct = NumBytes / sizeof(Node);  //выяснение кол-ва структур в файле
    f2.seekg(0, ios::beg);      //переход в начало файла
    for (int i = 1; i <= NumStruct; i++) {
        f2.read((char*)&current, sizeof(Node));  // запись структуры из файла в переменную current
        Node* newNode = createNode(current.data);
        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }
    f2.close();
    return head;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "ru");
    cout << "Создание списка" << endl;
    Node* head = createList();
    printList(head);

    cout << "Добавление элемента перед элементом с заданным ключом" << endl;
    int key;
    cout << "Введите ключ, перед которым необходимо добавить элемент: ";
    cin >> key;
    addNode(head, key);
    printList(head);

    cout << "Удаление заданного количества элементов, начиная с заданного номера" << endl;
    int index;
    cout << "Введите номер первого удаляемого элемента: ";
    cin >> index;
    int number;
    cout << "Введите количество удаляемых элементов: ";
    cin >> number;
    deleteNodes(head, index, number);
    printList(head);

    cout << "Сохранение списка в файл" << endl;
    SaveList(head);
    printList(head);

    cout << "Уничтожение списка" << endl;
    deleteList(head);
    printList(head);

    cout << "Восстановление списка из файла" << endl;
    head = LoadList();
    printList(head);

    cout << "Уничтожение списка" << endl;
    deleteList(head);
    printList(head);

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
