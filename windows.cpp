#include "windows.h"

windows::windows() : QWidget()
{
    setFixedSize(100, 50);

    m_bouton = new QPushButton("Run !", this);
    m_bouton->setFont(QFont("Comic Sans MS", 14));
    m_bouton->move(0, 0);

    step=default_step;


    timer = new QTimer(this);

    this->a=true;

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(afficher()));

    QObject::connect(m_bouton, SIGNAL(clicked()), this, SLOT(run()));

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0,0,500,300);
    m_view = new QGraphicsView(m_scene,this);
    m_view->move(100,100);
    m_view->show();

    avancement=0;
}

windows::windows(int dt, double gravity) : QWidget()
{
    setFixedSize(1000, 500);


    m_bouton = new QPushButton("Run !", this);
    m_bouton->setFont(QFont("Comic Sans MS", 14));
    m_reset = new QPushButton("Stop", this);

    step=dt;


    timer = new QTimer(this);

    this->a=true;

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(afficher()));

    QObject::connect(m_bouton, SIGNAL(clicked()), this, SLOT(run()));



    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0,0,500,300);


    m_view = new QGraphicsView(m_scene,this);
    m_view->move(0,0);
    m_view->show();

    moteur=new Moteur(gravity);

    double lambda=30;
    std::list<float32>* liste_sol=this->moteur->b2floor->getPoints();
    for(std::list<float32>::iterator it=liste_sol->begin();it!=liste_sol->end();it++){
        float32 x=*it;
        float32 y=*(++it);
        //sol.append(QPointF(5*x,-5*y));
        sol.append(QPointF(lambda*x,-lambda*y));
        /*
        std::cout<<x<<" ,";
        std::cout<<y<<std::endl;*/
    }


    this->m_LCD = new QLCDNumber(5, this);

    // Gestion du layout pour le placement des boutons
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(m_bouton,0,1);
    layout->addWidget(m_reset,0,2);
    layout->addWidget(m_LCD,1,0);
    layout->addWidget(m_view,0,0);
    this->setLayout(layout);

    this->m_Timer_value=0;
    this->m_timer = new QTimer(this);
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(update()));
    this->m_timer->setInterval(100);

    // On connecte les différents signaux et slots
    connect(this->m_bouton, SIGNAL(clicked()), this, SLOT(run()));
    connect(this->m_reset, SIGNAL(clicked()), this, SLOT(reset()));

    avancement=0;

}

void windows::run()
{

    this->m_timer->start();
    timer->start(0);

}

void windows::dessiner(QVector<QPointF> v,QPen pen,QBrush brush){
    m_scene->addPolygon(QPolygonF(v),pen,brush);
}

