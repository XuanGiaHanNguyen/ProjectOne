#ifndef NODE_H
#define NODE_H

// Node struct for a doubly linked list
template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
};

#endif
