#include <iostream>
#include <chrono> 
using namespace std;
using namespace std::chrono;

// Обобщенная структура узла списка с шаблонами
template <typename T>
struct ListNode {
    T val;
    ListNode* next;
};

// Функция для вывода списка
template <typename T>
void reorderList(ListNode<T>* head) {
    ListNode<T>* curr = head;
    while (curr) {
        cout << curr->val;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << endl;
}

// Функция для создания списка из массива
template <typename T>
ListNode<T>* createList(const T* arr, int size) {
    if (size == 0) return nullptr;
    ListNode<T>* head = new ListNode<T>;
    head->val = arr[0];
    head->next = nullptr;
    ListNode<T>* current = head;
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
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

// Перемещение последнего элемента после головы
template <typename T>
void moveLastToSecond(ListNode<T>* head) {
    if (!head || !head->next || !head->next->next) {
        return;
    }
    ListNode<T>* prev = nullptr;
    ListNode<T>* curr = head;
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

// Удаление элемента по индексу
template <typename T>
void deleteAtIndex(ListNode<T>*& head, int index) {
    if (!head || index < 0) return;
    if (index == 0) {
        ListNode<T>* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    ListNode<T>* current = head;
    for (int i = 0; current != nullptr && i < index - 1; ++i) {
        current = current->next;
    }
    if (current == nullptr || current->next == nullptr) return;
    ListNode<T>* temp = current->next;
    current->next = temp->next;
    delete temp;
}

// Функция для выполнения тестового набора
template <typename T>
void runTestSet(const T* arr, int size, int deleteIdx) {
    auto start_time = high_resolution_clock::now();

    ListNode<T>* head = createList(arr, size);
    cout << "Создан список: ";
    reorderList(head);

    moveLastToSecond(head);
    cout << "После перемещения последнего элемента после головы: ";
    reorderList(head);

    deleteAtIndex(head, deleteIdx);
    cout << "После удаления элемента с индексом " << deleteIdx << ": ";
    reorderList(head);

    // Удаление головы
    deleteAtIndex(head, 0);
    cout << "После удаления головы: ";
    reorderList(head);

    // Удаление последнего элемента
    int length = 0;
    ListNode<T>* temp = head;
    while (temp) {
        ++length;
        temp = temp->next;
    }
    if (length > 0) {
        deleteAtIndex(head, length - 1);
        cout << "После удаления последнего элемента: ";
        reorderList(head);
    }

    deleteList(head);
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Время выполнения: " << duration.count() << " миллисекунд.\n";
    cout << "------------------------------\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Первый набор данных
    int arr1[] = { 1, 2, 3, 4, 5 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Тест 1:\n";
    runTestSet(arr1, size1, 2); // удаляем элемент с индексом 2

    // Второй набор данных: массив с отрицательными и нулевыми значениями
    double arr2[] = { 0.0, -1.5, 3.14, 0.0, -2.71 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Тест 2:\n";
    runTestSet(arr2, size2, 1); // удаляем элемент с индексом 1

    // Третий набор: длинный список
    int arr3[20];
    for (int i = 0; i < 20; ++i) arr3[i] = i * 2;
    cout << "Тест 3:\n";
    runTestSet(arr3, 20, 10); // удаляем элемент с индексом 10

    // Четвертый набор: очень короткий список (2 элемента)
    int arr4[] = { 42, 99 };
    int size4 = sizeof(arr4) / sizeof(arr4[0]);
    cout << "Тест 4:\n";
    runTestSet(arr4, size4, 1); // удаляем второй элемент

    // Пятый набор: список из одного элемента
    int arr5[] = { 123 };
    int size5 = sizeof(arr5) / sizeof(arr5[0]);
    cout << "Тест 5:\n";
    runTestSet(arr5, size5, 0); // удаляем единственный элемент

    return 0;
}