#ifndef TREENODE_HPP
#define TREENODE_HPP

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

#endif // TREENODE_HPP
