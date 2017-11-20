#include "b2Car.h"

b2Car::b2Car()
{
}

void b2Car::initializeTestCar(b2World* m_world){

    radius1 = 0.4;
    radius2 = 0.4;
    float m_hz = 4.0f;
    float m_zeta = 0.7f;
    vivante = true;
    nom = "Voiture de test";
    tempsStagnation = 0;
    positionMaximale = new b2Vec2(0.0, 0.0);
    classement = -1;

    b2PolygonShape chassis;
    b2Vec2 vertices[8];
    vertices[0].Set(-1.5f, -0.5f);
    vertices[1].Set(1.5f, -0.5f);
    vertices[2].Set(1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(-1.15f, 0.9f);
    vertices[5].Set(-1.5f, 0.2f);
    chassis.Set(vertices, 6);

    b2CircleShape circle;
    circle.m_radius = 0.4f;


    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 1.0f);
    b2FixtureDef fd_car;
    fd_car.shape = &chassis;
    fd_car.density = 1.0f;
    fd_car.friction = 0.9f;
    fd_car.filter.groupIndex = -1;
    m_car = m_world->CreateBody(&bd);
    m_car->CreateFixture(&fd_car);

    b2FixtureDef fd;
    fd.shape = &circle;
    fd.density = 1.0f;
    fd.friction = 0.9f;
    fd.filter.groupIndex = -1;


    bd.position.Set(-1.0f, 0.35f);
    m_wheel1 = m_world->CreateBody(&bd);
    m_wheel1->CreateFixture(&fd);


    bd.position.Set(1.0f, 0.4f);
    m_wheel2 = m_world->CreateBody(&bd);
    m_wheel2->CreateFixture(&fd);

    b2WheelJointDef jd;
    b2Vec2 axis(0.0f, 1.0f);

    jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
    jd.motorSpeed = -10.0f;
    jd.maxMotorTorque = 20.0f;
    jd.enableMotor = true;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2WheelJoint* m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

    jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
    jd.motorSpeed = -10.0f;
    jd.maxMotorTorque = 10.0f;
    jd.enableMotor = true;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2WheelJoint* m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
}

void b2Car::initializeTestCarNulle(b2World* m_world){

    radius1 = 0.4;
    radius2 = 0.4;
    float m_hz = 4.0f;
    float m_zeta = 0.7f;
    vivante = true;
    nom = "Voiture de test nulle";
    tempsStagnation = 0;
    positionMaximale = new b2Vec2(0.0, 0.0);
    classement = -1;

    b2PolygonShape chassis;
    b2Vec2 vertices[8];
    vertices[0].Set(-1.5f, -0.5f);
    vertices[1].Set(1.5f, -0.5f);
    vertices[2].Set(1.5f, 0.0f);
    vertices[3].Set(0.0f, 0.9f);
    vertices[4].Set(-1.15f, 0.9f);
    vertices[5].Set(-1.5f, 0.2f);
    chassis.Set(vertices, 6);

    b2CircleShape circle;
    circle.m_radius = 0.4f;


    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 1.0f);
    b2FixtureDef fd_car;
    fd_car.shape = &chassis;
    fd_car.density = 1.0f;
    fd_car.friction = 0.9f;
    fd_car.filter.groupIndex = -1;
    m_car = m_world->CreateBody(&bd);
    m_car->CreateFixture(&fd_car);

    b2FixtureDef fd;
    fd.shape = &circle;
    fd.density = 1.0f;
    fd.friction = 0.9f;
    fd.filter.groupIndex = -1;

    bd.position.Set(-1.0f, 0.35f);
    m_wheel1 = m_world->CreateBody(&bd);
    m_wheel1->CreateFixture(&fd);
    bd.position.Set(1.0f, 0.4f);
    m_wheel2 = m_world->CreateBody(&bd);
    m_wheel2->CreateFixture(&fd);

    b2WheelJointDef jd;
    b2Vec2 axis(0.0f, 1.0f);

    jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
    jd.motorSpeed = -2.0f;
    jd.maxMotorTorque = 20.0f;
    jd.enableMotor = true;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2WheelJoint* m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);

    jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 10.0f;
    jd.enableMotor = false;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2WheelJoint* m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
}

