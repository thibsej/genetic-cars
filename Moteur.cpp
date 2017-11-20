#include "Floor.h"
#include "car.h"
#include "b2Car.h"
#include "Moteur.h"


Moteur::Moteur(){
    car = std::vector<b2Car*>();
}

Moteur::Moteur(float32 g){
    this->timeStep = 1.0f / 60.0f;
    this->velocityIterations = 5;
    this->positionIterations = 5;

    //Floor *fl = new Floor(80);
    this->tempsStagnationMax = 5.0;
    b2floor = new Floor(2.0, 0.012, true);
    b2floor->createArrayb2Vec2(1000);

    //test sol plat de 100m avec mur à 50m
//    Floor *fl = new Floor(50);
//    fl->createArrayb2Vec2(1000);

    this->car = std::vector<b2Car*>();
    b2Car* car1 = new b2Car();
    car.push_back(car1);
    b2Car* car2 = new b2Car();
    car.push_back(car2);

    world = new b2World(b2Vec2(0.0, -g));
    b2floor->floorInitialize(world);
    // Le compteur ici ne sert que pour les tests. A terme avec l'implémentation des voitures dans box2D, il devra etre supprimé
    int compteur = 0;
    for(std::vector<b2Car*>::iterator i = car.begin(); i != car.end(); i++){
        b2Car* currentCar = (*i);
        if (compteur == 0){ currentCar->initializeTestCar(world); } else{currentCar->initializeTestCarNulle(world);}
        //fl->floorInitialize(world);
        compteur++;
    }
}

Moteur::Moteur(float32 g, Car c){
    // crée un monde avec 2 voitures identiques basées sur Car c

    this->timeStep = 1.0f / 60.0f;
    this->velocityIterations = 8;
    this->positionIterations = 3;

    world = new b2World(b2Vec2(0.0, -g));

    //test sol aléatoire
//    Floor *fl = new Floor(1.0, 0.01, true);
//    fl->createArrayb2Vec2(1000);
//    fl->floorInitialize(world);

    //test sol plat de 100m avec mur à 50m
    b2floor = new Floor(50);
    b2floor->createArrayb2Vec2(1000);
    b2floor->floorInitialize(world);

    this->car = std::vector<b2Car*>();
    b2Car* car1 = new b2Car(c, world);
    car.push_back(car1);
    b2Car* car2 = new b2Car(c, world);
    car.push_back(car2);


}

Moteur::Moteur( vector<Car> V, float32 g, float32 timeStep, float32 velocityIterations, float32 positionIterations, float tempsStagnationMax, double length_floor, double var_floor ){
    // crée un monde avec les paramètres physiques proposés, un sol de longueur lenght et de variance var (sol aléatoire)  ajoute les Car de V au monde

    this->timeStep =timeStep ;
    this->velocityIterations = velocityIterations;
    this->positionIterations = positionIterations;
    this->tempsStagnationMax=tempsStagnationMax;

    world = new b2World(b2Vec2(0.0, -g));

    b2floor = new Floor(length_floor,  var_floor);
    b2floor->createArrayb2Vec2(1000);
    b2floor->floorInitialize(world);
    std::cout << "before car init" << '\n';
    this->car = std::vector<b2Car*>();

    for (auto car_V :V){
        std::cout << "before b2car initializeTestCar" << '\n';
        b2Car* voiture = new b2Car(car_V, world);
        std::cout << "mon print" << '\n';
        this->car.push_back(voiture);
    }
}
Moteur::~Moteur(){
    for(auto voiture : car){
        delete voiture;
    }
    delete b2floor;
    delete world;

}

void Moteur::next(float dt){
    // On fait avancer le moteur physique
    unsigned int n = floor(dt/timeStep);
    for (unsigned int i=0; i<n; i++){
            world->Step(this->timeStep, this->velocityIterations, this->positionIterations);
    }
    t += n*timeStep;
    // On met à jour les paramètres des voitures qui ne sont pas pris en compte par Box2D
    for (std::vector<b2Car*>::iterator i = car.begin(); i!=car.end(); i++){
        b2Car* currentCar = (*i);
        if (currentCar->positionMaximale->x < currentCar->m_car->GetPosition().x){
            // on est dans le cas où la voiture avance
            *(currentCar->positionMaximale) = currentCar->m_car->GetPosition();
        }
        else{
            // on est dans le cas où la voiture stagne
            // on incrémente le temps de stagnation de la voiture
            currentCar->tempsStagnation += n*timeStep;
            currentCar->vivante = !currentCar->bloquee(tempsStagnationMax);
        }
    }
    this->classement();
}

void Moteur::printPositions(){
    std::cout << "Au temps : " << t << std::endl;
    for (std::vector<b2Car*>::iterator i = car.begin(); i!=car.end(); i++){
        b2Car* currentCar = (*i);
        std::cout << "\n" << currentCar->nom;
        currentCar->printPosition();
    }
}

