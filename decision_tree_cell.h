#include <vector>
#include<utility>
#include "car.h"
using namespace std;

class decision_tree_cell{
public:

  string param; //paramètre selon lequel on discrimine
  int value; //valeur limite. Si on est < on descend à gauche sinon à droite.

  //constructor
  decision_tree_cell(string p, int v);
};
