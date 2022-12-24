//
// Created by haoranx98 on 12/22/22.
//

#ifndef MATHLOGIC_PREPROCESS_H
#include <vector>
#include <string>
#include "TreeNode.h"
#define MATHLOGIC_PREPROCESS_H


using namespace std;
bool isLetter(char i);

void read_input_file(string filename, vector<string> &formula_list);
void write_output_file(string filename, vector<string> three_CNF_list);
void handle_not_infix_formula_list(vector<string> pre_infix_formula_list, vector<string> &infix_formula_list);
void infix_to_polish_formula(vector<string> infix_formula_list, vector<string> &polish_formula_list);
void polish_formula_to_syntax_tree(vector<string> polish_formula_list, vector<TreeNode *> &syntax_tree);
#endif //MATHLOGIC_PREPROCESS_H
