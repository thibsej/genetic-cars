
#include <vector>
#include<utility>
#include "car.h"
using namespace std;

// class that makes the generation, using ferslearner

class learner
{
public :
    //constructor

    learner();
    // englobe les fonctions de first learners
    vector<Car> generate(int n,vector<pair<Car,double>> list);
    // continuous learner : garde en memoire toutes les voitures vues auparavant
    vector<Car> generate_continuous(int n,vector<pair<Car,double>> list);
    // données pour le continuous learner
    int continuous_call;
    vector<pair<Car,double>> old;

};


