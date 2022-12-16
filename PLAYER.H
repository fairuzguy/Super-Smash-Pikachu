#ifndef PLAYER
#define PLAYER 0x0004 /// 0000 0000 0000 0100

#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>
#include <iostream>
#include <fstream>

/// Player Class

/// |----------------------- https://www.spriters-resource.com/custom_edited/supersmashbroscustoms/sheet/17182/

using namespace std;
using namespace sf; //for graphics

const float Pi = 3.14159;
const float pixels_per_meter = 32.0;
const float deg_per_radian = 180.0 / Pi;

const float ConversionSpeed = 2.1155742440683000451251986259768;
const float Frametimevalue = 1 / 60;

class Player : public Sprite
{
    public :
        Player(b2World &world, float x, float y, string triangle_file, const sf::Texture &t)
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
            /// fixtureDef.isSensor = true;
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
                    vertices[j].Set(vx/pixels_per_meter,vy/pixels_per_meter);
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
                filter.categoryBits = 0x0004;

                filter.maskBits = (0x0002) | (~0x0004);
                //filter.groupIndex = -2;
                f->SetFilterData(filter);

            }
            sprint = false;
            CanJump = true;
            CanMove = true;


            myfile.close();

            lives = 5;


        }

        float getBoxPositionX()
        {
            return (body->GetPosition().x);
        }

        float getBoxPositionY()
        {
            return (body->GetPosition().y);
        }

        void setColour(Color c)
        {
            this->setColor(c);
        }

        Color getColour()
        {
            return this->getColor();
        }

        void setBoxPosition(Vector2f xy)
        {
            body->SetTransform(b2Vec2(xy.x / pixels_per_meter, xy.y / pixels_per_meter), 0);
        }

        void setVelocity(sf::Vector2f vel)
        {
            body->SetLinearVelocity(b2Vec2(vel.x,vel.y));

        }

        bool checkCollision()
        {
            for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
                if (edge->contact->IsTouching()) return true;
            }
            return false;
        }

        void Jump()
        {
            body->ApplyLinearImpulseToCenter(b2Vec2(0, -120), 1);
        }

        void Rise(float x)
        {
            body->ApplyLinearImpulseToCenter(b2Vec2(0, x), 1);
        }

        void Move(float x)
        {
            body->ApplyLinearImpulseToCenter(b2Vec2(x, 0), 1);
        }

        void updatePosition()
        {
            this->setPosition(body->GetPosition().x*pixels_per_meter, body->GetPosition().y*pixels_per_meter);
        }

        void setSprint(bool run)
        {
            sprint = run;
        }

        bool getSprint()
        {
            return sprint;
        }

        float getVerticalVelocity()
        {
            return body->GetLinearVelocity().y;
        }

        float getHorizontalVelocity()
        {
            return body->GetLinearVelocity().x;
        }

        b2Body* getBody()
        {
            return body;
        }

        bool isTouchingGround(b2Body* p1)
        {
            for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
                if (edge->other == p1) {
                    if (edge->contact->IsTouching()) {
                       return true;
                       Grounded = true;
                    }
                }
            }
            return false;
        }

        Vector2f getSize()
        {
            return this->getSize();
        }

        float getMass()
        {
            return body->GetMass();
        }

        void setJump1(bool x)
        {
            Jump1 = x;
        }

        void setJump2(bool x)
        {
            Jump2 = x;
        }

        bool getJump1()
        {
            return Jump1;
        }

        bool getJump2()
        {
            return Jump2;
        }

        void setGrounded(bool x)
        {
            Grounded = x;
        }

        bool isGrounded()
        {
            return Grounded;
        }

        void setInvincible(bool x)
        {
            Invincible = x;
        }

        bool isInvincible()
        {
            return Invincible;
        }

        void setUntargetable(bool x)
        {
            Untargetable = x;
        }

        bool isUntargetable()
        {
            return Untargetable;
        }

        void setAttacking(bool x)
        {
            Attacking = x;
        }

        bool isAttacking()
        {
            return Attacking;
        }

        bool isFalling()
        {
            if (this->getVerticalVelocity() > 0)
            {
                return true;
            }
            else
                return false;
        }

        bool isRising()
        {
            if (this->getVerticalVelocity() <= 0)
            {
                return true;
            }
            else
                return false;
        }

        void setUnderAttack(bool x)
        {
            UnderAttack = x;
        }

        bool isUnderAttack()
        {
            return UnderAttack;
        }

        void setMoving(bool x)
        {
            Moving = x;
        }

        bool isMoving()
        {
            return Moving;
        }

        void setLeft(bool x)
        {
            Left = x;
        }

        bool isLeft()
        {
            return Left;
        }

        void setRight(bool x)
        {
            Right = x;
        }

        bool isRight()
        {
            return Right;
        }

        void setSideSpecialLeft(bool x)
        {
            SideSpecialLeft = x;
        }

        bool isSideSpecialLeft()
        {
            return SideSpecialLeft;
        }

        void setSideSpecialRight(bool x)
        {
            SideSpecialRight = x;
        }

        bool isSideSpecialRight()
        {
            return SideSpecialRight;
        }

        void setCanMove(bool x)
        {
            CanMove = x;
        }

        bool getCanMove()
        {
            return CanMove;
        }

        void setPulse(bool x)
        {
            Pulse = x;
        }

        bool getPulse()
        {
            return Pulse;
        }

        void setCanJump(bool x)
        {
            CanJump = x;
        }

        bool getCanJump()
        {
            return CanJump;
        }

        float getDamage()
        {
            return Damage;
        }

        void setDamage(float x)
        {
            Damage = x;
        }




        void copyStats(Player x)
        {
            this->setJump1(x.getJump1());
            this->setJump2(x.getJump2());
            this->setGrounded(x.isGrounded());
            this->setInvincible(x.isInvincible());
            this->setUntargetable(x.isUntargetable());
            this->setAttacking(x.isAttacking());
            this->setUnderAttack(x.isUnderAttack());
            this->setMoving(x.isMoving());
            this->setLeft(x.isLeft());
            this->setRight(x.isRight());
            this->setCanMove(x.getCanMove());
            this->setCanJump(x.getCanJump());
            this->setPulse(x.getPulse());
        }

        void setLives(float x)
        {
            lives = x;
        }

        float getLives()
        {
            return lives;
        }











    private :
        b2Body* body;
        bool Jump1;
        bool Jump2;
        bool Grounded;
        bool Invincible;
        bool Untargetable;
        bool Attacking;
        bool Falling;
        bool Rising;
        bool UnderAttack;
        bool CliffHanging;
        bool Moving;
        bool Left;
        bool Right;
        float Damage;
        bool SideSpecialRight;
        bool SideSpecialLeft;
        bool CanMove;
        bool Pulse;
        bool CanJump;


        bool sprint;

        int lives;




};
#endif // Player
