#include "firstLearner.h"
#include <vector>
#include <utility>
#include <math.h>
#include <cmath>
#include <limits>
#include <iostream>
#include "decision_tree.h"

using namespace std;
// (TODO ) adapt to new variable names in car.h

firstLearner::firstLearner(int car_number,int point_voiture,vector<Car> listcar,vector<int> ranking,vector<double> scores){
    this->car_number=car_number;
    this->point_voiture= point_voiture;
    this->listcar=listcar;
    this->ranking=ranking;
    this->scores=scores;
    parameters_number=6 + 2* point_voiture;

    for(int i = 0; i <parameters_number ; i++){
        this->corrolations_ranking.push_back(0);
        this->corrolations_scores.push_back(0);
    }
    make_cars();
    compute_corrolations_ranking();
    compute_corrolations_scores();
}
firstLearner::firstLearner(int car_number,int point_voiture,vector<Car> listcar,vector<double> scores){
    this->car_number=car_number;
    this->point_voiture= point_voiture;
    this->listcar=listcar;
    this->scores=scores;
    //constructing ranking from score : naive O(n^2)
    for(int i=0;i<car_number;i++){
        ranking.push_back(0);
    }
    int pos;
    for(int i=0;i<car_number;i++){
        pos=1;
        for(int j=0;j<car_number;j++){
            if(scores[i]<scores[j]){
                pos++;
            }
        ranking[i]=pos;
        }
    }

    parameters_number=6 + 2* point_voiture;

    for(int i = 0; i <parameters_number ; i++){
        this->corrolations_ranking.push_back(0);
        this->corrolations_scores.push_back(0);
    }
    make_cars();
    compute_corrolations_ranking();
    compute_corrolations_scores();
}
// Transform an object Car in vector
std::vector<double> firstLearner::openCar(Car my_car){
    std::vector<double> data;
    data.push_back(my_car.r1);
    data.push_back(my_car.d1);
    data.push_back(my_car.r2);
    data.push_back(my_car.d2);
    data.push_back(my_car.D);
    data.push_back(my_car.d);
    for(int i=0;i< point_voiture;i++){

       data.push_back((my_car.get_points_without_wheels())[i].first);
       data.push_back((my_car.get_points_without_wheels())[i].second);
    }

    return data;
}
// Convert vector in car
Car firstLearner::returnCar(std::vector<double> attributes){
    Car my_car = Car();
    my_car.N=point_voiture+2;
    my_car.r1 = attributes[0];
    my_car.d1 = attributes[1];
    my_car.r2 = attributes[2];
    my_car.d2 = attributes[3];
    my_car.D = attributes[4];
    my_car.d = attributes[5];

    for(int j = 0; j < point_voiture; j++){
        my_car.angles_distances.push_back(pair<double, double> (attributes[6+2*j],attributes[7+2*j]));
    }
    return my_car;
}
// transform all cars to matrix
void firstLearner::make_cars(){
    for(int i = 0; i <car_number ; i++){
        all_cars.push_back(openCar(listcar[i]));

    }

}

void firstLearner::compute_corrolations_ranking(){
    // store les moyennes pour le calcul de la variance/ covariance et coeff de correlation
    vector<double> param_mean;

    // store la covariance non normalisée
    vector<double> param_cov;
    //store la variance des parametres non normalisée
    vector<double> param_var;
    // store la moyenne et variance du ranking non normalisée
    double ranking_mean=0;
    double ranking_var=0;


    // initialization
    for(int i = 0; i <parameters_number ; i++){
        param_mean.push_back(0);
        param_cov.push_back(0);
        param_var.push_back(0);
    }
    // calcul des moyennes
    for(int i = 0; i <car_number ; i++){
        ranking_mean+=ranking[i];
        for(int j = 0; j <parameters_number ; j++){
            param_mean[j]+=all_cars[i][j];
        }
    }

    ranking_mean/= car_number;
    for(int j = 0; j <parameters_number ; j++){
        param_mean[j]/= car_number;
    }


    // calcul des variances et covariances non normalisée, ( l'effet de la normalisation se compense lors du calcul des parametres de corrélation )
    for(int i = 0; i <car_number ; i++){
        for(int j = 0; j <parameters_number ; j++){
            param_var[j]+=( all_cars[i][j] -  param_mean[j] )*( all_cars[i][j] -  param_mean[j] );
            param_cov[j]+=( all_cars[i][j] -  param_mean[j] )*(ranking[i]-ranking_mean);
        }
        ranking_var+=(ranking[i]-ranking_mean)* (ranking[i]-ranking_mean);

    }

    // calcul des coeff de corrélation
    for(int i = 0; i <parameters_number ; i++){
        if( param_cov[i]==0){
            corrolations_ranking[i]=0;
        }
        else{
            corrolations_ranking[i]= param_cov[i] /(   sqrt(param_var[i]*ranking_var)  ) ;
        }
    }

}


