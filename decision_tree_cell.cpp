#include <vector>
#include <utility>
#include <math.h>
#include <limits>
#include <iostream>
#include "decision_tree_cell.h"

using namespace std;

decision_tree_cell::decision_tree_cell(string p,int v){
    this->param=p;
    this->value=v;
}
