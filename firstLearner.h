
#include <vector>
#include<utility>
#include "car.h"
using namespace std;

/* Load the a  vector of " cars "
 * load a vector of their performance ( or ranking )
 * Corrolation : Pearson product-moment correlation coefficient
 *  pour le score  coeff_correlation =1 => on prend la valeur max du parametre, -1 valeurs min, autres => min + (coeff+1)/2   *(max-min)
 * Pour le ranking ranking petit => meilleur voiture, => coeff_correlation =1 => on prend la valeur min du parametre, 1 valeurs max  autres => max + (coeff+1)/2   *(min-max)
 * pour la carcasse : Pour le moment , le nombre de point est choisi constant 8 poins : R1,R2 et 6 autres,
 *                                      toutes les voitures recus ont le même nmb de point
 *                                     Centre C(0,r1) , pas inclus dans la carcasse
 *                                     R1(D/2,0)  , D is noted L also
 *                                     R2(-D/2,0)
 *                                     car.angles et car.distances donne distance entre point et C, et les angles (C,axeX,point)
 *                                     Conditions : angles distincts
 * Create "best"  predicted car
 */



class firstLearner
{
public :
    vector<Car> listcar;
    vector<int> ranking;
    vector<double> scores; // = distance parcourues
    vector<vector<double>> all_cars;
    int car_number; // number of cars that we will use for the prediction, should be the length of listcar,ranking and scores
    int parameters_number ; // number of car parameters used for corrolation = 6  +   2* (nombre de points ( sans compter R1 et R2))
    int point_voiture; // nombre de points différent (sans compter R1 et R2))
    vector<double> corrolations_ranking; // corrolations with ranking
    vector<double> corrolations_scores ;// corrolations with score

    //constructeur
    firstLearner(int car_number,int point_voiture,vector<Car> listcar,vector<int> ranking,vector<double> scores);
    firstLearner(int car_number,int point_voiture,vector<Car> listcar,vector<double> scores);
    //corrolations
    void compute_corrolations_ranking();
    void compute_corrolations_scores();
    Car predict_ranking_car();
    Car predict_scores_car();
    //data processing
    std::vector<double> openCar(Car my_car);
    Car returnCar(std::vector<double> attributes);

    void make_cars();
    //Naive bayes
    Car predict_naive_Bayes_car(int fraction); // fraction = fraction des voitures qui sera considéré  comme gagnant ( ex: fraction =3 =>les 1/3  premier voitures sont gagnant )
    Car predict_kmean_cluster(int n_clust); //On classe les voitures en n_clust clusters, On calcule le score_moyen de chauqe cluster, On renvoit le centroid du cluster au plus haut score
    double vectordistance(int longueur,vector<double> v1, vector<double> v2); // distance entre deux vecteurs de même longueur donnée. utilisée pour calcul de distance dans kmeans
    bool testequals(vector<vector<double>> v1,vector<vector<double>> v2 ,int n_rows,int n_columns); //test l'égalité entre 2 matrice, utilisé pourcomparer centroi à Old centroid dans kmeans
    //decision tree functions
    int* reverse_ranking();

    double compute_I(int n, int p);


    void decision_tree(int fraction);




};




