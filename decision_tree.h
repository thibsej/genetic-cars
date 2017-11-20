#include <vector>
#include<utility>
#include "car.h"
#include "decision_tree_cell.h"
using namespace std;

class decision_tree{
public:
  decision_tree_cell cell;
  decision_tree* right;
  decision_tree* left;
  decision_tree* mother;

  //constructor
  decision_tree(decision_tree* mummy, decision_tree_cell c); //used to create a leaf
  decision_tree(decision_tree* mummy, decision_tree_cell c, decision_tree* l, decision_tree* r);

};
