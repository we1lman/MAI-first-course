#include "List.hpp"
#include <iostream>

int main() {
    LinkedList list;

    list.insert('f');
    list.insert('e');
    list.insert('d');
    list.insert('c');
    list.insert('b');
    list.insert('a');

    std::cout << "Initial list: ";
    list.printList();

    std::cout << "Lenght of list: " << list.getLength() << std::endl;

    list.remove('c');
    std::cout << "List after removing 'c': ";
    list.printList();

    list.swapSecondAndPenultimate();
    std::cout << "List after exchanging 2nd and penultimate elements: ";
    list.printList();

    return 0;
}
