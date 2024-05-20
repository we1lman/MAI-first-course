#include "../include/Queue.hpp"
#include <iostream>

int main() {
    Queue q;
    q.pushQueue(1);
    q.pushQueue(3);
    q.pushQueue(8);
    q.pushQueue(6);
    q.pushQueue(2);

    std::cout << "Initial queue: ";
    q.printQueue();

    q.moveElement();

    std::cout << "Modified queue: ";
    q.printQueue();

    return 0;
}
