#include <iostream>
#include "string"
#include "vector"
#include "queue"
#include "TreeNode.h"
#include "preprocess.h"
#include "expression_process.h"

using namespace std;

bool is_constant(TreeNode *root);

int main() {
    string filename = "../file/input.txt";
    vector<string> pre_infix_formula_list;
    vector<string> infix_formula_list;
    vector<string> polish_formula_list;
    vector<TreeNode*> syntax_tree;
    vector<TreeNode*> another_syntax_tree;

    read_input_file(filename, pre_infix_formula_list);
    handle_not_infix_formula_list(pre_infix_formula_list, infix_formula_list);
    infix_to_polish_formula(infix_formula_list, polish_formula_list);
    for (string infix_formula: infix_formula_list){
        cout << infix_formula << endl;
    }

    for(string polish: polish_formula_list){
        cout << polish << endl;
    }

    polish_formula_to_syntax_tree(polish_formula_list, syntax_tree);

    for (TreeNode *node: syntax_tree){
        inorder_traversal(node);
        cout << endl;
    }

    cout << "eliminate: " << endl;

    eliminate_entailment_and_equivalence_for_syntax_tree(syntax_tree);

    for(auto node: syntax_tree){
        inorder_traversal(node);
        cout << endl;
    }


    cout << "de morgan:" << endl;
    de_morgan_for_syntax_tree(syntax_tree);
    for (auto node: syntax_tree){
        inorder_traversal(node);
        cout << endl;
    }

    cout << "transfer to another tree:" << endl;



    return 0;
}

bool is_constant(TreeNode *root){
    bool result = false;
    if(root -> symbol == '!' || (root -> symbol <= 'z' && root -> symbol >= 'a')){
        result = true;
    }

    return result;
}

TreeNode* syntax_tree_to_another(TreeNode* root){
    vector<TreeNode *> t_node_queue;
    vector<TreeNode *> equivalence_list;
    int i = 1;
    int j = 0;

    if(root == nullptr || root -> symbol == '!' || (root -> symbol <= 'z' && root -> symbol >= 'a')){
        return root;
    }else{
        t_node_queue.push_back(root);
        while (j < t_node_queue.size()){
            root = t_node_queue[j];
            TreeNode* left_of_equ = new TreeNode('A' + j);
            TreeNode* equ = new TreeNode('=');
            TreeNode* operator_of_right_equ = new TreeNode(root->symbol);

            if(is_constant(root -> left)){
                operator_of_right_equ -> left = copy_tree(root -> left);

                if(is_constant(root -> right)){
                    operator_of_right_equ -> right = copy_tree((root -> right));
                }else{
                    t_node_queue.push_back(root -> right);
                    TreeNode* right_of_right_equ = new TreeNode('A' + t_node_queue.size() - 1);
                    operator_of_right_equ -> right = right_of_right_equ;
                }
            }else{
                t_node_queue.push_back(root -> left);
                TreeNode* left_of_right_equ = new TreeNode('A' + t_node_queue.size() - 1);
                operator_of_right_equ -> left = left_of_right_equ;
                if(is_constant(root -> right)){
                    operator_of_right_equ -> right = copy_tree(root -> right);
                }else{
                    t_node_queue.push_back(root -> right);
                    TreeNode* right_of_right_equ = new TreeNode('A' + t_node_queue.size() - 1);
                    operator_of_right_equ -> right = right_of_right_equ;
                }
            }

            equ -> left = left_of_equ;
            equ -> right = operator_of_right_equ;
            equivalence_list[j] = equ;
            j++;
        }


        TreeNode* symbol_and = new TreeNode('&');
        TreeNode* new_root = symbol_and;
        for (int i = 1; i < equivalence_list.size(); i++){
            symbol_and->right = equivalence_list[i];

        }

    }
}