void b2Car::printPosition(){
    b2Vec2 position = this->m_car->GetPosition();
    float32 angle = this->m_car->GetAngle();
    std::cout << " X : " << position.x << " \t Y : " << position.y << " \t Angle : " << angle << "\t Temps de stagnation : " << tempsStagnation << "Classement :" << classement <<  std::endl;
}

bool b2Car::bloquee(float tempsStagnationMax){
    return tempsStagnation > tempsStagnationMax;
}

//b2Car::b2Car(Car car){
//    //constructeur qui crée la forme + les joints + les roues etc ...
//}



void b2Car::creationChassis(b2Body* m_car, const vector<pair<double,double> > &pos, Car &c){
/* Prend en paramètre un b2Body et pos, la liste des positions des sommets d'une car
Attention, la voiture doit déjà avoir été ajoutée au monde */

//    b2Vec2 * vertices = new b2Vec2[c.N]; //conversion en b2Vec2
//    for(int i=0;i<c.N;++i)
//    {
//        std::cout<<(float)pos[i].first<<" / "<<(float)pos[i].second<<std::endl;
//        vertices[i].Set((float)pos[i].first,(float)pos[i].second);
//    }


    for(int i = 0; i<c.N; i++){ //décomposition en triangle élémentaire du polygone chassi, un sommet du triangle au centre et les autres sur deux sommets
        b2PolygonShape morceauChassis;
        b2Vec2* triangle = new b2Vec2[3];
        triangle[0].SetZero();
        triangle[1].Set((float32)pos[i].first, (float32)pos[i].second);
//        int k = (i+1)%(c.N);
        triangle[2].Set((float32)pos[( (i+1)%(c.N) )].first, (float32)pos[( (i+1)%(c.N) )].second); //le modulo permet de gérer le retour au premier sommet quand on arrive au dernier sommet
//        triangle[2].Set(vertices[( (i+1)%(c.N) )].x, vertices[( (i+1)%(c.N) )].y);
        morceauChassis.Set(triangle, 3);

        b2FixtureDef fdChassis;
        fdChassis.shape = &morceauChassis;
        fdChassis.density = (float)(c.d);
        fdChassis.friction = 0.9f;
        fdChassis.filter.groupIndex = -1;

        m_car->CreateFixture(&fdChassis); //ajout fixture sur m_car,attention car doit déjà avoir été donné au world
    }

}

b2Car::b2Car(Car car, b2World* m_world){

    vivante = true;
    radius1 = car.r1;
    radius2 = car.r2;
    voitureparent = car;
    float m_hz = 4.0f;
    float m_zeta = 0.7f;
    float m_speed = -50.0f;

    float hauteur = 1.0f; //hauteur de laché des voitures
    //avec cette hauteur la voiture par défaut se cabre complètement et roule en faisant une roue arrière
    //avec une hauteur plus grande, elle fait des tours sur elle-même

    nom = "Voiture";
    tempsStagnation = 0;
    positionMaximale = new b2Vec2(0.0, 0.0);
    classement = -1;

    //vrai fonction du constructeur
    vector<pair<double,double> > pos = car.get_points_xy(); //ensemble des positions des sommets du chassis avec origine situé au centre des roues en x et à r1 (rayon roue 1) en y, getpoint_xy renvoie n'importe quoi

//code en dur de la position des sommets de la voiture pour tester le programme
   //deux voitures possibles, un rectangle ou celle de testInit

//    vector<pair <double, double> > pos;
////     pos.push_back(std::make_pair(-2.0, -1.0));
////     pos.push_back(std::make_pair(2.0, -1.0));
////     pos.push_back(std::make_pair(2.0, 2.0));
////     pos.push_back(std::make_pair(2.0, -2.0));

//     //test avec la voiture par défaut
//     pos.push_back(std::make_pair(-1.5, -0.5));
//     pos.push_back(std::make_pair(1.5, -0.5));
//     pos.push_back(std::make_pair(1.5, -0.0));
//     pos.push_back(std::make_pair(0.0, 0.9));
//     pos.push_back(std::make_pair(-1.15, 0.9));
//     pos.push_back(std::make_pair(-1.5, 0.2));


//    std::cout<<(float)pos[iw1].first<<" /ROUE 1/ "<<iw1<<" "<<(float)pos[iw1].second<<std::endl;
//    std::cout<<(float)pos[iw2].first<<" /ROUE 2/ "<<iw2<<" "<<(float)pos[iw2].second<<std::endl;

//  création du bodydef pour m_car, déclaré comme body dynamique (qui peut bouger) et ajout de m_car au monde
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, hauteur); // hauteur initiale de laché des voitures, 10(m) semble ok
    m_car = m_world->CreateBody(&bd);

