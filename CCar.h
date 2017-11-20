//
//  CCar.h
//  Box2D
//
//  Created by Lucas Gonzalez on 15/11/2016.
//
//
#include <iostream>
#include <vector>
#include "../car.h"
#include "../car.cpp"

#include "../floor.h"



#ifndef CCar_h
#define CCar_h


class CCar : public Test
{
public:
    CCar(Car c) {
        

        
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, -20.0f);
        b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(500.0f, 17.0f);
        
        b2FixtureDef fdGround;
        fdGround.shape = &groundBox;
        fdGround.density = 0.0f;
        fdGround.friction = 0.9f;
        fdGround.filter.categoryBits = 0x0003;
        groundBody->CreateFixture(&fdGround);//shape, density
        
        
        //Floor f(1.0,1.0,0.5);
        //f.floorInitialize(*m_world);
        
        
        b2Body* m_car;
        b2Body* m_wheel1;
        b2Body* m_wheel2;
        
        float32 m_hz = 4.0;
        float32 m_zeta=0.7;
        
        
        
        float32 m_speed;
        b2WheelJoint* m_spring1;
        b2WheelJoint* m_spring2;
        
        b2PolygonShape chassis;
        vector<pair<double,double> > pos = c.get_points_xy();
        
        b2Vec2 * vertices = new b2Vec2[c.N];
        for(int i=0;i<c.N;++i)
        {
            std::cout<<(float)pos[i].first<<" / "<<(float)pos[i].second<<std::endl;
            vertices[i].Set((float)pos[i].first,(float)pos[i].second);
        }

        chassis.Set(vertices, c.N);
        
        
        int iw1 = c.get_wheels_index()[0];
        int iw2 = c.get_wheels_index()[1];
        
        
        
        b2CircleShape circle1;
        b2CircleShape circle2;

        
        circle1.m_radius = (float)c.r1;
        circle2.m_radius = (float)c.r2;

        
        
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(0.0f, 1.0f);
        m_car = m_world->CreateBody(&bd);
        
        
        b2FixtureDef fdChassis;
        fdChassis.shape = &chassis;
        fdChassis.density = 1.0f;
        fdChassis.filter.categoryBits = 0x0001;
        fdChassis.filter.maskBits = 0x0002;

        
        m_car->CreateFixture(&fdChassis);


        
        
        
        b2FixtureDef fd1;
        fd1.shape = &circle1;
        fd1.density = 1.0f;
        fd1.friction = 0.9f;
        fd1.filter.categoryBits = 0x0002;
        fd1.filter.maskBits = 0x0001;
        
        
        
        
        b2FixtureDef fd2;
        fd2.shape = &circle2;
        fd2.density = 1.0f;
        fd2.friction = 0.9f;
        
        b2BodyDef bd1;
        bd1.type = b2_dynamicBody;
        
        
        for(int i=0;i<c.N;++i)
        {
            std::cout<<(float)pos[i].first<<" / "<<(float)pos[i].second<<std::endl;
        }
        std::cout<<(float)pos[iw1].first<<" /ROUE 1/ "<<iw1<<" "<<(float)pos[iw1].second<<std::endl;
        std::cout<<(float)pos[iw2].first<<" /ROUE 2/ "<<iw2<<" "<<(float)pos[iw2].second<<std::endl;

        
        bd1.position.Set((float)pos[iw1].first,(float)pos[iw1].second);
        m_wheel1 = m_world->CreateBody(&bd1);
        m_wheel1->CreateFixture(&fd1);
        
        
        
        /*
        b2BodyDef bd2;
        bd2.type = b2_dynamicBody;
        bd2.position.Set((float)pos[iw2].first,(float)pos[iw2].second);
        m_wheel2 = m_world->CreateBody(&bd2);
        m_wheel2->CreateFixture(&fd2);
        */
        
        b2WheelJointDef jd;
        b2Vec2 axis(0.0f, 0.1f);
        
        jd.Initialize(m_car, m_wheel1, *(new b2Vec2((float)pos[iw1].first,(float)pos[iw1].second)), axis);
        
       // void Initialize(b2Body* bodyA, b2Body* bodyB, const b2Vec2& anchor, const b2Vec2& axis);
        
        jd.motorSpeed = -10.0f;
        jd.maxMotorTorque = 60.0f;
        jd.enableMotor = false;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        m_spring1 = (b2WheelJoint*)m_world->CreateJoint(&jd);
        /*
        jd.Initialize(m_car, m_wheel2, *(new b2Vec2((float)pos[iw2].first,(float)pos[iw2].second)), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 60.0f;
        jd.enableMotor = false;
        jd.frequencyHz = 4.0f;
        jd.dampingRatio = 0.5;
        m_spring2 = (b2WheelJoint*)m_world->CreateJoint(&jd);*/
        
        
    } //do nothing, no scene yet
    
    void Step(Settings* settings)
    {
        //run the default physics and rendering
        Test::Step(settings);
        
        //show some text in the main screen
        m_debugDraw.DrawString(5, m_textLine, "Now we have a foo test");
        m_textLine += 15;
        
        
        
    }
    
    static Test* Create()
    {
        vector<pair<double, double> > angles_distances;
        angles_distances.push_back(std::make_pair (0,2));
        angles_distances.push_back(std::make_pair (3,2));
        angles_distances.push_back(std::make_pair (6,2));
        angles_distances.push_back(std::make_pair (9,2));

        Car * c = new Car();//4,1.0, 1.0, 1.0, 1.0, 4.0, 1.0, angles_distances);
        return new CCar(*c);
    }
};


#endif /* CCar_h */
