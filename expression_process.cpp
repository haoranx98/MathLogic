//
// Created by haoranx98 on 12/22/22.
//

#include "expression_process.h"
#include "TreeNode.h"
#include "iostream"

using namespace std;

void eliminate_entailment_and_equivalence(TreeNode * &root) {
    if(root == nullptr){
        return;or_and_distributive_law(root -> left);
                or_and_distributive_law(root -> right);
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

void eliminate_entailment_and_equivalence(std::vector<TreeNode *> &syntax_tree){
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

bool is_constant(TreeNode *root){
    bool result = false;
    if(root -> symbol == '#' || root -> symbol == '!' || (root -> symbol <= 'z' && root -> symbol >= 'a') || (root->symbol <= 'Z' && root->symbol >= 'A')){
        result = true;
    }

    return result;
}

TreeNode* syntax_tree_to_another(TreeNode* root){
    vector<TreeNode *> clause_node_list;
    vector<TreeNode *> clause_node_pointer_list;
    vector<TreeNode *> clause_list;
    vector<TreeNode *> eliminate_entailment_and_equivalence_clause_list;
    TreeNode *equ_operator = nullptr;
    TreeNode *left_of_equ = nullptr;
    TreeNode *right_of_equ = nullptr;
    TreeNode *left_of_right_of_equ = nullptr;
    TreeNode *right_of_right_of_equ = nullptr;
    TreeNode *first_clause_node = nullptr;
    TreeNode *temp = nullptr;
    int j = 0;
    if(!is_constant(root)){
        first_clause_node = new TreeNode('A');
        clause_node_list.push_back(first_clause_node);
        clause_node_pointer_list.push_back(root);
        while(j < clause_node_list.size()){
            equ_operator = new TreeNode('=');
            left_of_equ = clause_node_list[j];
            right_of_equ = new TreeNode(root -> symbol);
            if(is_constant(root -> left)){
                left_of_right_of_equ = copy_tree(root -> left);

                if(is_constant(root -> right)){
                    right_of_right_of_equ = copy_tree(root -> right);
                }else{
                    TreeNode *new_clause_node = new TreeNode('A' + clause_node_list.size());
                    clause_node_list.push_back(new_clause_node);
                    clause_node_pointer_list.push_back(root -> right);
                    right_of_right_of_equ = new_clause_node;
                }
            }else{
                TreeNode *new_left_clause_node = new TreeNode('A' + clause_node_list.size());
                clause_node_list.push_back(new_left_clause_node);
                clause_node_pointer_list.push_back(root -> left);
                left_of_right_of_equ = new_left_clause_node;

                if(is_constant(root->right)){
                    right_of_right_of_equ = copy_tree(root -> right);
                }else{
                    TreeNode *new_right_clause_node = new TreeNode('A' + clause_node_list.size());
                    clause_node_list.push_back(new_right_clause_node);
                    clause_node_pointer_list.push_back(root -> right);
                    right_of_right_of_equ = new_right_clause_node;
                }
            }
            equ_operator -> left = left_of_equ;
            right_of_equ -> left = left_of_right_of_equ;
            right_of_equ -> right = right_of_right_of_equ;
            equ_operator -> right = right_of_equ;
            clause_list.push_back(equ_operator);
            if(j + 1 < clause_node_list.size()){
                root = clause_node_pointer_list[j+1];
            }
            j++;

        }

        eliminate_entailment_and_equivalence(clause_list);
        de_morgan_for_syntax_tree(clause_list);

        TreeNode *new_root = new TreeNode('&');
        new_root -> left = new TreeNode(first_clause_node -> symbol);
        for(auto clause: clause_list){
            new_root->right = clause;
            temp = new_root;
            new_root = new TreeNode('&');
            new_root -> left = temp;
        }
        root = new_root;
    }
    return root;
}

void syntax_tree_to_another_for_syntax_tree(std::vector<TreeNode *> &syntax_tree){
    for(auto & i : syntax_tree){
        i = syntax_tree_to_another(i);
    }
}

void or_and_distributive_law(TreeNode * &root){
    if(root == nullptr || is_constant(root)){
        return;
    }else{
        if(root -> symbol == '&'){
            or_and_distributive_law(root -> left);
            or_and_distributive_law(root -> right);
        }else {
            if(root -> left -> symbol == '&' && root -> right -> symbol == '&'){
                root -> symbol = '&';
                TreeNode* new_left = new TreeNode('|');
                TreeNode* new_right = new TreeNode('|');
                new_left -> left = root -> left -> left;
                new_left -> right = root -> right;
                new_right -> left = root -> left -> right;
                new_right -> right = copy_tree(root -> right);

                delete root -> left;

                root -> left = new_left;
                root -> right = new_right;

                or_and_distributive_law(root -> left);
                or_and_distributive_law(root -> right);
            }else if(root -> left -> symbol == '&'){
                TreeNode* temp = root -> right;
                root -> right = root -> left;
                root -> left = temp;
                or_and_distributive_law(root);
            }else if(root -> right -> symbol == '&'){
                root -> symbol = '&';
                TreeNode* new_left = new TreeNode('|');
                TreeNode* new_right = new TreeNode('|');
                new_left -> left = root -> left;
                new_left -> right = root -> right -> left;
                new_right -> left = copy_tree(root -> left);
                new_right -> right = root -> right -> right;
                delete root -> right;
                root -> left = new_left;
                root -> right = new_right;

                or_and_distributive_law(root -> left);
                or_and_distributive_law(root -> right);
            }else{
                return;
            }
        }
    }
}

void or_and_distributive_law(std::vector<TreeNode *> &syntax_tree){
    for(auto &node: syntax_tree){
        or_and_distributive_law(node);
    }
}