void firstLearner::compute_corrolations_scores(){
    // store les moyennes pour le calcul de la variance/ covariance et coeff de correlation
    vector<double> param_mean;

    // store la covariance non normalisée
    vector<double> param_cov;
    //store la variance des parametres non normalisée
    vector<double> param_var;
    // store la moyenne et variance du score non normalisée
    double scores_mean=0;
    double scores_var=0;


    // initialization
    for(int i = 0; i <parameters_number ; i++){
        param_mean.push_back(0);
        param_cov.push_back(0);
        param_var.push_back(0);
    }
    // calcul des moyennes
    for(int i = 0; i <car_number ; i++){
        scores_mean+=scores[i];
        for(int j = 0; j <parameters_number ; j++){
            param_mean[j]+=all_cars[i][j];
        }
    }

    scores_mean/= car_number;
    for(int j = 0; j <parameters_number ; j++){
        param_mean[j]/= car_number;
    }


    // calcul des variances et covariances non normalisée, ( l'effet de la normalisation se compense lors du calcul des parametres de corrélation )
    for(int i = 0; i <car_number ; i++){
        for(int j = 0; j <parameters_number ; j++){
            param_var[j]+=( all_cars[i][j] -  param_mean[j] )*( all_cars[i][j] -  param_mean[j] );
            param_cov[j]+=( all_cars[i][j] -  param_mean[j] )*(scores[i]-scores_mean);
        }
        scores_var+=(scores[i]-scores_mean)* (scores[i]-scores_mean);

    }

    // calcul des coeff de corrélation
    for(int i = 0; i <parameters_number ; i++){
        if( param_cov[i]==0){
            corrolations_scores[i]=0;
        }
        else{
            corrolations_scores[i]= param_cov[i] /(   sqrt(param_var[i]*scores_var)  ) ;
        }
        //std::cout << corrolations_scores[i] << " " <<param_cov[i] << " " << param_var[i]  << std::endl;
    }

}


