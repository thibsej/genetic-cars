#include "strategy.h"

strategy::strategy()
{

}

// Compute the random evolution of the new cars
//- We can imagine a model where the variability decreases (like temperature)
std::vector<double> strategy::generateRandomVector(std::vector<std::vector<double>> cars){
    std::vector<double> means;
    std::vector<double> variances;
    std::vector<double> new_car;
    std::default_random_engine generator;
    // pour chaque paramètre i (sauf la distance parcourue)
    for(int i=0;i<(cars[0].size()-1);i++){
        // calcul de la moyenne
       double m = 0;
        // pour chaque voiture j
       for(int j=0;j<cars.size();j++){
           m += cars[j][i];
       }
       m /= cars.size();
       // Calcul de la variance
       double var = 0;
       for(int j=0;j<cars.size();j++){
           var += (cars[j][i] - m)*(cars[j][i] - m);
       }
       var /= cars.size();
       variances.push_back(var);
    }
    // pour chaque param i
    for(int i=0;i<(cars[0].size()-1);i++){
        std::normal_distribution<double> distribution(0,variances[i]);
        double param = distribution(generator);
        new_car.push_back(param);
    }
    return new_car;
}

// Calcule les coefficients pour la combinaison linéaire des voitures
// première stratégie : on choisit deux parents parmis la population proportionnellement à leur performance (=distance parcourue)
//

// Tirage avec remise de deux parents, proportionnellement à la distance parcourue

std::vector<std::vector<double>> strategy::generateCoeffs(std::vector<std::vector<double>> carsAndDistance){
    std::vector<std::vector<double>> coeffs;

    std::vector<double> distances;
    for (int i=0;i<carsAndDistance.size() ; i++){
        distances.push_back(carsAndDistance[i][carsAndDistance[i].size()-1]);
    }

    std::pair<int,int> parents;
    parents = selectParents(distances);
    std::cout << "Parents:" << parents.first << parents.second << std::endl;

    std::vector<double> coeff1;
    std::vector<double> coeff2;

    for (int i=0 ; i<carsAndDistance[0].size() -1 ; i++){
        //on choisit chaque caractère entre parent 1 et 2 de manière aléatoire
        double r = ((double)rand() / (RAND_MAX));
        if (r <= 0.5){
            coeff1.push_back(0);
            coeff2.push_back(1);
        }else{
            coeff1.push_back(1);
            coeff2.push_back(0);
        }
    }
    // on met tous les autres coeff à 0
    std::vector<double> null(carsAndDistance[0].size()-1, 0.0);
    for (int i=0;i<carsAndDistance.size() ; i++){
        if(parents.first ==  parents.second && i == parents.first){
            std::vector<double> ones(carsAndDistance[0].size()-1, 1.0);
            coeffs.push_back(ones);
        } else if (i==parents.first){
            coeffs.push_back(coeff1);
        } else if (i==parents.second){
            coeffs.push_back(coeff2);
        } else {
            coeffs.push_back(null);
        }
    }

    return coeffs;
}

std::pair<int,int> strategy::selectParents(std::vector<double> & distances) {
    double distanceTotale = 0.0;
    double distanceCourante = 0.0;
    for(std::vector<double>::iterator it = distances.begin(); it != distances.end(); ++it){
        distanceTotale += *it;
    }
     std::cout << "distanceTotale = " << distanceTotale << endl;
    std::vector<double>::iterator it2 = distances.begin();
    int n1 = -1;
    int n2 = -1;
    int cpt = 0;
    srand(time(NULL));
    double r1 = ((double) rand() / (RAND_MAX));
    std::cout << "r1 = " << r1 << endl;
    double r2 = ((double) rand() / (RAND_MAX));
    std::cout << "r2 = " << r2 << endl;
    while(n1 < 0 || n2 < 0){
        distanceCourante += (*it2 / distanceTotale);
        std::cout << "distanceCourante = " << distanceCourante << endl;
        if(r1 <= distanceCourante && n1 < 0){
            n1 = cpt;
        }
        if(r2 <= distanceCourante && n2 < 0){
            n2 = cpt;
        }
        cpt++;
        it2++;
    }
    return make_pair(n1,n2);
}
