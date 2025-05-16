#include <iostream>
using namespace std;

// Структура узла списка
struct ListNode {
    int val;
    ListNode* next;
};

// Функция для вывода списка
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

// Функция для создания списка из массива
ListNode* createList(const int* arr, int size) {
    if (size == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    for (int i = 1; i < size; ++i) {
        ListNode<T>* newNode = new ListNode<T>;
        newNode->val = arr[i];
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }
    return head;
}

// Функция для освобождения памяти списка
template <typename T>
void deleteList(ListNode<T>* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция, которая перемещает последний элемент списка после головы
void moveLastToSecond(ListNode* head) {
    if (!head || !head->next || !head->next->next) {
        return;
    }

    // Найти предпоследний и последний узлы
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    // curr - последний узел
    // prev - предпоследний узел
    prev->next = nullptr;
    curr->next = head->next;
    head->next = curr;
}

int main() {
    setlocale(LC_ALL, "Russian");

    ListNode* head = createList(arr, size);

    cout << "Исходный список: ";
    printList(head);

    moveLastToSecond(head);

    cout << "После перемещения последнего элемента после головы: ";
    printList(head);

    return 0;
}