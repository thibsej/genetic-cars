#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>
#include <vector>
#include <utility> // pair
#include "car.h"
#include <utility> //std::pair
#include <math.h>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "strategy.h"

class strategy
{
public:
    strategy();
    std::vector<std::vector<double>> generateCoeffs(std::vector<std::vector<double>> carsAndDistance);
    std::pair<int,int> selectParents(std::vector<double> & distances);
    std::vector<double> generateRandomVector(std::vector<std::vector<double>> cars);
};

#endif // STRATEGY_H
