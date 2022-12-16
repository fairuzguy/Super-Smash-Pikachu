#ifndef HITBOX
#define HITBOX 0x0008 /// 0000 0000 0000 1000


#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>
#include <iostream>
#include <fstream>

/// Hitbox class

using namespace std;
using namespace sf; //for graphics


class Hitbox : RectangleShape
{
    public :
        Hitbox(b2World &world, float dx, float dy, float x, float y, float coef, b2BodyType type = b2_dynamicBody)
        {
            b2BodyDef bodyDef;
            bodyDef.position.Set((x + dx/2.0)/pixels_per_meter, (y + dy/2.0)/pixels_per_meter);
            bodyDef.type = type;
            bodyDef.linearDamping = 0.00;
            b2PolygonShape b2shape;
            b2shape.SetAsBox(dx/pixels_per_meter/2.0, dy/pixels_per_meter/2.0);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0;
            fixtureDef.friction = coef;
            fixtureDef.restitution = 0.0;
            fixtureDef.shape = &b2shape;
            fixtureDef.isSensor = true;

            body = world.CreateBody(&bodyDef);
            body->CreateFixture(&fixtureDef);

            //b2Filter filter;
            //filter.categoryBits = 0x0002;
            //filter.maskBits = 0x0004;

            //for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
            //{
            //    filter = f->GetFilterData();
                //filter.groupIndex = 0;
                //filter.groupIndex = -1;


            //    f->SetFilterData(filter);

            //}


            this->setPosition(x, y);
            this->setSize(Vector2f(dx, dy));
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

        bool checkCollision()
        {
            for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
                if (edge->contact->IsTouching()) return true;
            }
            return false;
        }

        b2Body* getBody()
        {
            return body;
        }

        void destroy(b2World &world)
        {
            world.DestroyBody(body);
        }

        Vector2f position()
        {
            return Vector2f(this->getPosition().x, this->getPosition().y);
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
#endif // Hitbox