/*Crée une fonction qui retourne les positions des centres de chaques voitures.
 * Pour chaque voiture de la course, on transmet un tableau contenant angle, x,y de son centre, et classement
 * */

std::vector<std::array<float, 4> > Moteur::getPosition(){
    // A refaire pourquoi pas avec un for_each !
    std::vector<std::array<float, 4>> positions;
    for (std::vector<b2Car*>::iterator i = car.begin(); i!=car.end(); i++){
        b2Car* currentCar = (*i);
        std::array<float, 4> positionCourante;
        positionCourante[0] = currentCar->m_car->GetAngle();
        //float angle = currentCar->m_car->GetAngle();
        positionCourante[1] = currentCar->m_car->GetPosition().x;
        //float x = currentCar->m_car->GetPosition().x;
        positionCourante[2] = currentCar->m_car->GetPosition().y;
        //float y = currentCar->m_car->GetPosition().y;
        positionCourante[3] = currentCar->classement;
        //float classement; = currentCar->classement;
        positions.push_back(positionCourante);

//        std::cout << "angle = " << positionCourante[0] << std::endl;
//        std::cout << "x = " << positionCourante[1] << std::endl;
//        std::cout << "y = " << positionCourante[2] << std::endl;
//        std::cout << "classement = " << positionCourante[3] << std::endl;
    }
    return positions;
}

std::vector<std::array<float,6> > Moteur::getWheels(){
    // A refaire pourquoi pas avec un for_each !
    std::vector<std::array<float, 6>> positions_angle;
    for (std::vector<b2Car*>::iterator i = car.begin(); i!=car.end(); i++){
        b2Car* currentCar = (*i);
        std::cout << "createshit" << '\n';
        std::array<float, 6> positionCourante;
        positionCourante[0] = currentCar->m_wheel1->GetPosition().x;
        //float angle = currentCar->m_car->GetAngle();
        positionCourante[1] = currentCar->m_wheel1->GetPosition().y;
        //float x = currentCar->m_car->GetPosition().x;
        positionCourante[2] = currentCar->m_wheel1->GetAngle();
        std::cout << "updateshit5" << '\n';
        //float y = currentCar->m_car->GetPosition().y;
        positionCourante[3] = currentCar->m_wheel2->GetPosition().x;
        //float angle = currentCar->m_car->GetAngle();
        positionCourante[4] = currentCar->m_wheel2->GetPosition().y;
        //float x = currentCar->m_car->GetPosition().x;
        positionCourante[5] = currentCar->m_wheel2->GetAngle();
        std::cout << "updateshit8" << '\n';
        //float y = currentCar->m_car->GetPosition().y;
        positions_angle.push_back(positionCourante);
        std::cout << "updateshit9" << '\n';

//        std::cout << "angle = " << positionCourante[0] << std::endl;
//        std::cout << "x = " << positionCourante[1] << std::endl;
//        std::cout << "y = " << positionCourante[2] << std::endl;
//        std::cout << "classement = " << positionCourante[3] << std::endl;
    }

    return positions_angle;
}

bool Moteur::toutesCarBloquees(){
    std::vector<b2Car*>::iterator i = car.begin();
    bool retour = true;
    while (retour && i!=car.end()){
        b2Car* currentCar = (*i);
        retour = currentCar->bloquee(tempsStagnationMax) & retour;
        i++;
    }
    return retour;
}


void Moteur::classement(){
    // Récupération des couples position/voiture
    std::vector<CouplePositionXVoiture> positionVoiture = std::vector<CouplePositionXVoiture> ();
    unsigned int compteur = 0;
    for (std::vector<b2Car*>::iterator i = car.begin(); i!=car.end(); i++){
        b2Car* currentCar = (*i);
        positionVoiture.push_back(CouplePositionXVoiture(currentCar->m_car->GetPosition().x, compteur));
        compteur ++;
    }
    // Tri des positionHorizontale
    compteur = 1;
    std::sort(positionVoiture.begin(), positionVoiture.end(), greater_than());
    // On réaffecte le classment
    for (std::vector<CouplePositionXVoiture>::iterator i = positionVoiture.begin(); i!=positionVoiture.end(); i++){
        CouplePositionXVoiture currentPositionVoiture = (*i);
        (car.at(currentPositionVoiture.voiture))->classement = compteur;
        compteur++;
    }
}

std::vector< std::pair< Car, double> > Moteur::getResult(){ //renvoie la car associé à sa distance parcourrue à la fin
    std::vector < pair < Car, double> > result;
    for(auto b2carCurrent : car){
        result.push_back(std::make_pair(b2carCurrent->voitureparent, (double) b2carCurrent->m_car->GetPosition().x));
    }
    return result;
}
