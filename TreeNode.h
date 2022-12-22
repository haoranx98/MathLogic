//
// Created by haoranx98 on 12/22/22.
//

#ifndef MATHLOGIC_TREENODE_H
#define MATHLOGIC_TREENODE_H

class TreeNode {
    public:
        TreeNode();
        TreeNode(char c);

        char symbol;
        bool isOperator;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
};

TreeNode* copy_tree(TreeNode *root);
void inorder_traversal(TreeNode *root);
void delete_tree(TreeNode* &root);
#endif //MATHLOGIC_TREENODE_H
