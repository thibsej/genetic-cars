#include "preprocessing.h"
#include "strategy.h"
#include "car.h"
#include <math.h>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <time.h>

// Initialise our working project
preprocessing::preprocessing(){
    srand(time(NULL));
    std::default_random_engine generator;
}

// Transfor a vector of vector of car parameters into a vector of cars
std::vector<Car> preprocessing::matrixToCars(std::vector<std::vector<double>>* matrix){
   std::vector<Car> cars;
   for(int i=0;i<(*matrix).size();i++){
       std::vector<double> tmp = (*matrix)[i];
       cars.push_back(returnCar(&tmp));
   }
   return cars;
}

/* Transforme l'output de la course en matrice
    Get: list of pair (Car, rankingof the car)
    Return: list of vector with params of the car + ranking at end of vector
*/
std::vector<std::vector<double>> preprocessing::carsToMatrix(std::vector<std::pair<Car,double>>* output){
    std::vector<std::vector<double>> M;
    for(std::vector<std::pair<Car,double>>::iterator it = output->begin(); it != output->end(); ++it){
        std::vector<double> data;
        data = openCar(&((*it).first));
        data.push_back((*it).second);
        M.push_back(data);
    }
    return M;
}

// Transform an object Car in vector
std::vector<double> preprocessing::openCar(Car* my_car){
    std::vector<double> data;
    data.push_back(my_car->r1);
    data.push_back(my_car->d1);
    data.push_back(my_car->r2);
    data.push_back(my_car->d2);
    data.push_back(my_car->D);
    data.push_back(my_car->d);
    for(int i=0;i<my_car->angles_distances.size();i++){
        data.push_back(my_car->angles_distances[i].first);
    }
    for(int i=0;i<my_car->angles_distances.size();i++){
        data.push_back(my_car->angles_distances[i].second);
    }
    return data;
}

// Convert vector in car
Car preprocessing::returnCar(std::vector<double>* attributes){
    int N = 8;
    double r1 = (*attributes)[0];
    double d1 = (*attributes)[1];
    double r2 = (*attributes)[2];
    double d2 = (*attributes)[3];
    double D = (*attributes)[4];
    double d = (*attributes)[5];

    int len = N - 2;//6

    std::vector<std::pair <double, double> > angles_distances;
    for(int i = 0; i < N - 2; i++){
      angles_distances.push_back(pair<double, double> ((*attributes)[6+i], (*attributes)[6+len+i]));


    }
    //return Car(N, r1, d1, r2, d2, D, d, angles_distances);
    return Car();
}

// Sum of two cars
std::vector<double> preprocessing::add(std::vector<double> a, std::vector<double> b){
    std::vector<double> c;
    for (int i=0;i<a.size();i++){
        c.push_back(a[i] + b[i]);
    }
    return c;
}

//Multiply car with a scalar
std::vector<double> preprocessing::multiply(std::vector<double> lambda, std::vector<double> car){
    std::vector<double> c;
    for (int i=0;i<car.size();i++){
        c.push_back( lambda[i] * car[i]);
    }
    return c;
}

// Pour la debug : print vector.
void preprocessing::printVector(std::vector<double>* vec){
    for (std::vector<double>::const_iterator i = vec->begin(); i != vec->end(); ++i)
        std::cout << *i << ' ';
    std::cout << ' ' << std::endl;
}

// Generate cars of a new generation from the result of a race.
void preprocessing::generate(strategy strat, std::vector<std::vector<double>> *cars,std::vector<std::vector<double>> *newCars,int nbCars){
    for (int i=0;i<nbCars;i++){//nbCars
        std::vector<std::vector<double>> coeffs = strat.generateCoeffs(*cars);
        std::vector<double> newCar((*cars)[0].size()-1,0);
        for (int j=0;j<cars->size();j++){
            std::vector<double> my_car = (*cars)[j];
            my_car.pop_back();
            std::vector<double> prod = preprocessing::multiply( my_car,coeffs[j] );
            newCar = preprocessing::add( newCar , prod );
        }
        printVector(&newCar);
        newCars->push_back(newCar);
    }
}

// Compute a random car with coherent coefficients (around coherent means and with a large variance).
Car preprocessing::generateRandomCar(std::vector<double> means, std::vector<double> variances){
    std::vector<double> attributes;
    for(int i = 0;i < 6; i++){
        std::normal_distribution<double> distribution(means[i], variances[i]);
        double value = distribution(generator);
        attributes.push_back(value);
    }
    int len = 6; //nombre de points libres dans le chassis
    for(int i = 0; i < len; i++){
        std::normal_distribution<double> distribution_means(means[6 + i], variances[6 + i]);
        double value_mean = distribution_means(generator);
        attributes.push_back(value_mean);
    }
    for(int i = 0; i < len; i++){
        std::normal_distribution<double> distribution_variances(means[6 + len + i], variances[6 + len + i]);
        double value_variance = distribution_variances(generator);
        attributes.push_back(value_variance);
    }
    return returnCar(&attributes);
}

// Function called to launch the simulation by generating N random cars.
std::vector<Car> preprocessing::initialise(int N, std::vector<double> means, std::vector<double> variances){
    std::vector<Car> firstCars;
    for (int i=0;i<N;i++){
        firstCars.push_back(preprocessing::generateRandomCar(means,variances));
    }
    return firstCars;
}

//Function called by the outside to generate the first generation of cars
std::vector<Car> preprocessing::generateCars(int n){
    preprocessing pre = preprocessing();
    std::vector<double> means = {1.6, 2.6, 3.6, 4.6, 22.6, 22.6, 22.6, 22.6, 22.6, 22.6, 22.6, 22.6, 22.6, 22.6, 10, 10, 10, 10}; //éventuellement changer le nombre de paramètres
    std::vector<double> variances = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    return pre.initialise(n,means,variances);
}

//Function called by the outside to generate the next generation of cars
std::vector<Car> preprocessing::generateCars(int n,std::vector<std::pair<Car,double>> list){
    strategy strat = strategy();
    preprocessing pre = preprocessing();
    std::vector<std::vector<double>> cars = pre.carsToMatrix(&list);
    std::vector<std::vector<double>> newCars;
    preprocessing::generate(strat,&cars,&newCars,n);
    return pre.matrixToCars(&newCars);
}