Car firstLearner::predict_ranking_car(){

    // store les valeurs min et max apparus de chaque parametres
    vector<double> param_min(parameters_number);
    vector<double> param_max(parameters_number);
    vector<double> new_car(parameters_number);
    double max_val=numeric_limits<double>::max();

    for(int i = 0; i <parameters_number ; i++){

        param_min[i]=max_val;
        param_max[i]=-1;
        new_car[i]=0;
    }
    for(int i = 0; i <car_number ; i++){
        for(int j = 0; j <parameters_number ; j++){
            if(param_min[j] > all_cars[i][j]) {
             param_min[j] = all_cars[i][j];
            }
            if(param_max[j] < all_cars[i][j]) {
               param_max[j] = all_cars[i][j];
            }

        }
    }
    for(int i = 0; i <parameters_number ; i++){
        new_car[i]= param_max[i] + (corrolations_ranking[i]+1)/2   *(param_min[i]-param_max[i]);
    }
    vector<pair <double,double>> nouvelle_carcasse;

    for(int j = 0; j <point_voiture ; j++){
        nouvelle_carcasse.push_back(pair<double, double> (new_car[6+2*j],new_car[7+2*j]));

    }




    Car rank_car(point_voiture+2,new_car[0],new_car[1],new_car[2],new_car[3],new_car[4],new_car[5],nouvelle_carcasse);
    return rank_car;

}
Car firstLearner::predict_scores_car(){

    // store les valeurs min et max apparus de chaque parametres
    vector<double> param_min(parameters_number);
    vector<double> param_max(parameters_number);
    vector<double> new_car(parameters_number);
    double max_val=numeric_limits<double>::max();

    for(int i = 0; i <parameters_number ; i++){

        param_min[i]=max_val;
        param_max[i]=-1;
        new_car[i]=0;
    }
    for(int i = 0; i <car_number ; i++){
        for(int j = 0; j <parameters_number ; j++){
            if(param_min[j] > all_cars[i][j]) {
             param_min[j] = all_cars[i][j];
            }
            if(param_max[j] < all_cars[i][j]) {
               param_max[j] = all_cars[i][j];
            }

        }
    }
    //std::cout << parameters_number << std::endl;
    for(int i = 0; i <parameters_number ; i++){
        //std::cout << corrolations_scores[i] << std::endl;
        new_car[i]= param_min[i] + (corrolations_scores[i]+1)/2   *(param_max[i]-param_min[i]);
        //std::cout << new_car[i] << " " <<  param_min[i] << " " << param_max[i] << " "<<corrolations_scores[i]<<   std::endl;
    }
    vector<pair <double,double>> nouvelle_carcasse;

    for(int j = 0; j <point_voiture ; j++){
        nouvelle_carcasse.push_back(pair<double, double> (new_car[6+2*j],new_car[7+2*j]));

    }




    Car scores_car(point_voiture+2,new_car[0],new_car[1],new_car[2],new_car[3],new_car[4],new_car[5],nouvelle_carcasse);
    return scores_car;

}
//this class uses ranking
Car firstLearner::predict_naive_Bayes_car(int fraction){
    int winner_number=car_number/fraction;
    // we devide the group of cars into winners(best ranking) and non winners
    //are_winners=1 if correspending car is winner
    vector<int> are_winners;
    for(int i=0;i<car_number;i++){
        if( ranking[i]<winner_number){
            are_winners.push_back(1);
        }
        else{
            are_winners.push_back(0);
        }
    }
    // store les valeurs min et max apparus de chaque parametres
    int category_number=10; //categories are portion * i with i=0 to i=10
    vector<double> param_min(parameters_number);
    vector<double> param_max(parameters_number);
    vector<double> new_car(parameters_number);
    double max_val=numeric_limits<double>::max();
    for(int i = 0; i <parameters_number ; i++){
        new_car[i]=0;
        param_min[i]=max_val;
        param_max[i]=-1;
    }
    for(int i = 0; i <car_number ; i++){
        for(int j = 0; j <parameters_number ; j++){
            if(param_min[j] > all_cars[i][j]) {
             param_min[j] = all_cars[i][j];
            }
            if(param_max[j] < all_cars[i][j]) {
               param_max[j] = all_cars[i][j];
            }

        }
    }
    vector<double> portion;


    for(int j = 0; j <parameters_number ; j++){
         portion.push_back( (param_max[j]-param_min[j])/category_number );

    }

    // représente une matrice de taille parameters_number * (category_number+1)
    // stocke le nombre d'apparition des features (catégorique et non continu) et de leurs proba
    //cond => conditionellement à l'appartenance de la voiture au groupes des voitures gagnantes
    vector<vector<double>> count;
    vector<vector<double>> proba;
    vector<vector<double>> cond_proba;
    vector<vector<double>> cond_count;
    // initialization
    for(int j = 0; j <parameters_number ; j++){
        vector<double> current1;
        vector<double> current2;
        vector<double> current3;
        vector<double> current4;

        for(int k = 0; k <category_number ; k++){

            current1.push_back(0);current2.push_back(0);current3.push_back(0);current4.push_back(0);
        }
        count.push_back(current1);
        proba.push_back(current2);
        cond_proba.push_back(current3);
        cond_count.push_back(current4);
    }
    // remplissage de count
    int k;
    for(int i = 0; i <car_number ; i++){
        for(int j = 0; j <parameters_number ; j++){
            if(portion[j]==0){
                k=0;
            }
            else{
                k=floor((all_cars[i][j]-  param_min[j])/  portion[j]) ;
            }

            if (k == category_number){
                k=k-1;
            }

            count[j][k]+=1;
            if (are_winners[i]==1){
            cond_count[j][k]+=1;
            }
        }
    }

    // remplissage des proba
     for(int j = 0; j <parameters_number ; j++){

         for(int k = 0; k <category_number  ; k++){

             proba[j][k]=count[j][k]/car_number;
             cond_proba[j][k]=cond_count[j][k]/winner_number;
         }
     }
     int p;
     int max;
    vector<double> bayes_portions;
    for(int j = 0; j <parameters_number ; j++){
        p=0;
        max=0;

        for(int k = 0; k <category_number ; k++){

            if(proba[j][k]!=0){
                if((cond_proba[j][k]/proba[j][k])>max){
                  max=(cond_proba[j][k]/proba[j][k]);
                  p=k;
                }
            }
        }
        bayes_portions.push_back(p);

    }

    for(int i = 0; i <parameters_number ; i++){

        new_car[i]= param_min[i] + portion[i]*bayes_portions[i];

    }
    vector<pair <double,double>> nouvelle_carcasse;

    for(int j = 0; j <point_voiture ; j++){
        nouvelle_carcasse.push_back(pair<double, double> (new_car[6+2*j],new_car[7+2*j]));

    }

    Car bayes_car(point_voiture+2,new_car[0],new_car[1],new_car[2],new_car[3],new_car[4],new_car[5],nouvelle_carcasse);
    return bayes_car;


}


