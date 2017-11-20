#ifndef MOTEUR_H
#define MOTEUR_H

#include "Box2D/Box2D.h"
#include "b2Car.h"
#include "Floor.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <array>




// Structure pour trier la position des voitures et donc faire le classment !
struct CouplePositionXVoiture
{
    float x; // position horizontale
    unsigned int voiture; // numéro de la voiture
    CouplePositionXVoiture(float x1, unsigned int voiture1) : x(x1), voiture(voiture1) {}
};
struct greater_than
{
    // operateur de comparaison
    inline bool operator() (const CouplePositionXVoiture& couple1, const CouplePositionXVoiture& couple2){
        return (couple1.x > couple2.x);
    }
};


class Moteur{

public :
//constructeurs de tests
    Moteur(); // Constructeur vide
    Moteur(float32 g); // Constructeur que j'utilise pour les test. NE PAS SUPPRIMER. Le constructeur final prendra beaucoup à celui-ci.
    Moteur(float32 g, Car c); // constructeur de test, fait rouler 2 voitures issues de la même Car c

//constructeur et destructeurs utiles
    Moteur( vector<Car> V, float32 g = 9.81f, float32 timeStep = 1.0f/60.0f, float32 velocityIterations = 8.0f, float32 positionIterations = 3.0f, float tempsStagnationMax=5, double length_floor = 1.0, double var_floor = 0.005);
// constructeur à utiliser dans l'appli
    ~Moteur(); // destructeur


    float t; // Temps dans le moteur physique
//paramètre de la simulation physique
    float32 timeStep; // Pas de temps dans le moteur physique box2d
    int32 velocityIterations; // Paramètre box2d
    int32 positionIterations; // Paramètre box2d

    Floor* b2floor; // Sol de notre monde
    float gravite; // Valeur absolue de l'intensite de la pesanteur dans notre monde

    b2World* world; // Tableau de pointeurs vers nos mondes. Un monde par voiture pour faire les courses en meme temps sans que les voitures se genent.
    std::vector<b2Car*> car; // Tableau de nos voitures box2d

    float tempsStagnationMax;
    bool toutesCarBloquees(); // Si true ie si toutes les voitures n'avancent plus depuis suffisamment longtemps la course s'arrete

    void printPositions(); // Imprime les positions, angles, temps de stagnation et classement de toutes nos voitures

//méthode pour l'interface graphique
    void next(float dt); // Avance de dt dans le moteur physique et mets à jour les paramètres
    std::vector<std::array<float, 4> > getPosition(); // Pour l'interface graphique.
    std::vector<std::array<float,6> > getWheels();
    void classement(); // Met à jour le classement des voitures
    std::vector< pair< Car, double> > getResult(); //renvoie la car associé à sa distance parcourrue à la fin
};

#endif // MOTEUR_H
