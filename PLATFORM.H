#ifndef PLATFORM
#define PLATFORM 0x0002 /// 0000 0000 0000 0010

/// Platform Class

#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>
#include <Box2D/Box2D.h>


using namespace sf; //for graphics

class Platform : public RectangleShape
{
    public :
        Platform(b2World &world, float dx, float dy, float x, float y, Color c, float coef, b2BodyType type = b2_staticBody)
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

            body = world.CreateBody(&bodyDef);
            body->CreateFixture(&fixtureDef);

            b2Filter filter;
            //filter.categoryBits = 0x0002;
            //filter.maskBits = 0x0004;

            for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
            {
                filter = f->GetFilterData();
                filter.categoryBits = 0x0002;
                filter.maskBits = 0x0004;


                f->SetFilterData(filter);

            }


            this->setFillColor(c);
            this->setPosition(x, y);
            this->setSize(Vector2f(dx, dy));
        }

        bool isHit(b2World &world)
        {
            for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
                if (edge->contact->IsTouching())
                {



                    return true;
                }
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




    private :
        b2Body* body;

};

#endif // Platform
