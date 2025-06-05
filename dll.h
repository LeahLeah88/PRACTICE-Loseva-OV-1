// dll.h
#ifndef DLL_H
#define DLL_H

#include <iostream>
#include <string>
#include <stdexcept>//для исключений

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

    void removeNode(Node<T>* node);
    void copyFrom(const DoublyLinkedList& other);
    void clear();

public:
    DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    ~DoublyLinkedList();

    void insertAtEnd(const T& value);
    void removeLast();
    size_t getSize() const;

protected:
    Node<T>* getHead() const;

    template <typename U>
    friend class Stack;
};

// Интерфейс контейнера
template <typename T>
class IContainer {
public:
    virtual ~IContainer() {}
    virtual void add(const T& element) = 0;
    virtual void remove() = 0;
    virtual bool isEmpty() const = 0;
};

// Стек на основе двусвязного списка
template <typename T>
class Stack : public IContainer<T> {
private:
    DoublyLinkedList<T> list;

public:
    void add(const T& element) override;
    void remove() override;
    bool isEmpty() const;
protected:
    Node<T>* getHead() const;

    // Объявляем дружественной функцию
    friend std::string processBackspaces(const std::string& input);
};

// Объявление функции обработки строки
std::string processBackspaces(const std::string& input);

#endif // DLL_H
