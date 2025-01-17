#include "list.hpp"

LinkedList::LinkedList() {
    barrier = new Node('\0');
    barrier->next = nullptr;
}

LinkedList::~LinkedList() {
    Node* current = barrier;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::printList() const {
    Node* current = barrier->next;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void LinkedList::insert(char data) {
    Node* newNode = new Node(data);
    newNode->next = barrier->next;
    barrier->next = newNode;
}

void LinkedList::remove(char data) {
    Node* current = barrier;
    while (current->next != nullptr && current->next->data != data) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

int LinkedList::getLength() const {
    int length = 0;
    Node* current = barrier->next;
    while (current != nullptr) {
        length += 1;
        current = current->next;
    }
    return length;
}

void LinkedList::swapSecondAndPenultimate() {
    if (barrier->next == nullptr || barrier->next->next == nullptr) {
        return;
    }

    Node* first = barrier->next;
    Node* second = barrier->next->next;
    Node* penultimate = nullptr;
    Node* penultimatePrev = nullptr;
    Node* current = barrier->next;

    while (current->next != nullptr) {
        penultimatePrev = penultimate;
        penultimate = current;
        current = current->next;
    }

    if (second->next == penultimate) {
        first->next = penultimate;
        second->next = penultimate->next;
        penultimate->next = second;
    } else {
        first->next = penultimate;
        penultimatePrev->next = second;
        Node* temp = second->next;
        second->next = penultimate->next;
        penultimate->next = temp;
    }
}

