#include "Floor.h"

/* Permet de créer un sol de test où tous les blocs sont plats*/
Floor::Floor(){
    this->length=1.0;
    this->variance=0.1;
    this->p=new std::list<b2Vec2> ();
    this->chaos=false;
    for(int i=0;i<101;i++){
        p->push_back(b2Vec2(i*length-10.0,-2.0));
    }
}

// Sol plat avec un mur à x = mur
// Pour les tests de temps de stagnation
Floor::Floor(float mur){
    this->length=1.0;
    this->variance=0.1;
    this->p=new std::list<b2Vec2> ();
    for(int i=0;i<101;i++){
        p->push_back(b2Vec2(i*length-10.0,-2.0));
    }
    // Construction du mur, #Trump
    p->push_back(b2Vec2(mur, 100.0));
    p->push_back(b2Vec2(mur, -100.0));
    p->push_back(b2Vec2(mur, 100.0));
}

/* Permet de créer un sol sont on peut fixer les paramètres des blocs*/
Floor::Floor(double l, double v){
    this->length=l;
    this->variance=v;
    this->p=new std::list<b2Vec2>();
}

/* Permet de créer un sol sont on peut fixer les paramètres des blocs*/
Floor::Floor(double l, double v, bool c){
    this->length=l;
    this->variance=v;
    this->chaos = c;
    this->p=new std::list<b2Vec2>();
}

double Floor::getLength(){
    return this->length;
}

double Floor::getVariance(){
    return this->variance;
}

//Crée un tableau de points permettant ensuite de générer le sol
//Un mur est ajouté à la fin pour stopper les voitures à la fin du circuit
void Floor::createArrayb2Vec2(int N){
    double x = -10.0;
    double y = -2.0;
    p->push_back(b2Vec2(x, y));

    //faire du vrai aléatoire grâce à l'horloge
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    for (int i = 1; i < N; i++){
        x = x + this->length;
        std::normal_distribution<double> distribution(0,this->variance*i);
        y = distribution(generator);
        // std::cout << y << std::endl;
        p->push_back(b2Vec2(x, y));
    }
   return;
}


// assigne le sol (comme succession des points à notre univers)
void Floor::floorInitialize(b2World* world){
    // objet b2box du sol
    b2Body* ground = NULL;

    // on l'assigne au monde
    b2BodyDef bd;
    ground = world->CreateBody(&bd);

    // chaque morceau de notre sol est une edge
    b2EdgeShape edge;

    // on donne les caractéristique du sol (utilisé pour chaque morceau ajouté)
    b2FixtureDef fd;
    fd.shape = &edge;
    fd.density = 0.0f;
    fd.friction = 0.9f;


    // q permet de reconstruire p après l'initialisation
    std::list<b2Vec2>* q = new std::list<b2Vec2>();

    // on parcourt la liste des points en ajoutant une à une les edges
    while(p->size() > 2){
        // on récupère les deux premiers points
        b2Vec2 q1 = p->front();
        p->pop_front();
        q->push_back(q1);
        b2Vec2 q2 = p->front();
        q->push_back(q2);

        // on crée le fixture de l'edge suivant et on l'ajoute
        edge.Set(q1, q2);
        ground->CreateFixture(&fd);
    }
    q->push_back(p->front());
    p=q;
}
//Convertit la liste de b2Vec2 en une liste de float32 à destination de l'UI. Les coordonnées x et y s'enchainent à la suite.
std::list<float32> *Floor::getPoints(){
    std::list<float32>* res=new std::list<float32>();
    for (std::list<b2Vec2>::iterator iiplist=(this->p->begin()); iiplist!=(p->end()); iiplist++){
        res->push_back((*iiplist).x);
        res->push_back((*iiplist).y);
    }
    return res;
}

/*
void Floor::extend(){
    //TO DO :
    Si le sol est trop court par rapport à la distance déjà parcourue par la meilleure voiture prolonger le sol
        Méthode peut être facultative, il suffit peut être de le créer assez grand au départ
        }
*/
