#include <iostream>
#include "string"
#include "vector"
#include "queue"
#include "TreeNode.h"
#include "preprocess.h"
#include "expression_process.h"

using namespace std;

TreeNode* syntax_tree_to_another(TreeNode* root);
int main() {
    string input_filename = "../file/input.txt";
    string output_filename = "../file/output.txt";
    vector<string> pre_infix_formula_list;
    vector<string> infix_formula_list;
    vector<string> polish_formula_list;
    vector<TreeNode*> syntax_tree;
    vector<TreeNode*> another_syntax_tree;
    vector<string> three_CNF_list;

    read_input_file(input_filename, pre_infix_formula_list);
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

    eliminate_entailment_and_equivalence(syntax_tree);

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
    syntax_tree_to_another_for_syntax_tree(syntax_tree);
    for (auto node: syntax_tree) {
        inorder_traversal(node);
        cout << endl;
    }

    cout << "or and distribute:" << endl;
    or_and_distributive_law(syntax_tree);
    for (TreeNode *node: syntax_tree){
        inorder_traversal(node);
        cout << endl;
    }

    cout << "result:" << endl;
//    cout << syntax_tree_to_string(syntax_tree[0]) << endl;
    syntax_tree_to_string_for_every_syntax_tree(syntax_tree, three_CNF_list);
    for(auto three_CNF: three_CNF_list){
        cout << three_CNF << endl;
    }

    write_output_file(output_filename, three_CNF_list);

    return 0;
}


