double firstLearner::compute_I(int n, int p){
  double i = 0;
  double pp = p/(p+n);
  double nn = n/(p+n);
  i = - pp * log2(pp) - nn * log2(nn);
  return i;
}

void firstLearner::decision_tree(int fraction){

//======================================================================================================================
//======================================================================================================================
//==================                                                                                    ================
//==================                          In this section we build tools.                           ================
//==================                                                                                    ================
//======================================================================================================================
//======================================================================================================================

  int good_cars_number = (int) car_number/fraction;
  //so the good_cars_number first cars are considered good.
  int bad_cars_number = car_number - good_cars_number;

  int winner_number=good_cars_number;
  // we devide the group of cars into winners(best ranking) and non winners
  //are_winners=1 if correspending car is winner
  vector<int> are_winners;
  for(int i=0;i<car_number;i++){
      if( ranking[i]<winner_number){
          are_winners.push_back(1);
      }
      else{
          are_winners.push_back(0);
      }
  }
  vector<double> param_min(parameters_number);
  vector<double> param_max(parameters_number);
  vector<double> new_car(parameters_number);
  double max_val=numeric_limits<double>::max();
  for(int i = 0; i <parameters_number ; i++){
      new_car[i]=0;
      param_min[i]=max_val;
      param_max[i]=-1;
  }
  for(int i = 0; i <car_number ; i++){
      for(int j = 0; j <parameters_number ; j++){
          if(param_min[j] > all_cars[i][j]) {
           param_min[j] = all_cars[i][j];
          }
          if(param_max[j] < all_cars[i][j]) {
             param_max[j] = all_cars[i][j];
          }

      }
  }

  //pour chaque parametre portion[i] donne la largeur d'une portion
  vector<double> portion;
  int category_number =10;
  for(int j = 0; j <parameters_number ; j++){
       portion.push_back( (param_max[j]-param_min[j])/category_number );
  }

  // représente une matrice de taille parameters_number * (category_number)
  // stocke le nombre d'apparition des features (catégorique et non continu) et de leurs proba
  //cond => conditionellement à l'appartenance de la voiture au groupes des voitures gagnantes
  vector<vector<double>> count;
  vector<vector<double>> proba;
  vector<vector<double>> cond_proba;
  vector<vector<double>> cond_count;

  // initialization
  for(int j = 0; j <parameters_number ; j++){
      vector<double> current1;
      vector<double> current2;
      vector<double> current3;
      vector<double> current4;
      for(int k = 0; k <category_number ; k++){
          current1.push_back(0);current2.push_back(0);current3.push_back(0);current4.push_back(0);
      }
      count.push_back(current1);
      proba.push_back(current2);
      cond_proba.push_back(current3);
      cond_count.push_back(current4);
  }

  // remplissage de count
  int k;
  for(int i = 0; i <car_number ; i++){
      for(int j = 0; j <parameters_number ; j++){
          if(portion[j]==0){
              k=0;
          }
          else{
              k=floor((all_cars[i][j]-  param_min[j])/  portion[j]) ;
          }
          if(k==category_number){
            k=k-1;
          }
          count[j][k]+=1;
          if (are_winners[i]==1){
          cond_count[j][k]+=1;
          }
      }
  }

  // remplissage des proba
   for(int j = 0; j <parameters_number ; j++){
       for(int k = 0; k <category_number; k++){
           proba[j][k]=count[j][k]/car_number;
           cond_proba[j][k]=cond_count[j][k]/winner_number;
       }
   }



   //======================================================================================================================
   //======================================================================================================================
   //==================                                                                                    ================
   //==================                          Here is the learning part.                                ================
   //==================                                                                                    ================
   //======================================================================================================================
   //======================================================================================================================

   vector<int> car_list;
   for (int i = 0; i<car_number; i++){
     car_list.push_back(1);
   }

   for (int nb_iteration = 0; nb_iteration<5; nb_iteration++){

      //car_list is a list containing the 1 or -1 to know whether a car is left after iteration i
      //for each iteration, we look for the parametre that give the best split.
      //for this parametre we look for the value of the split
      //enventually we keep track of the parameters and value of the split
      //and at the same time keep only the cars that fit those requirements.

      //see Machine Learning course for the definition of this function

      vector <int> current_cars;
      for (int i = 0; i < car_list.size(); i++){
        if (car_list[i] == 1){
          current_cars.push_back(i);
        }
      }

      int good_cars_number = (int) current_cars.size()/fraction;
      //so the good_cars_number first cars are considered good.
      int bad_cars_number = current_cars.size() - good_cars_number;


      double i = compute_I(good_cars_number, bad_cars_number);

      //for each parameter we compute the information gain
      vector<double> g; //
      for (int i = 0; i<parameters_number; i++){
       //compute entropy
       double e = 0.0;
       for(int j = 0; j<category_number; j++){
         e = e + count[i][j]/car_number + compute_I(cond_count[i][j], count[i][j] - cond_count[i][j]);
       }
       g.push_back(i - e);
     }

     //we check which parameter has the highest information gain.
     int max = g[0];
     int ind_max = 0;
     for (int i = 1; i<parameters_number; i++){
       if (g[i] > max){
         max = g[i]; ind_max = i;
       }
     }

     //here, ind_max is the index of the parameter that has the highest information gain.

     vector<int> sorted_cars;
     for (int i = 0; i<car_number; i++){
       sorted_cars.push_back(0);
     }
     //this vector contains the indexes of the cars sorted according to the value of their parameter ind_max.
     //Here we build this vector

      for (int i = 0; i < car_number; i++){
        int compteur = 1;
        int value = all_cars[i][ind_max];
        for (int j = 0; j< car_number; j++){
          if (value < all_cars[j][ind_max]){
            compteur++;
          }
        }
        if (compteur>car_number){
        std::cout<<"Error while building the vector Sorted_cars" <<endl;
        }else{
          sorted_cars[compteur-1] = i;
        }
     }


     int good_count_right = good_cars_number, bad_count_right = car_number - good_cars_number, good_count_left = 0, bad_count_left = 0;

     double current = param_min[ind_max]-1;
     double pas = (param_max[ind_max] - param_min[ind_max])/1000;

     double norme_max = 0;
     double curseur_max = current;
     char side = 'r';

     for (int i = 0; i<1000; i++){
       current = current + pas;
       int j = 0;
       while(j<car_number){
         if (all_cars[sorted_cars[j]][ind_max] <= current){
           if (ranking[sorted_cars[j]] <= good_cars_number){
             good_count_left++; good_count_right--;
           }else{
             bad_count_left++; bad_count_right--;
           }
           j++;
         }else{
           break;
         }
       }
       //calculons la norme de ce split.
       double abb = good_count_right + bad_count_left - good_count_left - bad_count_right;
       if ( abs(abb) > abs(norme_max)){
         norme_max = abb; curseur_max = current;
       }
     }
     //here norme_max is the value of the largest split.
     //it can be <0 or >0 whether you have to go in the right or left subtree to follow the good-car path.
     //curseur_max is the cursor corresponding to the value of the largest split.

     //now it is time to build the decision tree itself
     //we have to select the cars that
     //           - if norme_max > 0, have a parameter ind_max larger than curseur_max
     //           - if norme_max < 0, have a parameter ind_max smaller than curseur_max


  }
}
double firstLearner::vectordistance(int longueur,vector<double> v1, vector<double> v2){
    double res=0;
    for(int i=0;i<longueur;i++){
        res+=  (v1[i]-v2[i]) * (v1[i]-v2[i]) ;
    }
    res=sqrt(res);
    return res;
}

