#include <iostream>
#include <fstream>
#include <string>

// Узел двусвязного списка
template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

// Шаблон класса двусвязного списка
template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

    void copyFrom(const DoublyLinkedList& other) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            insertAtEnd(current->data);
            current = current->next;
        }
    }

    void clear() {
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

public:
    // Конструктор
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Конструктор копирования
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        copyFrom(other);
    }

    // Оператор присваивания
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Деструктор
    ~DoublyLinkedList() {
        clear();
    }

    void insertAtEnd(const T& value) {
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

    void remove(Node<T>* node) {
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

    size_t getSize() const {
        return size;
    }

    Node<T>* getHead() const {
        return head;
    }
};

// Интерфейс контейнера
template <typename T>
class IContainer {
public:
    virtual ~IContainer() {}

    virtual void add(const T& element) = 0;
    virtual void remove() = 0; // Удаляет элемент (например, первый или последний)
    virtual bool isEmpty() const = 0;
};

// Стек на основе двусвязного списка
template <typename T>
class Stack : public IContainer<T> {
private:
    DoublyLinkedList<T> list;

public:
    Node<T>* getHead() const {
        return list.getHead();
    }

    void add(const T& element) override {
        list.insertAtEnd(element);
    }

    void remove() override {
        if (!list.getSize())
            return;
        // Удаляем последний добавленный элемент (стек LIFO)
        Node<T>* current = list.getHead();
        while (current->next != nullptr)
            current = current->next;
        list.remove(current);
    }

    bool isEmpty() const override {
        return list.getSize() == 0;
    }
};


// Обработка строки с учетом символа #
std::string processBackspaces(const std::string& input) {
    Stack<char> stack;

    for (char ch : input) {
        if (ch == '#') {
            stack.remove();
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

// Основная программа для чтения файла и обработки строк
int main() {
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
