//
// Created by haoranx98 on 12/22/22.
//

#include "preprocess.h"
#include <iostream>
#include "fstream"
#include "stack"
#include "queue"
#include "unordered_map"

using namespace std;

bool isLetter(char i) {
    bool result = false;
    if((i <= 'z' && i >= 'a') || i == '#'){
        result = true;
    }
    return result;
}

void read_input_file(string filename, vector<string> &infix_formula_list){
//    vector<string> formula_list;
    ifstream input_file;

    input_file.open(filename, ios::in);

    if(!input_file.is_open()){
        cout << "can not open this file" << endl;
    }
    else{
        string formula;
        while (getline(input_file, formula)){
            if(formula.empty()){
                continue;
            }
            infix_formula_list.push_back(formula);
        }
    }
    input_file.close();
}

void handle_not_infix_formula_list(vector<string> pre_infix_formula_list, vector<string> &infix_formula_list) {
    for(string pre_infix_formula: pre_infix_formula_list){
        string infix = pre_infix_formula;
        infix.insert(0, 1, '(');
        infix.push_back(')');
        int size = infix.size();
        for (int i = 0; i < size; ++i) {
            if(infix[i] == '!'){
                if (isLetter(infix[i+1])){
                    infix.insert(i,"(#");
                    i+=3;
                    size+=2;
                    infix.insert(i+1, ")");
                    cout << infix << endl;
                }else{
                    infix.insert(i,"(#");
                    i+=3;
                    size += 2;
                    int n = 0;
                    int pos = 0;
                    for(int j = i; j < size; j++){
//                    cout << infix[j] << " " << n << " " << pos << " " << infix[pos] << endl;
                        if(infix[j] == '('){
                            n++;
                        }else if(infix[j] == ')'){
                            n--;
                        if(n == 0){
                            pos = j;
//                            cout << "break: " << infix[j] << " " << n << " " << pos << " " << infix[pos] << endl;
                            break;
                        }
                        }else{
                            continue;
                        }
                    }
                    infix.insert(pos, ")");
//                    cout << infix << endl;
                }
            }
        }
        infix_formula_list.push_back(infix);
    }
}

void infix_to_polish_formula(vector<string> infix_formula_list, vector<string> &polish_formula_list) {
    for(string infix_formula: infix_formula_list){
        stack<char> result;
        stack<char> operators;
        queue<char> polish_queue;
        string polish_formula;

        for (char c: infix_formula){
            if (isLetter(c)){
                polish_queue.push(c);
            }else if(c == ')'){
                while (operators.top() != '('){
                    polish_queue.push(operators.top());
                    operators.pop();
                }
                if (operators.top() == '('){
                    operators.pop();
                }
            }else{
                operators.push(c);
            }
        }

        while (!polish_queue.empty()){
            polish_formula.push_back(polish_queue.front());
            polish_queue.pop();
        }

//        cout << polish_formula << endl;

        polish_formula_list.push_back(polish_formula);
    }
}

void polish_formula_to_syntax_tree(vector<string> polish_formula_list, vector<TreeNode *> &syntax_tree){
    for(string polish_formula: polish_formula_list){
        stack<TreeNode *> tree_node_stack;
        for(char c: polish_formula){
            TreeNode* node = new TreeNode(c);
            if (isLetter(c)){
                tree_node_stack.push(node);
            }else{
                node->right = tree_node_stack.top();
                tree_node_stack.pop();
                node->left = tree_node_stack.top();
                tree_node_stack.pop();
                tree_node_stack.push(node);
            }
        }
        syntax_tree.push_back(tree_node_stack.top());
        tree_node_stack.pop();
    }
}
