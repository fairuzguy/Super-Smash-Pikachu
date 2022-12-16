#ifndef SENSORS
#define SENSORS 0x0000 /// 0000 0000 0000 0000


#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>
#include <iostream>
#include <fstream>

/// Sensor Class

using namespace std;
using namespace sf; //for graphics

//const float Pi = 3.14159;
//const float pixels_per_meter = 32.0;
//const float deg_per_radian = 180.0 / Pi;

//const float ConversionSpeed = 2.1155742440683000451251986259768;
//const float Frametimevalue = 1 / 60;

class Sensors : public Sprite
{
    public :
        Sensors(b2World &world, float x, float y, string triangle_file, const sf::Texture &t, float offsetx)
        {
            size_t n;
            float vx , vy;
            b2Vec2 vertices[3];
            b2PolygonShape polygonShape;

            b2BodyDef bodyDef;
            bodyDef.position.Set(x/pixels_per_meter, y/pixels_per_meter);
            bodyDef.type = b2_dynamicBody;
            bodyDef.linearDamping = 0.00;

            b2FixtureDef fixtureDef;

            fixtureDef.density = 1.0;
            fixtureDef.isSensor = true;
            fixtureDef.friction = 0.1;
            fixtureDef.restitution = 0.0;


            body = world.CreateBody(&bodyDef);

            ifstream myfile;
            myfile.open(triangle_file);
            if (!myfile.is_open()) {
                cout<<"No Vertex file located"<<endl;
                //return 0;
            }
            else {
                cout<<"Vertex file opened successfully"<<endl;
            }
            myfile>>n;
            cout<<n<<endl;
            for (size_t i= 0; i < n; i++ ) {
                for (size_t j = 0; j < 3; j++) {
                    myfile>>vx;
                    myfile>>vy;
                    vertices[j].Set((vx-offsetx)/pixels_per_meter,vy/pixels_per_meter);
                }
                polygonShape.Set(vertices, 3);
                fixtureDef.shape = &polygonShape;
                body->CreateFixture(&fixtureDef);
            }

            this->setPosition(x,y);
            this->setTexture(t);

            body->SetFixedRotation(1);

            b2Filter filter;
            for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
            {
                filter = f->GetFilterData();
                filter.categoryBits = 0x0000;
                //filter.maskBits = 0x0008 | (~0x0004 & ~0x0001);


                f->SetFilterData(filter);

            }
            sprint = false;


            myfile.close();


        }

        void updatePosition(Player Pika)
        {
            this->setPosition(Pika.getPosition().x, Pika.getPosition().y);
            body->SetTransform(b2Vec2(Pika.getBody()->GetPosition().x, Pika.getBody()->GetPosition().y), 0);
        }

        bool isColliding(b2Body* p1)
        {
            bool checked = false;
            for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
                if (!checked)
                {
                    if (edge->other == p1) {
                    if (edge->contact->IsTouching()) {
                       return true;
                       checked = true;


                        }
                    }
                }
            }
            return false;
        }

        float getBoxPositionX()
        {
            return (body->GetPosition().x);
        }

        float getBoxPositionY()
        {
            return (body->GetPosition().y);
        }




    private :
        b2Body* body;
        bool sprint;



};
#endif // Sensors

