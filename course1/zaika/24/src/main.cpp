#include "../include/ExpressionTree.hpp"
#include <iostream>
#include <cstring>

int main() {
    const char* infix = "4*a/2";
    std::cout << "Infix: " << infix << std::endl;
    ExpressionTree tree1;
    char* postfix = infixToPostfix(infix);
    std::cout << "Postfix: " << postfix << std::endl;

    tree1.build(postfix);
    std::cout << "Original Expression Tree: ";
    tree1.display();

    tree1.simplifyTree();
    std::cout << "Simplified Expression Tree: ";
    tree1.display();

    delete[] postfix;

    return 0;
}