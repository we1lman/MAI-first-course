#ifndef EXPRESSIONTREE_HPP
#define EXPRESSIONTREE_HPP

#include "ExpressionNode.hpp"
#include <iostream>
#include <cstring>

class ExpressionTree {
private:
    ExpressionNode* root;

    bool isNumber(const char* str) {
        for (size_t i = 0; str[i] != '\0'; ++i) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    void simplify(ExpressionNode* node) {
        if (!node) return;

        simplify(node->left);
        simplify(node->right);

        if (node->left && node->right && strcmp(node->value, "/") == 0) {
            bool leftIsNumber = isNumber(node->left->value);
            bool rightIsNumber = isNumber(node->right->value);

            if (strcmp(node->left->value, "*") == 0 && rightIsNumber) {
                int divisor = atoi(node->right->value);

                if (isNumber(node->left->left->value)) {
                    int multiplicand = atoi(node->left->left->value);

                    if (divisor != 0 && multiplicand % divisor == 0) {
                        int newValue = multiplicand / divisor;
                        delete[] node->value;
                        node->value = new char[2];
                        strcpy(node->value, "*");

                        delete[] node->left->left->value;
                        node->left->left->value = new char[20];
                        snprintf(node->left->left->value, 20, "%d", newValue);

                        delete node->right;
                        node->right = nullptr;
                    }
                }

                if (isNumber(node->left->right->value)) {
                    int multiplicand = atoi(node->left->right->value);

                    if (divisor != 0 && multiplicand % divisor == 0) {
                        int newValue = multiplicand / divisor;

                        delete[] node->value;
                        node->value = new char[2];
                        strcpy(node->value, "*");

                        delete[] node->left->right->value;
                        node->left->right->value = new char[20];
                        snprintf(node->left->right->value, 20, "%d", newValue);

                        delete node->right;
                        node->right = nullptr;
                    }
                }
            }
        }
    }

    void printInfix(ExpressionNode* node, bool isRoot = true) {
        if (!node) return;

        if (node->left) {
            bool needParens = (strcmp(node->value, "+") == 0 || strcmp(node->value, "-") == 0);
            if (needParens) std::cout << "(";
            printInfix(node->left, false);
            if (needParens) std::cout << ")";
        }

        std::cout << node->value;

        if (node->right) {
            bool needParens = (strcmp(node->value, "+") == 0 || strcmp(node->value, "-") == 0);
            if (needParens) std::cout << "(";
            printInfix(node->right, false);
            if (needParens) std::cout << ")";
        }

        if (isRoot && node->value && strcmp(node->value, "*") == 0) {
            std::cout << "\b \b";
        }
    }

public:
    ExpressionTree() : root(nullptr) {}
    ~ExpressionTree() {
        delete root;
    }

    void build(const char* postfix) {
        ExpressionNode* stack[100];
        int stackIndex = -1;
        const char* operators = "+-*/";

        for (size_t i = 0; i < strlen(postfix); ++i) {
            char ch = postfix[i];
            char value[2] = {ch, '\0'};
            if (strchr(operators, ch)) {
                ExpressionNode* right = stack[stackIndex--];
                ExpressionNode* left = stack[stackIndex--];
                ExpressionNode* node = new ExpressionNode(value);
                node->left = left;
                node->right = right;
                stack[++stackIndex] = node;
            } else {
                stack[++stackIndex] = new ExpressionNode(value);
            }
        }

        root = stack[stackIndex];
    }

    void simplifyTree() {
        simplify(root);
    }

    void display() {
        printInfix(root);
        std::cout << std::endl;
    }
};

int precedence(char op) {
    if(op == '+' || op == '-') {
        return 1;
    }
    if(op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

char* infixToPostfix(const char* infix) {
    char operators[100];
    int operatorsIndex = -1;
    char* postfix = new char[strlen(infix) + 1];
    int k = 0;

    for (size_t i = 0; i < strlen(infix); ++i) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            operators[++operatorsIndex] = c;
        } else if (c == ')') {
            while (operatorsIndex >= 0 && operators[operatorsIndex] != '(') {
                postfix[k++] = operators[operatorsIndex--];
            }
            operatorsIndex--;
        } else {
            while (operatorsIndex >= 0 && precedence(operators[operatorsIndex]) >= precedence(c)) {
                postfix[k++] = operators[operatorsIndex--];
            }
            operators[++operatorsIndex] = c;
        }
    }

    while (operatorsIndex >= 0) {
        postfix[k++] = operators[operatorsIndex--];
    }

    postfix[k] = '\0';
    return postfix;
}

#endif // EXPRESSIONTREE_HPP