void windows::afficher()
{

   // m_scene->clear();
    //if(a){

        /*
        QVector<QPointF> vect;
        vect.append(QPointF(avancement+10.0,10.0));
        vect.append(QPointF(avancement+10.0,100.0));
        vect.append(QPointF(avancement+200.0,150.0));
        vect.append(QPointF(avancement+300.0,100.0));
        vect.append(QPointF(avancement+200.0,50.0));
        vect.append(QPointF(avancement+150.0,10.0));
        dessiner(vect);
        //a=false;
        avancement++;
        QVector<QPointF> vect2;
        vect2.append(QPointF(10.0,160.0));
        vect2.append(QPointF(100.0,150.0));
        vect2.append(QPointF(200.0,160.0));
        vect2.append(QPointF(300.0,170.0));
        vect2.append(QPointF(400.0,150.0));
        vect2.append(QPointF(550.0,110.0));

        this->displayFloor(vect2);
        */
    /*
        QVector<QPointF> vect;
        vect.append(QPointF(10.0,10.0));
        vect.append(QPointF(10.0,100.0));
        vect.append(QPointF(200.0,150.0));
        vect.append(QPointF(300.0,100.0));
        vect.append(QPointF(200.0,50.0));
        vect.append(QPointF(150.0,10.0));
        dessiner(vect);


        QVector<QPointF> vect2;
        vect2.append(QPointF(10.0-avancement,160.0));
        vect2.append(QPointF(100.0-avancement,150.0));
        vect2.append(QPointF(200.0-avancement,160.0));
        vect2.append(QPointF(300.0-avancement,170.0));
        vect2.append(QPointF(400.0-avancement,150.0));
        vect2.append(QPointF(550.0-avancement,110.0));

        this->displayFloor(vect2);
        m_scene->setSceneRect(-avancement,0,500,300);

        avancement++;
    }
    else{

        QVector<QPointF> vect;
        vect.append(QPointF(10.0,10.0));
        vect.append(QPointF(10.0,100.0));
        vect.append(QPointF(200.0,150.0));
        vect.append(QPointF(300.0,100.0));
        vect.append(QPointF(200.0,50.0));
        vect.append(QPointF(150.0,10.0));
        dessiner(vect,QPen(Qt::green),QBrush(Qt::yellow));
        a=true;
    }
    */
    double lambda=30;
    m_scene->clear();
    moteur->next(0.1);
    std::cout << "after net" << '\n';
    int indice=-1;
    std::vector<std::array<float, 4> > V =moteur->getPosition();
    int classement = std::numeric_limits<int>::max();
    for(int i=0;i<V.size();i++){
        if(V[i][3]<classement && this->moteur->car[i]->vivante==1){
            indice=i;
            classement=V[i][3];
        }
        QVector<QPointF> vect;
        /*
        double abs=5*V[i][1];
        double ord=5*V[i][2];
        vect.append(QPointF(abs-290,-(10.0+ord)));
        vect.append(QPointF(abs-290,-(100.0+ord)));
        vect.append(QPointF(abs-100,-(150.0+ord)));
        vect.append(QPointF(abs,-(100.0+ord)));
        vect.append(QPointF(abs-100,-(50.0+ord)));
        vect.append(QPointF(abs-150,-(10.0+ord)));
        //dessiner(vect);
        */
        double abs=V[i][1];
        double ord=V[i][2];
        double angle=V[i][0];
        /*
        double x1=-
        x*cos(angle)-y*sin(angle)
        xsin(angle)+ycos(angle)
        */
        /*
        vect.append(QPointF(lambda*(abs-1.5),-lambda*(ord -0.5)));
        vect.append(QPointF(lambda*(abs+1.5),-lambda*(ord -0.5)));
        vect.append(QPointF(lambda*(abs+1.5),-lambda*(ord +0.0)));
        vect.append(QPointF(lambda*(abs+0.0),-lambda*(ord +0.9)));
        vect.append(QPointF(lambda*(abs-1.15),-lambda*(ord+0.9)));
        vect.append(QPointF(lambda*(abs-1.5),-lambda*(ord +0.2)));
        */
        vect.append(rotation(-1.5,-0.5,angle,abs,ord,lambda));
        vect.append(rotation(1.5,-0.5,angle,abs,ord,lambda));
        vect.append(rotation(1.5,0,angle,abs,ord,lambda));
        vect.append(rotation(0,0.9,angle,abs,ord,lambda));
        vect.append(rotation(-1.15,0.9,angle,abs,ord,lambda));
        vect.append(rotation(-1.5,0.2,angle,abs,ord,lambda));


        if(i==0) dessiner(vect);
        else dessiner(vect,QPen(Qt::green),QBrush(Qt::yellow));



    }
    std::vector<std::array<float, 6> > roues =moteur->getWheels();
    for(int i=0;i<roues.size();i++){
        /*
        double x1=roues[i][0];
        double y1=roues[i][1];
        double rayon1=this->moteur->car[i]->radius1;
        //std::cout<<rayon1<<std::endl;
        double x2=roues[i][3];
        double y2=roues[i][4];
        double rayon2=this->moteur->car[i]->radius2;
        m_scene->addEllipse(lambda*(x1-rayon1),-lambda*(y1+rayon1),2*lambda*rayon1,2*lambda*rayon1,QPen(Qt::black),QBrush(Qt::black));
        m_scene->addEllipse(lambda*(x2-rayon2),-lambda*(y2+rayon2),2*lambda*rayon2,2*lambda*rayon2,QPen(Qt::black),QBrush(Qt::black));
        double angle1=roues[i][2];
        double angle2=roues[i][5];
        m_scene->addLine(lambda*x1,-lambda*y1,lambda*(x1+rayon1*cos(angle1)),-lambda*(y1+rayon1*sin(angle1)),QPen(Qt::white));
    */
        displayWheels(i,roues[i],lambda);
    }
    /*
    double abs0=5*V[indice][1];
    double ord0=5*V[indice][2];
    */

    double abs0=lambda*V[indice][1];
    double ord0=lambda*V[indice][2];
    //std::cout<<abs0<<std::endl;

    /*
    QVector<QPointF> vect2;
    vect2.append(QPointF(10.0,160.0));
    vect2.append(QPointF(100.0,150.0));
    vect2.append(QPointF(200.0,160.0));
    vect2.append(QPointF(300.0,170.0));
    vect2.append(QPointF(400.0,150.0));
    vect2.append(QPointF(550.0,110.0));

    this->displayFloor(vect2);
    */
    this->displayFloor();
    std::cout << "dpfloor2" << '\n';
    m_scene->setSceneRect(abs0,-ord0,100,100);
    std::cout << "jsp" << '\n';

    if(indice==-1){
        std::vector< pair< Car, double> > results = moteur->getResult();
        delete moteur;
        // Update génétique
        std::cout << "starting gen generation" << '\n';
        std::vector<Car> new_cars = preprocessing::generateCars(1);
        std::cout << "ending gen generation" << '\n';
        moteur=new Moteur(9.8, new_cars[0]);
        std::cout << "moteur créé" << '\n';
    }

    timer->start(step);
    std::cout << "simulation step" << '\n';
}

