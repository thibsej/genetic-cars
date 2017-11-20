#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "car.h"
#include <utility> //std::pair
#include <math.h>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "strategy.h"

class preprocessing
{
public:
    std::default_random_engine generator;
    preprocessing();
    std::vector<double> openCar(Car* my_car);
    std::vector<Car> matrixToCars(std::vector<std::vector<double> >* matrix);
    Car returnCar(std::vector<double>* attributes);
    double computeCoeff(int rank, int total);
    std::vector<double> generateRandomVector(std::vector<std::vector<double> > cars);
    std::vector<double> generateCoeff(int N);
    static void generate(strategy strat, std::vector<vector<double>> *cars,std::vector<vector<double>> *newCars,int nbCars);
    std::vector<std::vector<double>> carsToMatrix(std::vector<std::pair<Car,double>>* output);
    static void printVector(std::vector<double> * vec);
    std::vector<Car> initialise(int N, std::vector<double> means, std::vector<double> variances);

    static std::vector<double> add(std::vector<double> a, std::vector<double> b);
    static std::vector<double> multiply(std::vector<double> lambda, std::vector<double> car);

    Car generateRandomCar(std::vector<double> means, std::vector<double> variances);

    static std::vector<Car> generateCars(int n);
    static std::vector<Car> generateCars(int n,std::vector<std::pair<Car,double>> list);



};

#endif // PREPROCESSING_H
