//
// Created by haoranx98 on 12/22/22.
//

#include "TreeNode.h"
#include "iostream"
#include "queue"

TreeNode::TreeNode()
{
    this->isOperator = false;
}

TreeNode::TreeNode(char c)
{
    this->symbol = c;
    if((c >= 'a' && c <= 'z') || c == '#'){
        this->isOperator = false;
    }
    else{
        this->isOperator= true;
    }
}

TreeNode *copy_tree(TreeNode *root) {

    TreeNode *node = nullptr;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    if(root != nullptr){
        if(root->left != nullptr){
            left = copy_tree(root->left);
        }else{
            left = nullptr;
        }

        if(root->right != nullptr){
            right = copy_tree(root->right);
        } else{
            right = nullptr;
        }
        node = new TreeNode(*root);
        node->left = left;
        node->right = right;
    }
    return node;
}

void inorder_traversal(TreeNode *root) {
    if(root != nullptr){
        inorder_traversal(root->left);
        std::cout << root->symbol;
        inorder_traversal(root->right);
    }
}

void delete_tree(TreeNode* &root)
{
        // empty tree
        if (root == nullptr) {
                return;
        }

        // create an empty queue and enqueue the root node
        std::queue<TreeNode*> queue;
        queue.push(root);

        TreeNode* front = nullptr;

        // loop till queue is empty
        while (!queue.empty())
        {
                // delete each node in the queue one by one after pushing their
                // non-empty left and right child to the queue
                front = queue.front();
                queue.pop();

                if (front->left) {
                        queue.push(front->left);
                }

                if (front->right) {
                        queue.push(front->right);
                }

                // it is important to delete the front node ONLY after enqueuing its children
                delete front;
        }

        // set root as null before returning
        root = nullptr;
}