void windows::reset()
{
    this->m_timer->stop();
    m_Timer_value=0;
    m_LCD->display(m_Timer_value);
    timer->stop();
}

void windows::update()
{
    m_Timer_value++;
    m_LCD->display(m_Timer_value);
}

QPointF windows::cartesien(double x, double y, double angle, double longueur, double repere){
    double x0=x+longueur*cos(angle+repere);
    double y0=y+longueur*sin(angle+repere);
    return QPointF(x0,y0);
}

void windows::displayFloor(QVector<QPointF> v){
    QPointF p1=v.first();
    v.pop_front();
    while(!v.isEmpty()){
        QPointF p2=v.first();
        v.pop_front();
        m_scene->addLine(QLineF ( p1, p2));
        p1=p2;
    }

}

void windows::displayFloor(){
    this->displayFloor(this->sol);
}

QPointF windows::rotation(double x0, double y0, double angle,double abs, double ord, double lambda){
    double x=x0*cos(angle)-y0*sin(angle);
    double y=x0*sin(angle)+y0*cos(angle);
    return QPointF(lambda*(x+abs),-lambda*(y+ord));
}

void windows::displayWheels(int i,std::array<float, 6> roues,double lambda){
    double x1=roues[0];
    double y1=roues[1];
    double rayon1=this->moteur->car[i]->radius1;
    double x2=roues[3];
    double y2=roues[4];
    double rayon2=this->moteur->car[i]->radius2;
    m_scene->addEllipse(lambda*(x1-rayon1),-lambda*(y1+rayon1),2*lambda*rayon1,2*lambda*rayon1,QPen(Qt::black),QBrush(Qt::black));
    m_scene->addEllipse(lambda*(x2-rayon2),-lambda*(y2+rayon2),2*lambda*rayon2,2*lambda*rayon2,QPen(Qt::black),QBrush(Qt::black));
    double angle1=roues[2];
    double angle2=roues[5];
    m_scene->addLine(lambda*x1,-lambda*y1,lambda*(x1+rayon1*cos(angle1)),-lambda*(y1+rayon1*sin(angle1)),QPen(Qt::white));
    m_scene->addLine(lambda*x2,-lambda*y2,lambda*(x2+rayon2*cos(angle2)),-lambda*(y2+rayon2*sin(angle2)),QPen(Qt::white));
}
