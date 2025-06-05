// dll.cpp
#include "dll.h"
#include <fstream>

// Реализация методов DoublyLinkedList
template <typename T>
void DoublyLinkedList<T>::removeNode(Node<T>* node) {
    if (node == nullptr)
        return;
    if (node == head)
        head = node->next;
    if (node == tail)
        tail = node->prev;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    delete node;
    --size;
}

template <typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList& other) {
    Node<T>* current = other.head;
    while (current != nullptr) {
        insertAtEnd(current->data);
        current = current->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    copyFrom(other);
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::insertAtEnd(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

template <typename T>
void DoublyLinkedList<T>::removeLast() {
    if (tail != nullptr) {
        removeNode(tail);
    }
}

template <typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
}

template <typename T>
Node<T>* DoublyLinkedList<T>::getHead() const {
    return head;
}

// Реализация методов Stack
template <typename T>
void Stack<T>::add(const T& element) {
    list.insertAtEnd(element);
}

template <typename T>
void Stack<T>::remove() {
    if (list.getSize() == 0)
        throw std::underflow_error("Попытка удалить элемент из пустого стека");
    list.removeLast();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return list.getSize() == 0;
}

template <typename T>
Node<T>* Stack<T>::getHead() const {
    return list.getHead();
}

// Обработка строки с учетом символа #
std::string processBackspaces(const std::string& input) {
    Stack<char> stack;

    for (char ch : input) {
        if (ch == '#') {
            try {
                stack.remove();
            }
            catch (const std::underflow_error& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
        }
        else {
            stack.add(ch);
        }
    }

    // Собираем результат из стека
    std::string result;
    Node<char>* current = stack.getHead();
    while (current != nullptr) {
        result += current->data;
        current = current->next;
    }
    return result;
}

// Основная программа
int main() {
    system("chcp 1251>nul");
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Не удалось открыть файл input.txt";
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::string processed = processBackspaces(line);
        std::cout << processed << std::endl;
    }

    infile.close();
    return 0;
}
