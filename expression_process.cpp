//
// Created by haoranx98 on 12/22/22.
//

#include "expression_process.h"
#include "TreeNode.h"
#include "iostream"

void eliminate_entailment_and_equivalence(TreeNode * &root) {
    if(root == nullptr){
        return;
    }else{
        if(root->symbol=='$'){
            TreeNode* node = new TreeNode('|');
            node->left = new TreeNode('!');
            node->right = root->right;
            node->left->left = new TreeNode('#');
            node->left->right = root->left;
            TreeNode* temp = root;
            root = node;
            delete temp;
            eliminate_entailment_and_equivalence(root -> left);
            eliminate_entailment_and_equivalence(root -> right);
        }else if(root->symbol == '='){
            TreeNode* node = copy_tree(root);
            TreeNode* new_root = new TreeNode('&');
            // !p | q
            new_root -> left = new TreeNode('|');
            new_root -> left -> left = new TreeNode('!');
            new_root -> left -> right = root -> right;
            new_root -> left -> left -> left = new TreeNode('#');
            new_root -> left -> left -> right = root -> left;
            // !q | p
            new_root -> right = new TreeNode('|');
            new_root -> right -> left = new TreeNode('!');
            new_root -> right -> right = node -> left;
            new_root -> right -> left -> left = new TreeNode('#');
            new_root -> right -> left -> right = node -> right;

            TreeNode* temp = root;
            root = new_root;
            delete temp;
            delete node;
            eliminate_entailment_and_equivalence(root -> left);
            eliminate_entailment_and_equivalence(root -> right);
        }else{
            eliminate_entailment_and_equivalence(root -> left);
            eliminate_entailment_and_equivalence(root -> right);
        }
    }
}

void eliminate_entailment_and_equivalence_for_syntax_tree(std::vector<TreeNode *> &syntax_tree){
    for (auto & i : syntax_tree) {
        eliminate_entailment_and_equivalence(i);
    }
}

TreeNode* eliminate_repeated_not(TreeNode* &root){
    if(root == nullptr){
        return nullptr;
    }else if((root -> symbol == '!' && root -> right != nullptr) && root -> right -> symbol == '!'){
        TreeNode* temp = root;
        root = root -> right -> right;
        temp -> right -> right = nullptr;
        delete_tree(temp);
        root = eliminate_repeated_not(root);
        return root;
    }else{
        root -> left = eliminate_repeated_not(root -> left);
        root -> right = eliminate_repeated_not(root -> right);
        return root;
    }
}

void elimnate_repeated_not_for_syntax_tree(std::vector<TreeNode *> &syntax_tree){
    for (auto & i : syntax_tree) {
        eliminate_repeated_not(i);
    }
}

TreeNode* de_morgan(TreeNode* &root){
    if (root == nullptr){
        return nullptr;
    }else{
        if (root -> symbol == '!' && root -> right != nullptr){
            if (root -> right -> symbol == '&' || root -> right -> symbol == '|'){
                TreeNode* temp = root;
                TreeNode* new_root = root -> right;
                TreeNode* new_root_left = new TreeNode('!');
                new_root_left -> left = new TreeNode('#');
                new_root_left -> right = new_root -> left;
                TreeNode* new_root_right = new TreeNode('!');
                new_root_right -> left = new TreeNode('#');
                new_root_right -> right = new_root -> right;
                new_root -> left = new_root_left;
                new_root -> right = new_root_right;
                if(new_root -> symbol == '&'){
                    new_root -> symbol = '|';
                }else{
                    new_root -> symbol = '&';
                }
                root = new_root;
                delete temp -> left;
                delete temp;

                root -> left = de_morgan(root -> left);
                root -> right = de_morgan(root -> right);

                return root;
            }else if(root -> right -> symbol == '!'){
                root = eliminate_repeated_not(root);
                return root;
            }else{
                root -> left = de_morgan(root -> left);
                root -> right = de_morgan(root -> right);
                return  root;
            }
        }else{
            root -> left = de_morgan(root -> left);
            root -> right = de_morgan(root -> right);
            return  root;
        }
    }
}

void de_morgan_for_syntax_tree(std::vector<TreeNode *> &syntax_tree){
    for(auto &node: syntax_tree){
        node = de_morgan(node);
    }
}

