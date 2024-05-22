#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.hpp"
#include <iostream>

const int INT_MAX = 2147483647;

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void findMinLeaf(TreeNode* node, int& minLeaf) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            if (node->value < minLeaf) minLeaf = node->value;
            return;
        }
        findMinLeaf(node->left, minLeaf);
        findMinLeaf(node->right, minLeaf);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void inorderPrint(TreeNode* node, int level = 0) const {
        if (node != nullptr) {
            for (int i = 0; i < level; i++) {
                std::cout << "  ";
            }
            std::cout << node->value << std::endl;
            inorderPrint(node->left, level + 1);
            inorderPrint(node->right, level + 1);
        }
    }

    void printTree() {
        inorderPrint(root);
        std::cout << std::endl;
    }

    int getMinLeaf() {
        int minLeaf = INT_MAX;
        findMinLeaf(root, minLeaf);
        return minLeaf;
    }
};

#endif // BINARYSEARCHTREE_H
