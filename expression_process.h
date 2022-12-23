//
// Created by haoranx98 on 12/22/22.
//

#ifndef MATHLOGIC_EXPRESSION_PROCESS_H
#include "TreeNode.h"
#include "vector"
#define MATHLOGIC_EXPRESSION_PROCESS_H
bool is_constant(TreeNode *root);
void eliminate_entailment_and_equivalence(TreeNode* &root);
void eliminate_entailment_and_equivalence_for_syntax_tree(std::vector<TreeNode *> &syntax_tree);
TreeNode* eliminate_repeated_not(TreeNode* &root);
void elimnate_repeated_not_for_syntax_tree(std::vector<TreeNode *> &syntax_tree);
TreeNode* de_morgan(TreeNode* &root);
void de_morgan_for_syntax_tree(std::vector<TreeNode *> &syntax_tree);
TreeNode* syntax_tree_to_another(TreeNode* root);
void syntax_tree_to_another_for_syntax_tree(std::vector<TreeNode *> &syntax_tree);
void or_and_distributive_law(TreeNode * &root);
void or_and_distributive_law_for_syntax_tree(std::vector<TreeNode *> &syntax_tree);
#endif //MATHLOGIC_EXPRESSION_PROCESS_H
