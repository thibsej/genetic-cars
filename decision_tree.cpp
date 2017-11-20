#include <vector>
#include <utility>
#include <math.h>
#include <limits>
#include <iostream>
#include "decision_tree.h"

using namespace std;

decision_tree::decision_tree(decision_tree* mummy, decision_tree_cell c): cell(c){

  this->right = NULL;
  this->left = NULL;
  this->mother = mummy;
}

decision_tree::decision_tree(decision_tree* mummy, decision_tree_cell c, decision_tree* l, decision_tree* r): cell(c){

  this->right = r;
  this->left = l;
  this->mother = mummy;
}
