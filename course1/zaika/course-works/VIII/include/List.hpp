#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

struct Node {
    char data;
    Node* next;
    Node(char d) : data(d), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void printList() const;
    void insert(char data);
    void remove(char data);
    int getLength() const;
    void swapSecondAndPenultimate();

private:
    Node* barrier;
};

#endif // LIST_HPP
