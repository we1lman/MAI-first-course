#include "../include/BinarySearchTree.hpp"
#include <iostream>

int main() {
    BinarySearchTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    tree.insert(15); // leaf
    tree.insert(35); // leaf
    tree.insert(55); // leaf
    tree.insert(75); // leaf

    int minLeafValue = tree.getMinLeaf();
    std::cout << minLeafValue << std::endl;

    tree.printTree();

    return 0;
}