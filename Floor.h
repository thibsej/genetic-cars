#ifndef FLOOR_H
#define FLOOR_H

#include "Box2D/Box2D.h"
#include <list>
#include <random>
#include <iostream>
#include <chrono>

class Floor
{
public:
    Floor(); // Constuit un sol plat de 100m. ICI un sol = une liste de points
    Floor(float mur); // Construit un sol plat de 100m avec un mur vertical en x = mur
    Floor(double l, double v); //initialisateur 'classique' de la classe
    Floor(double l, double v, bool c); // initialisateur 'classique' de la classe, devrait etre supprime a terme car chaos est inutile
    double getLength(); // récupère les éléments private
    double getVariance(); // récupère les éléments private
    void createArrayb2Vec2(int N); // Construit un sol aléatoire avec la méthode de Thibault
    void floorInitialize(b2World* world);// Construit effectivement le sol dans le monde pointé
    std::list<float32>* getPoints();
    std::list<b2Vec2>* p; // Liste des points du sol dans l'ordre gauche -> droite
//    void extend();
private:
    double length; // Longueur de chaque bout de segments
    double variance; // Variance -> génère le chaos du sol

    bool chaos; // booleen qui s'il est faux lisse le sol car l'angle dépend du précédent. sinon l'angle sera totalement aléatoire
};
#endif // FLOOR_H
