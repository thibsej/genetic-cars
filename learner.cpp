#include "learner.h"
#include <vector>
#include <utility>
#include <math.h>
#include <limits>
#include <iostream>
#include "firstLearner.h"

using namespace std;


learner::learner(){
    this->continuous_call=0;
    //std::cout<< " here" << endl;



}

vector<Car> learner::generate(int n,vector<pair<Car,double>> list){
    //getting number of cars
    int num_car=list.size();
    vector<Car> carlist;
    vector<double> les_scores;
    //seperating cars and scores:
    for(int i=0;i<num_car;i++){
        carlist.push_back(list[i].first);
        les_scores.push_back(list[i].second);
    }
    firstLearner testlearner =firstLearner(num_car,6,carlist,les_scores);
    vector<Car> return_car;
    for(int i=0;i<n;i++){
        if(i==0){
            return_car.push_back(testlearner.predict_scores_car());
        }
        else if(i==1){
            return_car.push_back(testlearner.predict_ranking_car());
        }
        else{
            if(i%2==0){
                return_car.push_back(testlearner.predict_naive_Bayes_car(i));
            }
            else{
                return_car.push_back(testlearner.predict_kmean_cluster(i));
            }


        }


    }



    return return_car;

}

vector<Car> learner::generate_continuous(int n,vector<pair<Car,double>> list){
    //getting number of cars


    old.insert( old.end(), list.begin(), list.end() );
    if(continuous_call!=0){
        continuous_call=1;

    }

    int num_car=old.size();
    //cout<< "nub_car used is " << num_car << endl;
    vector<Car> carlist;
    vector<double> les_scores;
    //seperating cars and scores:
    for(int i=0;i<num_car;i++){
        carlist.push_back(old[i].first);
        les_scores.push_back(old[i].second);
    }
    firstLearner testlearner =firstLearner(num_car,6,carlist,les_scores);
    vector<Car> return_car;
    for(int i=0;i<n;i++){
        if(i==0){
            return_car.push_back(testlearner.predict_scores_car());
        }
        else if(i==1){
            return_car.push_back(testlearner.predict_ranking_car());
        }
        else{
            if(i%2==0){
                return_car.push_back(testlearner.predict_naive_Bayes_car(i));
            }
            else{
                return_car.push_back(testlearner.predict_kmean_cluster(i));
            }


        }


    }
    int n_old=old.size();
    if(n_old>100){
        int to_remove=n_old-100;
        old.erase(old.begin(), old.begin() + to_remove);


    }

    return return_car;

}

