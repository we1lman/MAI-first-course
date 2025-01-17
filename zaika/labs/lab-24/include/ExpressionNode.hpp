#ifndef EXPRESSIONNODE_HPP
#define EXPRESSIONNODE_HPP

#include <iostream>
#include <cstring>

class ExpressionNode {
public:
    char* value;
    ExpressionNode* left;
    ExpressionNode* right;

    ExpressionNode(const char* val) : left(nullptr), right(nullptr) {
        value = new char[strlen(val) + 1];
        strcpy(value, val);
    }

    ~ExpressionNode() {
        delete[] value;
        delete left;
        delete right;
    }
};

#endif // EXPRESSIONNODE_HPP
