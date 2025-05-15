#include <iostream>
using namespace std;

// Структура узла списка
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
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
        current->next = new ListNode(arr[i]);
        current = current->next;
    }
    return head;
}

// Функция для освобождения памяти списка
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция, которая перемещает последний элемент списка после головы
void moveLastToSecond(ListNode* head) {
    if (!head || !head->next || !head->next->next) {
        // В списке меньше 3 элементов, ничего делать не нужно
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

    // Отделить последний узел
    prev->next = nullptr;

    // Вставить его после головы
    curr->next = head->next;
    head->next = curr;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int size = sizeof(arr) / sizeof(arr[0]);

    ListNode* head = createList(arr, size);

    cout << "Исходный список: ";
    printList(head);

    moveLastToSecond(head);

    cout << "После перемещения последнего элемента после головы: ";
    printList(head);

    deleteList(head);
    return 0;
}