// la création de l'envellope de la voiture (fixture) est cachée dans creation chassis

    b2Car::creationChassis(m_car, pos, car);

//création des fixtures pour les roues
    int iw1 = car.get_wheels_index()[0];
    int iw2 = car.get_wheels_index()[1];


    //code en dur pour les positions des roues pour les tests
//    int iw1 = 0;
//    int iw2 = 1;

    b2CircleShape circle1;
    b2CircleShape circle2;

    circle1.m_radius = (float)car.r1;
    circle2.m_radius = (float)car.r2;

    b2FixtureDef fd1;
    fd1.shape = &circle1;
    fd1.density = (float)(car.d1);
    fd1.friction = 0.9f;
    fd1.filter.groupIndex = -1;

    b2FixtureDef fd2;
    fd2.shape = &circle2;
    fd2.density = (float)(car.d2);
    fd2.friction = 0.9f;
    fd2.filter.groupIndex = -1;

// création des b2body  pour les roues

    b2BodyDef bd1;
    bd1.type = b2_dynamicBody;

    bd1.position.Set((float)pos[iw1].first,(float)pos[iw1].second + hauteur);  //la voiture a été remonté de 4m, idem pour les roues

    // code en dur pour la voiture de test de la position des roues
    //bd1.position.Set(-1.0f, 0.35f - 1.0f +hauteur);

    m_wheel1 = m_world->CreateBody(&bd1);
    m_wheel1->CreateFixture(&fd1);

    b2BodyDef bd2;
    bd2.type = b2_dynamicBody;
    bd2.position.Set((float)pos[iw2].first,(float)pos[iw2].second + hauteur);

    // code en dur pour la voiture de test de la position des roues
    //bd2.position.Set(1.0f, 0.4f -1.0f +hauteur);

    m_wheel2 = m_world->CreateBody(&bd2);
    m_wheel2->CreateFixture(&fd2);

// création des suspensions
    b2WheelJointDef jd;
    jd.motorSpeed = m_speed;
    jd.maxMotorTorque = 60.0f;
    jd.enableMotor = true;
    jd.frequencyHz = m_hz;
    jd.dampingRatio = m_zeta;
    b2Vec2 axis(0.0f, 1.0f); //axe de la suspension, coordonnée dans le repère du chassis

    jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis); //initialize suppose que les objets sont déjà à la bonne place et les contraints à une rotation autour de m_wheel-> Get position

    b2WheelJoint* m_spring1;
    m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);
//    (b2WheelJoint*)m_world->CreateJoint(&jd);

    jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);

    b2WheelJoint* m_spring2;
    m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);
//    (b2WheelJoint*)m_world->CreateJoint(&jd);


}

vector<pair<double,double> > b2Car::get_chassis(){ //renvoie le chassis de la voiture parent
    return voitureparent.get_points_xy();
}