bool firstLearner::testequals(vector<vector<double>> v1,vector<vector<double>> v2 ,int n_rows,int n_columns){

    for(int i=0;i<n_rows;i++){
        for(int j=0;j<n_columns;j++){
            if(v1[i][j]!=v2[i][j]){
                return false;
            }


        }
    }
    return true;
}

Car firstLearner::predict_kmean_cluster(int n_clust){
    //cout<< "initializing centroids" << endl;
    //store values of centroids
    vector<vector<double>> centroids;
    //random initialization of centroids
    for(int i = 0; i < n_clust; i++)
    {
     centroids.push_back(  all_cars[rand() % car_number]  );
    }
    //cout<< "centroid initialized" << endl;
    int n_iterations=0;
    // store old centroids, needed to test convergence of kmeans
    vector<vector<double> > oldCentroids;
    //initialization oldCentroids;
    vector<double> a;
    for(int k=0;k<parameters_number;k++){
     a.push_back(0);
    }
    for(int j=0;j<n_clust;j++){
        oldCentroids.push_back(a);

    }
    //store labels
    vector<double> labels;
    //initialize labes
    for(int j=0;j<car_number;j++){
        labels.push_back(0);

    }
    double l;
    double newl;
    int cluster_count=0;
    //cout<< "entering do loop" << endl;
    do{
        //incremanting iteration number
        n_iterations++;
        //Oldcentroids update
        for(int j=0;j<n_clust;j++){
            for(int k=0;k<parameters_number;k++){
             oldCentroids[j][k]=centroids[j][k];
            }

        }
        // associating new labels to all cars
        for(int i=0;i<car_number;i++){
            labels[i]=0;
            l=vectordistance(parameters_number, all_cars[i],centroids[0] );
            for(int j=0;j<n_clust;j++){
                newl=vectordistance(parameters_number, all_cars[i],centroids[j]);
                if(newl<l){
                    l=newl;
                    labels[i]=j;
                }
            }

        }
        //mise a jour de OldCentroids
        for(int k=0;k<n_clust;k++){
            for(int j=0;j<parameters_number;j++){
                oldCentroids[k][j]=centroids[k][j];
            }

        }
        //mise a jour des centroids
        for(int k=0;k<n_clust;k++){
            for(int j=0;j<parameters_number;j++){
                centroids[k][j]=0;

            }
            cluster_count=0;
            for(int i=0;i<car_number;i++){
                if(labels[i]==k){
                    cluster_count++;
                    // centroid[k]=centroid[k]+voiture[i]
                    for(int j=0;j<parameters_number;j++){
                        centroids[k][j]+=all_cars[i][j];

                    }

                }


            }
            //centroid[k]=centroid[k]/cluster_count
            for(int j=0;j<parameters_number;j++){
                centroids[k][j]=centroids[k][j]/cluster_count;
            }
         }



    //testing iterations
    //std::cout<<n_iterations<<std::endl;

    }while(n_iterations <100 && !(testequals(centroids,oldCentroids,n_clust,parameters_number))   );
    // la clusterisation est fini :D , mnt il faut calculer le score moyen de chaque cluster !
    int index;
    //storent les scores de chaque clusters, et le nombre de voitures par clusters
    vector<double> clust_scores;
    vector<double> counts;
    // initialization a zero
    for(int k=0;k<n_clust;k++){
        clust_scores.push_back(0);
        counts.push_back(0);
    }
    // calcul des scores cummulés et counts
    for(int i=0;i<car_number;i++){
        index=labels[i];
        clust_scores[index]+=scores[i];
        counts[index]++;
    }
    //calcul des scores moyens par cluster
    for(int k=0;k<n_clust;k++){
        clust_scores[k]=clust_scores[k]/counts[k];
    }
    // recherce du meilleur maximale

    double max_score=0;
    double max_index=0;
    for(int k=0;k<n_clust;k++){
        if(clust_scores[k]>max_score){
            max_score=clust_scores[k];
            max_index=k;
        }
    }
    // maintenant on renvoi le centroid du cluster max_index
    vector<double> new_car(parameters_number);

    for(int i = 0; i <parameters_number ; i++){
        new_car[i]=0;
    }

    for(int i = 0; i <parameters_number ; i++){

        new_car[i]= centroids[max_index][i];

    }
    vector<pair <double,double>> nouvelle_carcasse;

    for(int j = 0; j <point_voiture ; j++){
        nouvelle_carcasse.push_back(pair<double, double> (new_car[6+2*j],new_car[7+2*j]));

    }

    Car kmeans_car(point_voiture+2,new_car[0],new_car[1],new_car[2],new_car[3],new_car[4],new_car[5],nouvelle_carcasse);
    return kmeans_car;

}
