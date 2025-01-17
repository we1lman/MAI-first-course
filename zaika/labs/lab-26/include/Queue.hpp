#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

struct Node {
    int data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void pushQueue(int value) {
        Node* newNode = new Node{value, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void moveElement() {
        if (front == nullptr || front->next == nullptr) return;

        Node* prev = front;
        Node* current = front->next;
        Node* smallestPrev = nullptr;
        Node* smallest = nullptr;

        while (current != nullptr) {
            if (current->data < prev->data) {
                smallestPrev = prev;
                smallest = current;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (smallest != nullptr) {
            if (smallestPrev != nullptr) {
                smallestPrev->next = smallest->next;
                if (smallest == rear) {
                    rear = smallestPrev;
                }
            }

            smallest->next = front;
            front = smallest;
        }
    }

    void printQueue() const {
        Node* current = front;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif // QUEUE_HPP
