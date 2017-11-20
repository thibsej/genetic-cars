#include <QCoreApplication>
#include "car.h"
#include "firstLearner.h"
#include "learner.h"
#include <iostream>
#include "windows.h"
#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPolygonF>
#include <QPointF>
#include <utility>
#include "Moteur.h"
#include <math.h>
#include <vector>
#include <typeinfo>

using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testing firstLearner

    int point_voiture=6;
    vector<pair <double,double>> nouvelle_carcasse1;
    vector<pair <double,double>> nouvelle_carcasse2;
    vector<pair <double,double>> nouvelle_carcasse3;
    vector<pair <double,double>> nouvelle_carcasse4;
    vector<pair <double,double>> nouvelle_carcasse5;
    vector<pair <double,double>> nouvelle_carcasse6;
    for(int j = 0; j <point_voiture ; j++){
        nouvelle_carcasse1.push_back(pair<double, double> ((1+j)*3.12/point_voiture,j+1));
        nouvelle_carcasse2.push_back(pair<double, double> ((0.5+j)*3.12/point_voiture,j+1));
        nouvelle_carcasse3.push_back(pair<double, double> ((0.4+j)*3.12/point_voiture,2*j+1));
        nouvelle_carcasse4.push_back(pair<double, double> ((1+0.8*j)*3.12/point_voiture,2*j+1));
        nouvelle_carcasse5.push_back(pair<double, double> ((1+0.1*j)*3.12/point_voiture,j+2));
        nouvelle_carcasse6.push_back(pair<double, double> ((1+0.6*j)*3.12/point_voiture,j+1));
    }
    int nombre_sommet=point_voiture+2;
    Car car1(8,2,3,2,4,10,6,nouvelle_carcasse1);
    Car car2(8,2,2,4,4,5,5,nouvelle_carcasse2);
    Car car3(8,7,4,13,4,15,18,nouvelle_carcasse3);
    Car car4(8,2,3,12,4,27,16,nouvelle_carcasse4);
    Car car5(8,5,5,7,4,20,15,nouvelle_carcasse5);
    Car car6(8,7,3,3,4,27,18,nouvelle_carcasse6);

    //std::cout << (car1.get_points())[2].first << std::endl;

    vector<Car> Listcar;
    Listcar.push_back(car1);
    Listcar.push_back(car2);
    Listcar.push_back(car3);
    Listcar.push_back(car4);
    Listcar.push_back(car5);
    Listcar.push_back(car6);
    //std::cout << Listcar[1].r1 << std::endl;
    vector<double> scores;
    scores.push_back(250);
    scores.push_back(260);
    scores.push_back(70);
    scores.push_back(170);
    scores.push_back(100);
    scores.push_back(150);
    vector<int> ranking;
    ranking.push_back(2);
    ranking.push_back(1);
    ranking.push_back(6);
    ranking.push_back(3);
    ranking.push_back(5);
    ranking.push_back(4);

    //testing learner and generate...
    learner predictor=learner();
    //std::cout<< " here" << endl;
    vector<Car> result;
    vector<pair<Car,double>> train;
    for(int i=0;i<6;i++) {
        train.push_back(  pair<Car, double> ( Listcar[i]  ,scores[i]  )  );
    }
    result= predictor.generate(5,train);

    result= predictor.generate_continuous(6,train);
    //visualizing result
    for(int i=0;i<6;i++) {
        std::cout << "car number "<< i<< std::endl;

        std::cout << result[i].r1 << std::endl;
        std::cout << result[i].d1 << std::endl;
        std::cout << result[i].r2 << std::endl;
        std::cout << result[i].d2 << std::endl;
        std::cout << result[i].D << std::endl;
        std::cout << result[i].d << std::endl;
        for (int j=0;j<point_voiture;j++){
            std::cout << (result[i].get_points_without_wheels())[j].first << std::endl;
            std::cout << (result[i].get_points_without_wheels())[j].second << std::endl;
        }

    }
    for (int i=0; i< 30;i++){
    result= predictor.generate_continuous(6,train);
    }
    //visualizing result
    for(int i=0;i<6;i++) {
        std::cout << "car number "<< i<< std::endl;

        std::cout << result[i].r1 << std::endl;
        std::cout << result[i].d1 << std::endl;
        std::cout << result[i].r2 << std::endl;
        std::cout << result[i].d2 << std::endl;
        std::cout << result[i].D << std::endl;
        std::cout << result[i].d << std::endl;
        for (int j=0;j<point_voiture;j++){
            std::cout << (result[i].get_points_without_wheels())[j].first << std::endl;
            std::cout << (result[i].get_points_without_wheels())[j].second << std::endl;
        }

    }





    //instruction to execute fiest learner
    //begin

    //firstLearner testlearner1 =firstLearner(6,point_voiture,Listcar,ranking,scores);
    /*
    app.exec();

    std::cout << "Starting..." << std::endl;

    return 0;
    */

}

