#ifndef B2CAR_H
#define B2CAR_H

#include "car.h"
#include "Box2D/Box2D.h"
#include <iostream>
#include <string>

class b2Car
{
public:
    b2Car(); // Constructeur vide
    b2Car(Car car, b2World * m_world); // constructeur d'une b2Car (pour box2d) à partir d'une Car (ensemble de double)

    //idée : remplacer les initialize par des contructeurs + un boolean de test qui permet de ne pas donner de car mais de prendre la car de test
    //créer b2(Car car, b2world* m_world, bool test)

    Car voitureparent; // pointeur vers la Car qui a permis de générer la b2Car
    b2Body* m_car; //
    b2Body* m_wheel1;
    float radius1;
    float radius2;
    b2Body* m_wheel2;
    b2Vec2* positionMaximale; // Ce point enregistre les coordonnées du centre de la position la plus à droite de la voiture.
    float32 tempsStagnation; // Temps pendant lequel la voiture n'avance plus.
    std::string nom; // Nom de la voiture
    int classement; // Classement de la voiture en fin. Si non classée, -1.
    bool vivante;
    void initializeTestCar(b2World* m_world); // On construit une voiture test (celle de l'exemple Box2D) dans un monde pointé
    void initializeTestCarNulle(b2World* m_world); // On construit une voiture test (comme la précédente) mais qui avance moins vite pour tester les fonctions de classement
    void printPosition(); // imprime position, angle, temps de stagnation, classment en console. Pour les tests
    bool bloquee(float tempsStagnationMax); // true si la voiture est morte

    void creationChassis(b2Body* m_car, const vector< pair<double, double> > &pos, Car &c); //crée un chassis correspondant à la car c sur m_car qui doit déjà avoir été ajouté au m_world
    vector<pair<double,double> > get_chassis(); //renvoie le chassis de la voiture parent

};

#endif // B2CAR_H
