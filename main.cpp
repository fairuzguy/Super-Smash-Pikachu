#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Aspect.h"
#include "Camera.h"
#include "Sensors.h"
#include "Hitbox.h"
#include "Buttons.h"

using namespace std;
using namespace sf;

float findDx(float x1, float x2)  /// Finds "Distance" x
{
    if (x2 - x1 >= 0)
        return (x2 - x1);
    else
        return (x1 - x2);
}
float findDy(float y1, float y2) /// Finds "Distance" y
{
    if (y2 - y1 >= 0)
        return (y2 - y1);
    else
        return (y1 - y2);
}
float findDt(float x1, float x2, float y1, float y2)  /// Finds "Distance" total
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
float findAx(float x1, float x2) /// Finds "Average" x
{
    return (x1 + x2) / 2;
}
float findAy(float y1, float y2) /// Finds "Average" y
{
    return (y1 + y2) / 2;
}

int main()
{
    RenderWindow window(VideoMode(1200 , 900), "Super Smash Pikachu");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second

    srand(time(0));

    b2World world(b2Vec2(0, 150));

    cout << "Hello" << endl;

    Music song;
    song.openFromFile("ThePikachu.ogg");

    Music lose;
    lose.openFromFile("Waa.ogg");

    bool start = false;
    Texture title;
    cout << title.loadFromFile("Title.png") << endl;
    Sprite titlescreen;
    titlescreen.setTexture(title);
    titlescreen.setScale(0.5f, 0.5f);
    titlescreen.move(-140, 100);

    Sprite icon1;
    icon1.setTexture(title);
    icon1.setScale(0.05f, 0.05f);
    icon1.setPosition(300, 700);
    float sizeratio = 1200 / (0.05 * 2048);
    Sprite icon2;
    icon2.setTexture(title);
    icon2.setScale(0.05f, 0.05f);
    icon2.setColor(Color::Red);
    icon2.setPosition(700, 700);

    float screemx = 0;
    float screemy = 0;
    float cposx = 0;
    float cposy = 0;
    float camerax = 0;
    float cameray = 0;

    bool gameover;

    Font percent;
    percent.loadFromFile("Blazed.ttf");

    Text health1;
    health1.setFont(percent);
    health1.setCharacterSize(40);
    health1.setFillColor(Color::White);
    Text health2;
    health2.setFont(percent);
    health2.setCharacterSize(40);
    health2.setFillColor(Color::White);

    Text life1;
    life1.setFont(percent);
    life1.setCharacterSize(40);
    life1.setFillColor(Color::White);
    Text life2;
    life2.setFont(percent);
    life2.setCharacterSize(40);
    life2.setFillColor(Color::White);


    Texture super;
    cout << super.loadFromFile("Super.png") << endl;
    Sprite smash;
    smash.setTexture(super);
    smash.setPosition(30, 20);
    smash.scale(1.5f, 1.5f);


    Texture words;
    cout << words.loadFromFile("Pikapika.png") << endl;
    Sprite wordy;
    wordy.setTexture(words);
    wordy.setPosition(750, 100);
    wordy.scale(1.2f, 1.2f);

    Texture help;
    cout << help.loadFromFile("struct.png");
    Sprite helppage;
    helppage.setTexture(help);
    helppage.setPosition(-15, -35);

    Font f1;
    cout << f1.loadFromFile("Stencil.ttf") << endl;



    Button play(300, 80, 800, 500, Color::Yellow, Color::Blue);
    Text playw;
    playw.setFont(f1);
    playw.setCharacterSize(60);
    playw.setPosition(play.getPosition().x + 100, play.getPosition().y + 3);
    playw.setString("PLAY");
    playw.setFillColor(Color::Black);

    Button in(300, 80, 800, 600, Color::Yellow, Color::Blue);
    Text inw;
    inw.setFont(f1);
    inw.setCharacterSize(60);
    inw.setPosition(in.getPosition().x + 20, in.getPosition().y);
    inw.setString("INSTRUCTIONS");
    inw.setFillColor(Color::Black);

    Button backy(300, 80, 800, 600, Color::Yellow, Color::Blue);
    Text backw;
    backw.setFont(f1);
    backw.setCharacterSize(60);
    backw.setPosition(in.getPosition().x + 100, in.getPosition().y + 3);
    backw.setString("BACK");
    backw.setFillColor(Color::Black);

    Button again(300, 80, 450, 600, Color::Yellow, Color::Blue);
    Text retry;
    retry.setFont(f1);
    retry.setCharacterSize(60);
    retry.setPosition(again.getPosition().x + 25, again.getPosition().y +3);
    retry.setString("PLAY AGAIN?");
    retry.setFillColor(Color::Black);

    Text winner;
    winner.setFont(percent);
    winner.setCharacterSize(60);
    winner.setPosition(20, 400);
    winner.setFillColor(Color::Yellow);




    Texture t1;
    cout << t1.loadFromFile("Pikachu.png") << endl;
    Player Pika1(world, 250, 100, "PikachuPoints.txt", t1);
    vector <Sensors> Pikas1;
    vector <Sensors> Pikas2;
    Player Pika2(world, 800, 100, "PikachuPoints.txt", t1);
    //Pika2.setColour(Color(255 - Pika2.getColour().r, 255 - Pika2.getColour().g, 255 - Pika2.getColour().b + 255, 255));
    Pika2.setColour(Color::Red);

/// |------------------ PLAYERS ----------------------|




    vector <Texture> clouds;
    Texture cloud;
    cout << cloud.loadFromFile("Clouds1.png") << endl;
    clouds.push_back(cloud);
    cout << cloud.loadFromFile("Clouds2.png") << endl;
    clouds.push_back(cloud);
    cout << cloud.loadFromFile("Clouds3.png") << endl;
    clouds.push_back(cloud);
    cout << cloud.loadFromFile("Clouds4.png") << endl;
    clouds.push_back(cloud);
    cout << cloud.loadFromFile("Clouds5.png") << endl;
    clouds.push_back(cloud);


    Texture run;
    cout << run.loadFromFile("runsheet.png") << endl;
    //Pika1.setTexture(run);
    int runcount1 = 1;
    int runcount2 = 1;

    Texture runl;
    cout << runl.loadFromFile("runsheet2.png") << endl;

    Texture walk;
    cout << walk.loadFromFile("walksheet.png") << endl;
    Pika1.setTexture(walk);
    int walkcount1 = 0;
    int walkcount2 = 0;

    Texture walk2;
    cout << walk2.loadFromFile("walksheet2.png") << endl;

    Texture air;
    cout <<air.loadFromFile("airsheet.png") << endl;
    int aircount1 = 0;
    int aircount2 = 0;

    Texture air2;
    cout <<air2.loadFromFile("airsheet2.png") << endl;

    Texture charge;
    cout << charge.loadFromFile("chargesheet.png") << endl;

    Texture charge2;
    cout << charge2.loadFromFile("chargesheet2.png") << endl;

    Texture spin1;
    cout <<spin1.loadFromFile("spinsheet.png") << endl;
    int spincount1 = 0;
    int spincount2 = 0;

    Texture spin2;
    cout << spin2.loadFromFile("spinsheet2.png");


/// |------------------------ SENSOR LOADING --------------------------|

    Sensors running11(world, -1000, 100, "run1-1.txt", run, 0);
    Sensors running12(world, -2000, 100, "run1-2.txt", run, 133);
    Sensors running13(world, -3000, 100, "run1-3.txt", run, 276);
    Sensors running14(world, -4000, 100, "run1-4.txt", run, 427);

    Sensors running21(world, -5000, 100, "run2-1.txt", runl, 0);
    Sensors running22(world, -6000, 100, "run2-2.txt", runl, 144);
    Sensors running23(world, -7000, 100, "run2-3.txt", runl, 295);
    Sensors running24(world, -8000, 100, "run2-4.txt", runl, 428);

    Sensors walk11(world, -9000, 100, "walk1-1.txt", walk, 0);
    Sensors walk12(world, -10000, 100, "walk1-2.txt", walk, 97);
    Sensors walk13(world, -11000, 100, "walk1-3.txt", walk, 209);

    Sensors walk21(world, -12000, 100, "walk2-1.txt", walk2, 0);
    Sensors walk22(world, -13000, 100, "walk2-2.txt", walk2, 110);
    Sensors walk23(world, -14000, 100, "walk2-3.txt", walk2, 220);

    Pikas1.push_back(walk11);
    Pikas2.push_back(walk11);

/// |------------------------------------------------------------------|

    Sprite dust;
    int counter1 = 0;

    bool cansprintleft1 = false;
    bool cansprintleft2 = false;
    bool cansprintright1 = false;
    bool cansprintright2 = false;

    float xscreen = 0;
    float yscreen = 0;

    float ax = 0;
    float ay = 0;
    float dx = 0;
    float dy = 10;

    float vy = 0;
    float pikaposy = 0;
    float friction = 0;
    float diffvel = 0;

    bool doublehit = false;

    bool startscreen = true;
    bool instructions = true;
    bool goback = true;

    float hitx1 = 0;
    float hity1 = 0;

    float hitx2 = 0;
    float hity2 = 0;

    //const float ConversionSpeed = 2.1155742440683000451251986259768
    //const float Frametimevalue = 1 / 60;

    Pika1.setCanMove(true);


/// |---------------- PLATFORMS ------------------|
    /// REAL platform (invisible)
    vector <Platform> Base;
    Platform Basebase(world, 800, 30, 200, 550, Color::White, 1.0);
    Base.push_back(Basebase);
    /// FAKE platform (visible)
    Aspect FakeBase(Quads);
    FakeBase.addVertex(Vertex(Vector2f(200, 550), Color::White));
    FakeBase.addVertex(Vertex(Vector2f(1000, 550), Color::White));
    FakeBase.addVertex(Vertex(Vector2f(1000, 580), Color::White));
    FakeBase.addVertex(Vertex(Vector2f(200, 580), Color::White));






/// |-------------- ASPECTS --------------|
    Aspect aBase(Quads);
    aBase.addVertex(Vertex(Vector2f(200, 550), Color::Red));
    aBase.addVertex(Vertex(Vector2f(210, 530), Color::Blue));
    aBase.addVertex(Vertex(Vector2f(990, 530), Color::Blue));
    aBase.addVertex(Vertex(Vector2f(1000, 550), Color::Red));

    Aspect aBaseLeft(Quads);
    aBaseLeft.addVertex(Vertex(Vector2f(200, 550), Color::Green)); /// Does not move
    aBaseLeft.addVertex(Vertex(Vector2f(210, 530), Color::Green)); /// To be changed
    aBaseLeft.addVertex(Vertex(Vector2f(210, 500), Color::Green)); /// To be changed
    aBaseLeft.addVertex(Vertex(Vector2f(200, 580), Color::Green)); /// Does not move

    Aspect aBaseRight(Quads);
    aBaseRight.addVertex(Vertex(Vector2f(1000, 550), Color::Green)); /// Does not move
    aBaseRight.addVertex(Vertex(Vector2f(990, 530), Color::Green)); /// To be changed
    aBaseRight.addVertex(Vertex(Vector2f(990, 500), Color::Green)); /// To be changed
    aBaseRight.addVertex(Vertex(Vector2f(1000, 580), Color::Green)); /// Does not move

    Aspect aBaseBottom(Quads);
    aBaseBottom.addVertex(Vertex(Vector2f(1000, 580), Color::Yellow)); /// Does not move
    aBaseBottom.addVertex(Vertex(Vector2f(200, 550), Color::Yellow)); /// To be changed
    aBaseBottom.addVertex(Vertex(Vector2f(200, 550), Color::Yellow)); /// To be changed
    aBaseBottom.addVertex(Vertex(Vector2f(200, 580), Color::Yellow)); /// Does not move

/// |----------------- View Tools ------------------|
    RectangleShape refersquare(Vector2f(20, 20));
    refersquare.setPosition(10, 400);
    refersquare.setFillColor(Color::Magenta);

    View camera(Vector2f(1200/2, 900/2), Vector2f(1200, 900));
    window.setView(camera);

    RectangleShape mid(Vector2f(1,1));
    float xc = 0;
    float yc = 0;




/// |------------ HITBOXES -----------------------| because sensors are horrible...

    //Hitbox p1s(world, hitx1, hity1, 0, 0, 0);
    vector <Hitbox> p1;
    //Hitbox p2s(world, hitx2, hity2, 0, 0, 0);
    vector <Hitbox> p2;


/// |------------------- Time --------------------|

    Time watch;


    Clock run1;
    Clock run2;
    Clock sideb1;
    Clock sideb2;
    Clock saute;
    Clock saute2;
    Clock inv1;
    Clock inv2;
    Clock clickclack;
    Clock clackclick;
    Clock frames;
    Clock game;


    while (window.isOpen())     //the main game loop, exit if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop

        window.clear(); //clears the screen

        watch = frames.getElapsedTime();
        frames.restart();
        //cout << watch.asMilliseconds() << endl;


        /// Calculations

        if (start)
        {

            if ((Pika1.getPosition().y > 1500) || (Pika1.getPosition().y > 5000) || (Pika1.getPosition().x < -2000) || (Pika1.getPosition().x > 3200))
            {
                Pika1.setInvincible(true);
                Pika1.setPosition(250, 100);
                Pika1.setBoxPosition(Vector2f(250, 100));
                Pika1.setLives(Pika1.getLives() - 1);
                Pika1.setDamage(0);
                diffvel = -Pika1.getHorizontalVelocity() * Pika1.getMass();
                Pika1.Move(diffvel);
                diffvel = -Pika1.getVerticalVelocity() * Pika1.getMass();
                Pika1.Rise(diffvel);
                inv1.restart();
                Pika2.move(0, -findDy(Pika2.getPosition().y, Base[0].getPosition().y));
                Pika2.setBoxPosition(Vector2f(Pika2.getPosition().x, Pika2.getPosition().y));

            }
            if ((Pika2.getPosition().y > 1500) || (Pika2.getPosition().y > 5000) || (Pika2.getPosition().x < -2000) || (Pika2.getPosition().x > 3200))
            {
                Pika2.setInvincible(true);
                Pika2.setPosition(800, 100);
                Pika2.setBoxPosition(Vector2f(800, 100));
                Pika2.setLives(Pika2.getLives() - 1);
                Pika2.setDamage(0);
                diffvel = -Pika2.getHorizontalVelocity() * Pika2.getMass();
                Pika2.Move(diffvel);
                diffvel = -Pika2.getVerticalVelocity() * Pika2.getMass();
                Pika2.Rise(diffvel);
                inv2.restart();
                Pika1.move(0, -findDy(Pika1.getPosition().y, Base[0].getPosition().y));
                Pika1.setBoxPosition(Vector2f(Pika1.getPosition().x, Pika1.getPosition().y));
            }

            if (inv1.getElapsedTime().asSeconds() > 2)
            {
                Pika1.setInvincible(false);
            }
            if (inv2.getElapsedTime().asSeconds() > 2)
            {
                Pika2.setInvincible(false);
            }

            cout << Pika1.isInvincible() << " " << Pika2.isInvincible() <<  endl;


    /// |-------------------------------- Left Movement Controls ---------------------------------|

            /// Pika1
            if (Pika1.getCanMove())
            {
                if ((Keyboard::isKeyPressed(Keyboard::A)) && (!Keyboard::isKeyPressed(Keyboard::D)))
                {
                    Pika1.setMoving(true);
                    Pika1.setLeft(true);
                    Pika1.setRight(false);

                    if (cansprintleft1)
                        Pika1.setSprint(true);
                    else
                        Pika1.setSprint(false);


                    if (!Pika1.getSprint())
                    {
                        //Pika1.setVelocity(Vector2f(-300, Pika1.getVerticalVelocity()));
                        if (Pika1.getHorizontalVelocity() > -10)
                            Pika1.Move(-10);
                        run1.restart();
                        if (Pika1.isGrounded())
                        {
                            Pika1.setTexture(walk2);
                            walkcount1++;
                            if (walkcount1%32 == 0)
                            {
                                Pika1.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                                //if (!Pikas1.empty())
                                //{
                                //   Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk23);
                                    hitx1 = 315 - 220;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (walkcount1%32 == 8)
                            {
                                Pika1.setTextureRect(IntRect(111, 0, 217 - 111, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk22);
                                    hitx1 = 217 - 111;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (walkcount1%32 == 16)
                            {
                                Pika1.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk23);
                                    hitx1 = 315 - 220;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (walkcount1%32 == 24)
                            {
                                Pika1.setTextureRect(IntRect(0, 0, 104, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk21);
                                    hitx1 = 104;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                        }
                    }
                    else if (Pika1.getSprint())
                    {
                        //Pika1.setVelocity(Vector2f(-600, Pika1.getVerticalVelocity()));
                        if (Pika1.getHorizontalVelocity() > -20)
                            Pika1.Move(-20);
                        run1.restart();
                        if (Pika1.isGrounded())
                        {
                            Pika1.setTexture(runl);
                            runcount1++;
                            if (runcount1%16 == 0)
                            {
                                Pika1.setTextureRect(IntRect(439, 0, 604 - 439, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running24);
                                    hitx1 = 604 - 439;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (runcount1%16 == 4)
                            {
                                Pika1.setTextureRect(IntRect(296, 0, 438 - 296, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running23);
                                    hitx1 = 438 - 296;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (runcount1%16 == 8)
                            {
                                Pika1.setTextureRect(IntRect(145, 0, 295 - 145, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running22);
                                    hitx1 = 295 - 145;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (runcount1%16 == 12)
                            {
                                Pika1.setTextureRect(IntRect(0, 0, 144, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running21);
                                    hitx1 = 144;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                        }
                    }

                }
                else if (!Pika1.isRight())
                {
                    Pika1.setTexture(walk2);
                    Pika1.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                    //if (!Pikas1.empty())
                    //{
                    //    Pikas1.erase(Pikas1.begin());
                    //    Pikas1.push_back(walk23);
                        hitx1 = 315 - 220;
                        hity1 = 117;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    //}
                }
                /// Detects for second press within 0.1 seconds.
                if ((!Keyboard::isKeyPressed(Keyboard::A)) && (run1.getElapsedTime().asMilliseconds() < 100))
                {
                    cansprintleft1 = true;
                }
                else if (run1.getElapsedTime().asMilliseconds() > 100)
                    cansprintleft1 = false;
            }



            /// Pika2
            if (Pika2.getCanMove())
            {
                if ((Keyboard::isKeyPressed(Keyboard::Left)) && (!Keyboard::isKeyPressed(Keyboard::Right)))
                {
                    Pika2.setMoving(true);
                    Pika2.setLeft(true);
                    Pika2.setRight(false);

                    if (cansprintleft2)
                        Pika2.setSprint(true);
                    else
                        Pika2.setSprint(false);


                    if (!Pika2.getSprint())
                    {
                        //Pika2.setVelocity(Vector2f(-300, Pika2.getVerticalVelocity()));
                        if (Pika2.getHorizontalVelocity() > -10)
                            Pika2.Move(-10);
                        run2.restart();
                        if (Pika2.isGrounded())
                        {
                            Pika2.setTexture(walk2);
                            walkcount2++;
                            if (walkcount2%32 == 0)
                            {
                                Pika2.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk23);
                                    hitx2 = 315 - 220;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (walkcount2%32 == 8)
                            {
                                Pika2.setTextureRect(IntRect(111, 0, 217 - 111, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk22);
                                    hitx2 = 217 - 111;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (walkcount2%32 == 16)
                            {
                                Pika2.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk23);
                                    hitx2 = 315 - 220;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (walkcount2%32 == 24)
                            {
                                Pika2.setTextureRect(IntRect(0, 0, 104, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk21);
                                    hitx2 = 104;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                        }

                    }
                    else if (Pika2.getSprint())
                    {
                        //Pika2.setVelocity(Vector2f(-600, Pika2.getVerticalVelocity()));
                        if (Pika2.getHorizontalVelocity() > -20)
                            Pika2.Move(-20);
                        run2.restart();
                        if (Pika2.isGrounded())
                        {
                            Pika2.setTexture(runl);
                            runcount2++;
                            if (runcount2%16 == 0)
                            {
                                Pika2.setTextureRect(IntRect(439, 0, 604 - 439, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running24);
                                    hitx2 = 604 - 439;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (runcount2%16 == 4)
                            {
                                Pika2.setTextureRect(IntRect(296, 0, 438 - 296, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running23);
                                    hitx2 = 438 - 296;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (runcount2%16 == 8)
                            {
                                Pika2.setTextureRect(IntRect(145, 0, 295 - 145, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running22);
                                    hitx2 = 295 - 145;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (runcount2%16 == 12)
                            {
                                Pika2.setTextureRect(IntRect(0, 0, 144, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running21);
                                    hitx2 = 144;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                        }
                    }

                }
                else if (!Pika2.isRight())
                {
                    Pika2.setTexture(walk2);
                    Pika2.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                    //if (!Pikas2.empty())
                    //{
                    //    Pikas2.erase(Pikas2.begin());
                    //    Pikas2.push_back(walk23);
                        hitx2 = 315 - 220;
                        hity2 = 117;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    //}
                }
                /// Detects for second press within 0.1 seconds.
                if ((!Keyboard::isKeyPressed(Keyboard::Left)) && (run2.getElapsedTime().asMilliseconds() < 100))
                {
                    cansprintleft2 = true;
                }
                else if (run2.getElapsedTime().asMilliseconds() > 100)
                    cansprintleft2 = false;
            }

    /// Run sprites
    /*
            runcount++;
            if (runcount%16 == 0)
            {
                Pika1.setTextureRect(IntRect(0, 0, 133, 111));
            }
            if (runcount%16 == 4)
            {
                Pika1.setTextureRect(IntRect(134, 0, 144, 111));
            }
            if (runcount%16 == 8)
            {
                Pika1.setTextureRect(IntRect(279, 0, 428 - 279, 111));
            }
            if (runcount%16 == 12)
            {
                Pika1.setTextureRect(IntRect(429, 0, 604 - 429, 111));
            }
    */


    /// Walk sprites
    /*
            walkcount++;
            if (walkcount%32 == 0)
            {
                Pika1.setTextureRect(IntRect(0, 0, 96, 117));
            }
            if (walkcount%32 == 8)
            {
                Pika1.setTextureRect(IntRect(97, 0, 203 - 97, 117));
            }
            if (walkcount%32 == 16)
            {
                Pika1.setTextureRect(IntRect(0, 0, 96, 117));
            }
            if (walkcount%32 == 24)
            {
                Pika1.setTextureRect(IntRect(210, 0, 315 - 210, 117));
            }
    */



    /// |------------------------------------ Right Movement Controls ----------------------------------| ///
            /// Pika1
            if (Pika1.getCanMove())
            {
                //cout << "Hello" << endl;
                if ((Keyboard::isKeyPressed(Keyboard::D)) && (!Keyboard::isKeyPressed(Keyboard::A)))
                {
                    Pika1.setMoving(true);
                    Pika1.setRight(true);
                    Pika1.setLeft(false);

                    if (cansprintright1)
                        Pika1.setSprint(true);
                    else
                        Pika1.setSprint(false);




                    if (!Pika1.getSprint())
                    {
                        //Pika1.setVelocity(Vector2f(300, Pika1.getVerticalVelocity()));
                        if (Pika1.getHorizontalVelocity() < 10)
                            Pika1.Move(10);
                        run1.restart();
                        //cout << "hello" << endl;
                        if (Pika1.isGrounded())
                        {
                            Pika1.setTexture(walk);
                            walkcount1++;

                            if (walkcount1%32 == 0)
                            {
                                Pika1.setTextureRect(IntRect(0, 0, 96, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk11);
                                    hitx1 = 96;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (walkcount1%32 == 8)
                            {
                                Pika1.setTextureRect(IntRect(97, 0, 203 - 97, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk12);
                                    hitx1 = 203 - 97;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (walkcount1%32 == 16)
                            {
                                Pika1.setTextureRect(IntRect(0, 0, 96, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk11);
                                    hitx1 = 96;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (walkcount1%32 == 24)
                            {
                                Pika1.setTextureRect(IntRect(210, 0, 315 - 210, 117));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(walk13);
                                    hitx1 = 315 - 210;
                                    hity1 = 117;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                        }
                    }
                    else if (Pika1.getSprint())
                    {
                        //Pika1.setVelocity(Vector2f(600, Pika1.getVerticalVelocity()));
                        if (Pika1.getHorizontalVelocity() < 20)
                            Pika1.Move(20);
                        run1.restart();
                        if (Pika1.isGrounded())
                        {
                            Pika1.setTexture(run);
                            runcount1++;
                            if (runcount1%16 == 0)
                            {
                                Pika1.setTextureRect(IntRect(0, 0, 133, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running11);
                                    hitx1 = 133;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (runcount1%16 == 4)
                            {
                                Pika1.setTextureRect(IntRect(134, 0, 144, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running12);
                                    hitx1 = 144;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (runcount1%16 == 8)
                            {
                                Pika1.setTextureRect(IntRect(279, 0, 428 - 279, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running13);
                                    hitx1 = 428 - 279;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                            if (runcount1%16 == 12)
                            {
                                Pika1.setTextureRect(IntRect(429, 0, 604 - 429, 111));
                                //if (!Pikas1.empty())
                                //{
                                //    Pikas1.erase(Pikas1.begin());
                                //    Pikas1.push_back(running14);
                                    hitx1 = 604 - 429;
                                    hity1 = 111;
                                    if (!p1.empty())
                                    {
                                        p1.front().destroy(world);
                                        p1.erase(p1.begin());
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                    }
                                    else
                                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                                //}
                            }
                        }
                    }

                }
                else if (!Pika1.isLeft())
                {
                    Pika1.setTexture(walk);
                    Pika1.setTextureRect(IntRect(0, 0, 96, 117));
                    //if (!Pikas1.empty())
                    //{
                    //    Pikas1.erase(Pikas1.begin());
                    //    Pikas1.push_back(walk11);
                        hitx1 = 96;
                        hity1 = 117;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    //}
                }

                if ((!Keyboard::isKeyPressed(Keyboard::D)) && (run1.getElapsedTime().asMilliseconds() < 100))
                {
                    cansprintright1 = true;
                }
                else if (run1.getElapsedTime().asMilliseconds() > 100)
                    cansprintright1 = false;
            }


            /// Pika2
            if (Pika2.getCanMove())
            {
                if ((Keyboard::isKeyPressed(Keyboard::Right)) && (!Keyboard::isKeyPressed(Keyboard::Left)))
                {
                    Pika2.setRight(true);
                    Pika2.setLeft(false);

                    if (cansprintright2)
                        Pika2.setSprint(true);
                    else
                        Pika2.setSprint(false);


                    if (!Pika2.getSprint())
                    {
                        //Pika2.setVelocity(Vector2f(300, Pika2.getVerticalVelocity()));
                        if (Pika2.getHorizontalVelocity() < 10)
                            Pika2.Move(10);
                        run2.restart();
                        if (Pika2.isGrounded())
                        {
                            Pika2.setTexture(walk);
                            walkcount2++;
                            if (walkcount2%32 == 0)
                            {
                                Pika2.setTextureRect(IntRect(0, 0, 96, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk11);
                                    hitx2 = 96;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (walkcount2%32 == 8)
                            {
                                Pika2.setTextureRect(IntRect(97, 0, 203 - 97, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk12);
                                    hitx2 = 203 - 97;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (walkcount2%32 == 16)
                            {
                                Pika2.setTextureRect(IntRect(0, 0, 96, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk11);
                                    hitx2 = 96;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (walkcount2%32 == 24)
                            {
                                Pika2.setTextureRect(IntRect(210, 0, 315 - 210, 117));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(walk13);
                                    hitx2 = 315 - 210;
                                    hity2 = 117;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                        }
                    }
                    else if (Pika2.getSprint())
                    {
                        //Pika2.setVelocity(Vector2f(600, Pika2.getVerticalVelocity()));
                        if (Pika2.getHorizontalVelocity() < 20)
                            Pika2.Move(20);
                        run2.restart();
                        if (Pika2.isGrounded())
                        {
                            Pika2.setTexture(run);
                            runcount2++;
                            if (runcount2%16 == 0)
                            {
                                Pika2.setTextureRect(IntRect(0, 0, 133, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running11);
                                    hitx2 = 133;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (runcount2%16 == 4)
                            {
                                Pika2.setTextureRect(IntRect(134, 0, 144, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running12);
                                    hitx2 = 144;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (runcount2%16 == 8)
                            {
                                Pika2.setTextureRect(IntRect(279, 0, 428 - 279, 111));
                                //if (!Pikas2.empty())
                                //{
                                //   Pikas2.erase(Pikas2.begin());
                                //   Pikas2.push_back(running13);
                                    hitx2 = 428 - 279;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                            if (runcount2%16 == 12)
                            {
                                Pika2.setTextureRect(IntRect(429, 0, 604 - 429, 111));
                                //if (!Pikas2.empty())
                                //{
                                //    Pikas2.erase(Pikas2.begin());
                                //    Pikas2.push_back(running14);
                                    hitx2 = 604 - 429;
                                    hity2 = 111;
                                    if (!p2.empty())
                                    {
                                        p2.front().destroy(world);
                                        p2.erase(p2.begin());
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                    }
                                    else
                                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                                //}
                            }
                        }
                    }

                }
                else if (!Pika2.isLeft())
                {
                    Pika2.setTexture(walk);
                    Pika2.setTextureRect(IntRect(0, 0, 96, 117));
                    //if (!Pikas2.empty())
                    //{
                    //    Pikas2.erase(Pikas2.begin());
                    //    Pikas2.push_back(walk11);
                        hitx2 = 96;
                        hity2 = 117;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    //}
                }

                if ((!Keyboard::isKeyPressed(Keyboard::Right)) && (run2.getElapsedTime().asMilliseconds() < 100))
                {
                    cansprintright2 = true;
                }
                else if (run2.getElapsedTime().asMilliseconds() > 100)
                    cansprintright2 = false;
            }

            if ((!Keyboard::isKeyPressed(Keyboard::A)) && (!Keyboard::isKeyPressed(Keyboard::D)))
            {
                if (Pika1.isLeft())
                {
                    Pika1.setTexture(walk2);
                    Pika1.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                    hitx1 = 315 - 220;
                    hity1 = 117;
                    //if (!Pikas1.empty())
                    //{
                    //    Pikas1.erase(Pikas1.begin());
                    //    Pikas1.push_back(walk23);
                        hitx1 = 315 - 220;
                        hity1 = 117;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    //}


                }
                if (Pika1.isRight())
                {
                    Pika1.setTexture(walk);
                    Pika1.setTextureRect(IntRect(0, 0, 96, 117));
                    hitx1 = 96;
                    hity1 = 117;
                    //if (!Pikas1.empty())
                    //{
                    //    Pikas1.erase(Pikas1.begin());
                    //    Pikas1.push_back(walk11);
                        hitx1 = 96;
                        hity1 = 117;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    //}
                }
            }

            if ((!Keyboard::isKeyPressed(Keyboard::Left)) && (!Keyboard::isKeyPressed(Keyboard::Right)))
            {
                if (Pika2.isLeft())
                {
                    Pika2.setTexture(walk2);
                    Pika2.setTextureRect(IntRect(220, 0, 315 - 220, 117));
                    hitx2 = 315 - 220;
                    hity2 = 117;
                    //if (!Pikas2.empty())
                    //{
                    //    Pikas2.erase(Pikas2.begin());
                    //    Pikas2.push_back(walk23);
                        hitx2 = 315 - 220;
                        hity2 = 117;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    //}


                }
                if (Pika2.isRight())
                {
                    Pika2.setTexture(walk);
                    Pika2.setTextureRect(IntRect(0, 0, 96, 117));
                    hitx2 = 96;
                    hity2 = 117;
                    //if (!Pikas2.empty())
                    //{
                    //    Pikas2.erase(Pikas2.begin());
                    //    Pikas2.push_back(walk11);
                        hitx2 = 96;
                        hity2 = 117;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    //}
                }
            }




            /// Note that the same clock is used - I could have used different clocks for each direction, but in the actual game,
            /// moving the opposite direction automatically gives you a sprinting momentum (it is a lot easier to do it with a
            /// joystick, but I can't use joysticks at school so I'm stuck with this).

            //cout << game.getElapsedTime().asMilliseconds() << " " << Pika1.getPosition().x << endl;
            //cout << Pika1.getMass() << " " << Pika1.getHorizontalVelocity() << endl;

    /// |----------------------------------------------- Jumping -----------------------------------------------------|

            /// Pika1
            if (Pika1.isTouchingGround(Base[0].getBody()))
            {
                Pika1.setGrounded(true);
                Pika1.setJump1(false);
                Pika1.setJump2(false);
            }
            if (Pika1.getCanJump())
            {
                if (Keyboard::isKeyPressed(Keyboard::W))
                {
                    ///if ((Pika1.isTouchingGround(Base[0].getBody())) && (Pika1.isGrounded()))
                    if (!Pika1.getJump1())
                    {
                        Pika1.setGrounded(false);
                        diffvel = -Pika1.getVerticalVelocity() * Pika1.getMass();
                        Pika1.Rise(diffvel);
                        Pika1.Jump();
                        Pika1.Jump();
                        Pika1.setJump1(true);
                        saute.restart();
                    }
                    if ((Pika1.getJump1()) && (saute.getElapsedTime().asMilliseconds() > 200) && (!Pika1.getJump2()))
                    {
                        diffvel = -Pika1.getVerticalVelocity() * Pika1.getMass();
                        Pika1.Rise(diffvel);
                        Pika1.Jump();
                        Pika1.Jump();
                        Pika1.setJump2(true);
                    }
                }
            }

            if ((!Pika1.isGrounded()) && (Keyboard::isKeyPressed(Keyboard::S)))
            {
                Pika1.Rise(50);
            }

            if (Pika1.isTouchingGround(Base[0].getBody()))
            {
                Pika1.setGrounded(true);
            }
            else
                Pika1.setGrounded(false);

            if ((!Pika1.isGrounded()) && (Pika1.isRising()))
            {
                if (Pika1.isRight())
                {
                    Pika1.setTexture(air);
                    Pika1.setTextureRect(IntRect(0, 0, 105, 122));
                    hitx1 = 105;
                    hity1 = 122;
                    if (!p1.empty())
                    {
                        p1.front().destroy(world);
                        p1.erase(p1.begin());
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    else
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                }
                if (Pika1.isLeft())
                {
                    Pika1.setTexture(air2);
                    Pika1.setTextureRect(IntRect(121, 0, 105, 122));
                    hitx1 = 105;
                    hity1 = 122;
                    if (!p1.empty())
                    {
                        p1.front().destroy(world);
                        p1.erase(p1.begin());
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    else
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));


                }

            }

            if ((!Pika1.isGrounded()) && (Pika1.isFalling()) && ((Pika1.getJump1()) || (Pika1.getPosition().y > Base[0].getPosition().y)))
            {
                if (Pika1.isRight())
                {
                    Pika1.setTexture(air);
                    Pika1.setTextureRect(IntRect(106, 0, 120, 122));
                    hitx1 = 120;
                    hity1 = 122;
                    if (!p1.empty())
                    {
                        p1.front().destroy(world);
                        p1.erase(p1.begin());
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    else
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                }
                if (Pika1.isLeft())
                {
                    Pika1.setTexture(air2);
                    Pika1.setTextureRect(IntRect(0, 0, 120, 122));
                    hitx1 = 120;
                    hity1 = 122;
                    if (!p1.empty())
                    {
                        p1.front().destroy(world);
                        p1.erase(p1.begin());
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    else
                        p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                }
            }

            /// Pika2
            if (Pika2.isTouchingGround(Base[0].getBody()))
            {
                Pika2.setGrounded(true);
                Pika2.setJump1(false);
                Pika2.setJump2(false);
            }

            if (Pika2.getCanJump())
            {
                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    ///if ((Pika1.isTouchingGround(Base[0].getBody())) && (Pika1.isGrounded()))
                    if (!Pika2.getJump1())
                    {
                        Pika2.setGrounded(false);
                        diffvel = -Pika2.getVerticalVelocity() * Pika2.getMass();
                        Pika2.Rise(diffvel);
                        Pika2.Jump();
                        Pika2.Jump();
                        Pika2.setJump1(true);
                        saute2.restart();
                    }
                    if ((Pika2.getJump1()) && (saute2.getElapsedTime().asMilliseconds() > 200) && (!Pika2.getJump2()))
                    {
                        diffvel = -Pika2.getVerticalVelocity() * Pika2.getMass();
                        Pika2.Rise(diffvel);
                        Pika2.Jump();
                        Pika2.Jump();
                        Pika2.setJump2(true);
                    }
                }
            }

            if ((!Pika2.isGrounded()) && (Keyboard::isKeyPressed(Keyboard::Down)))
            {
                Pika2.Rise(50);
            }

            if (Pika2.isTouchingGround(Base[0].getBody()))
            {
                Pika2.setGrounded(true);
            }
            else
                Pika2.setGrounded(false);

            if ((!Pika2.isGrounded()) && (Pika2.isRising()))
            {
                if (Pika2.isRight())
                {
                    Pika2.setTexture(air);
                    Pika2.setTextureRect(IntRect(0, 0, 105, 122));
                    hitx2 = 105;
                    hity2 = 122;
                    if (!p2.empty())
                    {
                        p2.front().destroy(world);
                        p2.erase(p2.begin());
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    else
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                }
                if (Pika2.isLeft())
                {
                    Pika2.setTexture(air2);
                    Pika2.setTextureRect(IntRect(121, 0, 105, 122));
                    hitx2 = 105;
                    hity2 = 122;
                    if (!p2.empty())
                    {
                        p2.front().destroy(world);
                        p2.erase(p2.begin());
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    else
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));


                }

            }


            if ((!Pika2.isGrounded()) && (Pika2.isFalling()) && ((Pika2.getJump1()) || (Pika2.getPosition().y > Base[0].getPosition().y)))
            {
                if (Pika2.isRight())
                {
                    Pika2.setTexture(air);
                    Pika2.setTextureRect(IntRect(106, 0, 120, 122));
                    hitx2 = 120;
                    hity2 = 122;
                    if (!p2.empty())
                    {
                        p2.front().destroy(world);
                        p2.erase(p2.begin());
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    else
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                }
                if (Pika2.isLeft())
                {
                    Pika2.setTexture(air2);
                    Pika2.setTextureRect(IntRect(0, 0, 120, 122));
                    hitx2 = 120;
                    hity2 = 122;
                    if (!p2.empty())
                    {
                        p2.front().destroy(world);
                        p2.erase(p2.begin());
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    else
                        p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                }
            }

    /*        if (!Pika1.isGrounded())
            {
                counter1 = 0;
            }

            if (!Pika2.isGrounded())
            {
                counter2 = 0;
            }*/


    //        if ((Pika1.isGrounded()) && (counter1 < 5))
      //      {
        //        cout << "CLOUDS" << counter1 << endl;
          //      dust.setTexture(clouds[counter1]);
            //    dust.setPosition(Pika1.getPosition().x /*+ (Pika1.getSize().x / 2)*/ - 50, Pika1.getPosition().y /*+ Pika1.getSize().y*/ + 30);
              //  counter1++;
            //}

    ///|----------------------- ATTACK(S)------------------------------------|


            /// Combos - Pika1

            if (Keyboard::isKeyPressed(Keyboard::H)) /// Basic Special
            {
                /// Thunderjolt
            }
            if (Keyboard::isKeyPressed(Keyboard::J)) /// Basic Attack
            {
                if (Pika1.isGrounded())
                {
                    /// Fan-like attack
                }
                else
                {
                    /// spin in the air attack
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::K)) /// Jump ??
            {
                /// Probably not here, going to fix
            }
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                /// taunt
            }

            /// SPIN MOVE
            if ((Keyboard::isKeyPressed(Keyboard::D)) && (Keyboard::isKeyPressed(Keyboard::K)) && (!Pika1.isAttacking()))
            {
                Pika1.setSideSpecialRight(true);
                Pika1.setCanMove(false);
                Pika1.setCanJump(false);
                Pika1.setTexture(charge);
                Pika1.setTextureRect(IntRect(0, 0, 130, 108));
                hitx1 = 130;
                hity1 = 108;
                if (!p1.empty())
                {
                    p1.front().destroy(world);
                    p1.erase(p1.begin());
                    p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                }
                else
                    p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                //cout << "hello" << endl;
                if (!Pika1.getPulse())
                    sideb1.restart();
                Pika1.setPulse(true);

            }

            if (((!Keyboard::isKeyPressed(Keyboard::D)) || (!Keyboard::isKeyPressed(Keyboard::K)) || (sideb1.getElapsedTime().asSeconds() > 1.5) || (!Pika1.getPulse())) && (Pika1.isSideSpecialRight()))
            {

                if (Pika1.getPulse())
                {
                    diffvel = -Pika1.getVerticalVelocity() * Pika1.getMass();
                    Pika1.Rise(diffvel);
                    diffvel = -Pika1.getHorizontalVelocity() * Pika1.getMass();
                    Pika1.Move(diffvel);
                    Pika1.Rise(-150);
                    Pika1.Move(200 * sideb1.getElapsedTime().asSeconds());
                    Pika1.setPulse(false);
                    sideb1.restart();
                }
                if (((Pika1.isGrounded()) && (!Pika1.getPulse()) && (sideb1.getElapsedTime().asSeconds() > 0.2)) || (sideb1.getElapsedTime().asSeconds() > 1))
                {
                    Pika1.setAttacking(false);
                    Pika1.setSideSpecialRight(false);
                    Pika1.setCanMove(true);
                    Pika1.setCanJump(true);
                }
                else
                {
                    Pika1.setAttacking(true);
                    Pika1.setTexture(spin1);

                    if (spincount1 % 4 == 0)
                    {
                        Pika1.setTextureRect(IntRect(0, 0, 134, 96));
                        hitx1 = 134;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    if (spincount1 % 4 == 1)
                    {
                        Pika1.setTextureRect(IntRect(135, 0, 269 - 134, 96));
                        hitx1 = 269 - 134;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    if (spincount1 % 4 == 2)
                    {
                        Pika1.setTextureRect(IntRect(270, 0, 403 - 269, 96));
                        hitx1 = 403 - 269;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    if (spincount1 % 4 == 3)
                    {
                        Pika1.setTextureRect(IntRect(403, 0, 539 - 402, 96));
                        hitx1 = 539 - 402;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    spincount1++;
                }
            }


            ///--------------------------------------------------------------------------
            if ((Keyboard::isKeyPressed(Keyboard::A)) && (Keyboard::isKeyPressed(Keyboard::K)) && (!Pika1.isAttacking()))
            {
                Pika1.setSideSpecialLeft(true);
                Pika1.setCanMove(false);
                Pika1.setCanJump(false);
                Pika1.setTexture(charge2);
                Pika1.setTextureRect(IntRect(0, 0, 130, 108));
                hitx1 = 130;
                hity1 = 108;
                if (!p1.empty())
                {
                    p1.front().destroy(world);
                    p1.erase(p1.begin());
                    p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                }
                else
                    p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                //cout << "hello" << endl;
                if (!Pika1.getPulse())
                    sideb1.restart();
                Pika1.setPulse(true);

            }

            if (((!Keyboard::isKeyPressed(Keyboard::A)) || (!Keyboard::isKeyPressed(Keyboard::K)) || (sideb1.getElapsedTime().asSeconds() > 1.5) || (!Pika1.getPulse())) && (Pika1.isSideSpecialLeft()))
            {

                if (Pika1.getPulse())
                {
                    diffvel = -Pika1.getVerticalVelocity() * Pika1.getMass();
                    Pika1.Rise(diffvel);
                    diffvel = -Pika1.getHorizontalVelocity() * Pika1.getMass();
                    Pika1.Move(diffvel);
                    Pika1.Rise(-150);
                    Pika1.Move(-200 * sideb1.getElapsedTime().asSeconds());
                    Pika1.setPulse(false);
                    sideb1.restart();
                }
                if (((Pika1.isGrounded()) && (!Pika1.getPulse()) && (sideb1.getElapsedTime().asSeconds() > 0.2)) || (sideb1.getElapsedTime().asSeconds() > 1))
                {
                    Pika1.setAttacking(false);
                    Pika1.setSideSpecialLeft(false);
                    Pika1.setCanMove(true);
                    Pika1.setCanJump(true);
                }
                else
                {
                    Pika1.setAttacking(true);
                    Pika1.setTexture(spin2);

                    if (spincount1 % 4 == 0)
                    {
                        Pika1.setTextureRect(IntRect(409, 0, 544 - 409, 96));
                        hitx1 = 544 - 409;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    if (spincount1 % 4 == 1)
                    {
                        Pika1.setTextureRect(IntRect(274, 0, 408 - 274, 96));
                        hitx1 = 408 - 274;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    if (spincount1 % 4 == 2)
                    {
                        Pika1.setTextureRect(IntRect(140, 0, 273 - 140, 96));
                        hitx1 = 273 - 140;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    if (spincount1 % 4 == 3)
                    {
                        Pika1.setTextureRect(IntRect(0, 0, 139, 96));
                        hitx1 = 139;
                        hity1 = 96;
                        if (!p1.empty())
                        {
                            p1.front().destroy(world);
                            p1.erase(p1.begin());
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                        }
                        else
                            p1.push_back(Hitbox(world, hitx1, hity1, Pika1.getPosition().x, Pika1.getPosition().y, 0));
                    }
                    spincount1++;
                }
            }

            //cout << Pika1.isAttacking() << endl;

            /// Pika2 --------------------------------------------

            if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Numpad2)) && (!Pika2.isAttacking()))
            {
                Pika2.setSideSpecialRight(true);
                Pika2.setCanMove(false);
                Pika2.setCanJump(false);
                Pika2.setTexture(charge);
                Pika2.setTextureRect(IntRect(0, 0, 130, 108));
                hitx2 = 130;
                hity2 = 108;
                if (!p2.empty())
                {
                    p2.front().destroy(world);
                    p2.erase(p2.begin());
                    p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                }
                else
                    p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                //cout << "hello" << endl;
                if (!Pika2.getPulse())
                    sideb2.restart();
                Pika2.setPulse(true);

            }

            if (((!Keyboard::isKeyPressed(Keyboard::Right)) || (!Keyboard::isKeyPressed(Keyboard::Numpad2)) || (sideb2.getElapsedTime().asSeconds() > 1.5) || (!Pika2.getPulse())) && (Pika2.isSideSpecialRight()))
            {

                if (Pika2.getPulse())
                {
                    diffvel = -Pika2.getVerticalVelocity() * Pika2.getMass();
                    Pika2.Rise(diffvel);
                    diffvel = -Pika2.getHorizontalVelocity() * Pika2.getMass();
                    Pika2.Move(diffvel);
                    Pika2.Rise(-150);
                    Pika2.Move(200 * sideb2.getElapsedTime().asSeconds());
                    Pika2.setPulse(false);
                    sideb2.restart();
                }
                if (((Pika2.isGrounded()) && (!Pika2.getPulse()) && (sideb2.getElapsedTime().asSeconds() > 0.2)) || (sideb2.getElapsedTime().asSeconds() > 1))
                {
                    Pika2.setAttacking(false);
                    Pika2.setSideSpecialRight(false);
                    Pika2.setCanMove(true);
                    Pika2.setCanJump(true);
                }
                else
                {
                    Pika2.setAttacking(true);
                    Pika2.setTexture(spin1);

                    if (spincount2 % 4 == 0)
                    {
                        Pika2.setTextureRect(IntRect(0, 0, 134, 96));
                        hitx2 = 134;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    if (spincount2 % 4 == 1)
                    {
                        Pika2.setTextureRect(IntRect(135, 0, 269 - 134, 96));
                        hitx2 = 269 - 134;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    if (spincount2 % 4 == 2)
                    {
                        Pika2.setTextureRect(IntRect(270, 0, 403 - 269, 96));
                        hitx2 = 403 - 269;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    if (spincount2 % 4 == 3)
                    {
                        Pika2.setTextureRect(IntRect(403, 0, 539 - 402, 96));
                        hitx2 = 539 - 402;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    spincount2++;
                }
            }

            ///----------------------
            if ((Keyboard::isKeyPressed(Keyboard::Left)) && (Keyboard::isKeyPressed(Keyboard::Numpad2)) && (!Pika2.isAttacking()))
            {
                Pika2.setSideSpecialLeft(true);
                Pika2.setCanMove(false);
                Pika2.setCanJump(false);
                Pika2.setTexture(charge2);
                Pika2.setTextureRect(IntRect(0, 0, 130, 108));
                hitx2 = 130;
                hity2 = 108;
                if (!p2.empty())
                {
                    p2.front().destroy(world);
                    p2.erase(p2.begin());
                    p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                }
                else
                    p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                //cout << "hello" << endl;
                if (!Pika2.getPulse())
                    sideb2.restart();
                Pika2.setPulse(true);

            }

            if (((!Keyboard::isKeyPressed(Keyboard::Left)) || (!Keyboard::isKeyPressed(Keyboard::Numpad2)) || (sideb2.getElapsedTime().asSeconds() > 1.5) || (!Pika2.getPulse())) && (Pika2.isSideSpecialLeft()))
            {

                if (Pika2.getPulse())
                {
                    diffvel = -Pika2.getVerticalVelocity() * Pika2.getMass();
                    Pika2.Rise(diffvel);
                    diffvel = -Pika2.getHorizontalVelocity() * Pika2.getMass();
                    Pika2.Move(diffvel);
                    Pika2.Rise(-150);
                    Pika2.Move(-200 * sideb2.getElapsedTime().asSeconds());
                    Pika2.setPulse(false);
                    sideb2.restart();
                }
                if (((Pika2.isGrounded()) && (!Pika2.getPulse()) && (sideb2.getElapsedTime().asSeconds() > 0.2)) || (sideb2.getElapsedTime().asSeconds() > 1))
                {
                    Pika2.setAttacking(false);
                    Pika2.setSideSpecialLeft(false);
                    Pika2.setCanMove(true);
                    Pika2.setCanJump(true);
                }
                else
                {
                    Pika2.setAttacking(true);
                    Pika2.setTexture(spin2);

                    if (spincount2 % 4 == 0)
                    {
                        Pika2.setTextureRect(IntRect(409, 0, 544 - 409, 96));
                        hitx2 = 544 - 409;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    if (spincount2 % 4 == 1)
                    {
                        Pika2.setTextureRect(IntRect(274, 0, 408 - 274, 96));
                        hitx2 = 408 - 274;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    if (spincount2 % 4 == 2)
                    {
                        Pika2.setTextureRect(IntRect(140, 0, 273 - 140, 96));
                        hitx2 = 273 - 140;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    if (spincount2 % 4 == 3)
                    {
                        Pika2.setTextureRect(IntRect(0, 0, 139, 96));
                        hitx2 = 139;
                        hity2 = 96;
                        if (!p2.empty())
                        {
                            p2.front().destroy(world);
                            p2.erase(p2.begin());
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                        }
                        else
                            p2.push_back(Hitbox(world, hitx2, hity2, Pika2.getPosition().x, Pika2.getPosition().y, 0));
                    }
                    spincount2++;
                }
            }
            if ((!Pika1.isSideSpecialLeft()) && (!Pika1.isSideSpecialRight()) &&
                (!Pika2.isSideSpecialLeft()) && (!Pika2.isSideSpecialRight()) &&
                (doublehit))
            {
                doublehit = false;
            }




    /// |------------------------------- COLLISIONS --------------------------------|
            world.Step(1.0/240, int32(8), int32(3));
            if ((!Pika1.isInvincible()) && (!Pika2.isInvincible()))
            {
                if ((!p1.empty()) && (!p2.empty()))
                {
                    if (p1.front().isColliding(p2.front().getBody()))
                    {
                        if ((Pika1.isSideSpecialRight() || Pika1.isSideSpecialLeft()) && (Pika2.isSideSpecialRight() || Pika2.isSideSpecialLeft()) && (!doublehit))
                        {
                            if (abs(Pika1.getHorizontalVelocity()) > abs(Pika2.getHorizontalVelocity()))
                            {
                                Pika2.Move(Pika1.getHorizontalVelocity() * 10 * (1 + 0.1 *Pika2.getDamage()));
                                Pika2.Rise(-abs(Pika1.getHorizontalVelocity()) * 20 * (1 + 0.1 *Pika2.getDamage()));
                                diffvel = -Pika1.getHorizontalVelocity() * Pika1.getMass();
                                Pika2.setDamage(Pika2.getDamage() + abs(1.0 * Pika1.getHorizontalVelocity()));
                                Pika1.Move(diffvel);

                            }
                            else if (abs(Pika1.getHorizontalVelocity()) < abs(Pika2.getHorizontalVelocity()))
                            {
                                Pika1.Move(Pika2.getHorizontalVelocity() * 10 * (1 + 0.1 *Pika1.getDamage()));
                                Pika1.Rise(-abs(Pika2.getHorizontalVelocity()) * 20 * (1 + 0.1 *Pika1.getDamage()));
                                diffvel = -Pika2.getHorizontalVelocity() * Pika2.getMass();
                                Pika1.setDamage(Pika1.getDamage() + abs(1.0 * Pika2.getHorizontalVelocity()));
                                Pika2.Move(diffvel);

                            }
                            else if (abs(Pika1.getHorizontalVelocity() == Pika2.getHorizontalVelocity()))
                            {
                                diffvel = -Pika1.getHorizontalVelocity() * Pika1.getMass();
                                Pika1.Move(diffvel);
                                diffvel = -Pika2.getHorizontalVelocity() * Pika2.getMass();
                                Pika2.Move(diffvel);
                            }
                            doublehit = true;

                        }
                        else if ((Pika1.isSideSpecialRight() || Pika1.isSideSpecialLeft()) && (!Pika2.isSideSpecialRight() && !Pika2.isSideSpecialLeft()))
                        {
                            Pika2.Move(Pika1.getHorizontalVelocity() * 10 * (1 + 0.1 *Pika2.getDamage()));
                            Pika2.Rise(-abs(Pika1.getHorizontalVelocity()) * 20 * (1 + 0.1 *Pika2.getDamage()));
                            diffvel = -Pika1.getHorizontalVelocity() * Pika1.getMass();
                            Pika2.setDamage(Pika2.getDamage() + abs(1.0 * Pika1.getHorizontalVelocity()));
                            Pika1.Move(diffvel);

                            //cout << "Hello" << endl;
                        }
                        else if ((Pika2.isSideSpecialRight() || Pika2.isSideSpecialLeft()) && (!Pika1.isSideSpecialRight() && !Pika1.isSideSpecialLeft()))
                        {
                            Pika1.Move(Pika2.getHorizontalVelocity() * 10 * (1 + 0.1 *Pika1.getDamage()));
                            Pika1.Rise(-abs(Pika2.getHorizontalVelocity()) * 20 * (1 + 0.1 *Pika1.getDamage()));
                            diffvel = -Pika2.getHorizontalVelocity() * Pika2.getMass();
                            Pika1.setDamage(Pika1.getDamage() + abs(1.0 * Pika2.getHorizontalVelocity()));
                            Pika2.Move(diffvel);

                        }
                        //cout << Pika1.getHorizontalVelocity() << " " << Pika2.getHorizontalVelocity() << endl;
                    }
                }
            }






    /// |--------------------------- View Management -----------------------------|
            /// Camera works so that the characters (in this preliminary stage, pikachu and a square) are focused, with the aspect ratio the SAME.
            xscreen = findDx(Pika1.getPosition().x, Pika2.getPosition().x) + 500; /// + 500 for surroundings
            yscreen = findDy(Pika1.getPosition().y, Pika2.getPosition().y) + 375; /// + 375 for surroundings
            //cout << xscreen << " " << xscreen / 1200 * 900 << " " << endl;
            //cout << yscreen / 900 * 1200 << " " << yscreen << endl;
            /// *********Reposition glitch needs to be fixed*********
            if ((xscreen > 800) || (yscreen > 600))
            {
                if (xscreen > yscreen * 4/3)
                {
                    camera.setSize(Vector2f(xscreen, xscreen / 1200 * 900));  /// ensures the ratio of x:y is the same when resizing the view

                }
                else
                {
                    camera.setSize(Vector2f(yscreen / 900 * 1200, yscreen));  /// "                                                          "

                }

            }
            else
                camera.setSize(Vector2f(800, 600));
            /// Sets center at the average coordinates of the two points of reference
            camera.setCenter(Vector2f(findAx(Pika1.getPosition().x, Pika2.getPosition().x) + 90, findAy(Pika1.getPosition().y, Pika2.getPosition().y) + 20));
            screemx = camera.getSize().x;
            screemy = camera.getSize().y;
            mid.setPosition(camera.getCenter().x, camera.getCenter().y); /// Making sure the camera is really at the center
            xc = mid.getPosition().x; /// Coordinates for later
            yc = mid.getPosition().y;
            window.setView(camera);

    /// |-------------------------- Updating POV ------------------------|
           // cout << xc - FakeBase.getPosition().x << " " << yc - FakeBase.getPosition().y << endl;
            aBase[1].position.y = (yc - FakeBase[0].position.y) * 1000 / 5587 + FakeBase[0].position.y; /// Fun numbers I know
            aBase[2].position.y = (yc - FakeBase[0].position.y) * 1000 / 5587 + FakeBase[0].position.y;  /// NOOO WAY THIS IS SO COOL
            aBase[1].position.x = (xc - FakeBase[0].position.x) * 0.05 + FakeBase[0].position.x;
            aBase[2].position.x = (xc - (FakeBase[0].position.x + 800)) * 0.05 + FakeBase[0].position.x + 800;  /// Too cool

            aBaseLeft[1].position.y = aBase[1].position.y;
            aBaseLeft[1].position.x = aBase[1].position.x;
            aBaseLeft[2].position.x = aBase[1].position.x;
            aBaseLeft[2].position.y = aBaseLeft[1].position.y + 15;

            aBaseRight[1].position.y = aBase[2].position.y;
            aBaseRight[1].position.x = aBase[2].position.x;
            aBaseRight[2].position.x = aBase[2].position.x;
            aBaseRight[2].position.y = aBaseRight[1].position.y + 15;

            aBaseBottom[1].position.y = aBaseRight[2].position.y;
            aBaseBottom[1].position.x = aBaseRight[2].position.x;
            aBaseBottom[2].position.y = aBaseLeft[2].position.y;
            aBaseBottom[2].position.x = aBaseLeft[2].position.x;

            /// Real invisible base warping
            /// **************************** STILL NEEDS TO BE FIXED **********************************************
            if ((!Keyboard::isKeyPressed(Keyboard::A)) || (!Keyboard::isKeyPressed(Keyboard::D)))
            {
                friction = 1.7;

            }
            else
                friction = 0.0;
            if (!Base.empty())
                {
                    Base[0].destroy(world);
                    Base.erase(Base.begin());
                }
            ax = findAx(FakeBase[0].position.x, aBase[1].position.x);
            ay = findAy(FakeBase[0].position.y, aBase[1].position.y);
            dx = findDx(findAx(FakeBase[1].position.x, aBase[2].position.x), ax);
            Base.push_back(Platform(world, dx, dy, ax, ay + 5, Color::White, friction));
            //cout << Pika1.getPosition().y << " " << Base[0].getPosition().y << endl;


    /// |------------------------------------------------------------------|





    /// |------------------------------------------------------------------|


    /*
            /// For use of camera without having to move pikachu around
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                refersquare.move(-3, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                refersquare.move(3, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                refersquare.move(0, -3);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                refersquare.move(0, 3);
            }

    */

    /// |-------------------- Updating Commands ---------------------------------|
            world.Step(1.0/240, int32(8), int32(3));
            Pika1.updatePosition();
            Pika2.updatePosition();
    /// |--------------------- Drawing commands ----------------------|
            window.draw(mid);
            //window.draw(refersquare);
            if (yc < 580 + 86.26)
                window.draw(aBaseBottom);
            if (xc < 1000)
                window.draw(aBaseRight);
            if (xc > 200)
                window.draw(aBaseLeft);
            window.draw(aBase);
            if (xc > 1000)
                window.draw(aBaseRight);
            if (xc < 200)
                window.draw(aBaseLeft);
            window.draw(Pika1);
            window.draw(Pika2);
            if (yc >=  580 + 86.26)
                window.draw(aBaseBottom);
            window.draw(FakeBase);

            camerax = camera.getCenter().x;
            cameray = camera.getCenter().y;
            cposx = camerax - (0.5 * screemx);
            cposy = cameray - (0.5 * screemy);
            icon1.setScale(screemx / (2048 * sizeratio), screemx / (2048 * sizeratio)); /// makes the player stats the same size, all the time.
            icon2.setScale(screemx / (2048 * sizeratio), screemx / (2048 * sizeratio));
            icon1.setPosition(cposx + (1.0/3) * screemx - 30, cposy + (7.0 / 9) * screemy);
            icon2.setPosition(cposx + (2.0/3) * screemx - 30, cposy + (7.0 / 9) * screemy);

            //cout << icon2.getPosition().x << " " << icon2.getPosition().y << endl;

            health1.setString(to_string(int(Pika1.getDamage())) + "%");
            health1.setFillColor(Color(255, 255 - 2 * Pika1.getDamage(), 255 - 2 * Pika1.getDamage()));
            health1.setPosition(cposx + (1.0/3) * screemx - 30, cposy + (8.0 / 9) * screemy);
            health1.setScale(screemx / 1200, screemx / 1200);
            health2.setString(to_string(int(Pika2.getDamage())) + "%");
            health2.setFillColor(Color(255, 255 - 2 * Pika2.getDamage(), 255 - 2 * Pika2.getDamage()));
            health2.setPosition(cposx + (2.0/3) * screemx - 30, cposy + (8.0 / 9) * screemy);
            health2.setScale(screemx / 1200, screemx / 1200);

            life1.setString(to_string(int(Pika1.getLives())));
            life1.setFillColor(Color(255, 255 - 50 * (5 - Pika1.getLives()), 255 - 50 * (5 - Pika1.getLives())));
            life1.setPosition(cposx + (1.0/3) * screemx - 30, cposy + (8.5 / 9) * screemy);
            life1.setScale(screemx / 1200, screemx / 1200);
            life2.setString(to_string(int(Pika2.getLives())));
            life2.setFillColor(Color(255, 255 - 50 * (5 - Pika2.getLives()), 255 - 50 * (5 - Pika2.getLives())));
            life2.setPosition(cposx + (2.0/3) * screemx - 30, cposy + (8.5 / 9) * screemy);
            life2.setScale(screemx / 1200, screemx / 1200);

            if ((Pika1.getLives() <= 0) || (Pika2.getLives() <= 0))
            {
                gameover = true;
                if (Pika1.getLives() > 0)
                    {
                        winner.setString("YELLOW WINS!");
                        winner.setFillColor(Color::Yellow);
                        winner.setPosition(130, 400);
                    }
                if (Pika2.getLives() > 0)
                    {
                        winner.setString("RED WINS!");
                        winner.setFillColor(Color::Red);
                        winner.setPosition(250, 400);
                    }
                start = false;
                song.pause();

            }



            window.draw(icon1);
            window.draw(icon2);
            window.draw(health1);
            window.draw(health2);
            window.draw(life1);
            window.draw(life2);
        }
        if (gameover)
        {
            window.setView(View(Vector2f(1200 / 2, 900 / 2), Vector2f(1200, 900)));


            again.checkMouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y, Mouse::isButtonPressed(Mouse::Left), gameover);
            if (!gameover)
            {

                startscreen = true;
                instructions = true;
                Pika1.setLives(5);
                Pika1.setDamage(0);
                Pika2.setLives(5);
                Pika2.setDamage(0);

            }
            window.draw(again);
            window.draw(retry);

            window.draw(winner);
        }


        if ((startscreen) && (instructions))
        {
            window.draw(titlescreen);
            window.draw(smash);
            window.draw(wordy);

            play.checkMouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y, Mouse::isButtonPressed(Mouse::Left), startscreen);
            if (!startscreen)
                {
                    start = true;
                    Pika1.setPosition(250, 100);
                    Pika1.setBoxPosition(Vector2f(250, 100));
                    Pika2.setPosition(800, 100);
                    Pika2.setBoxPosition(Vector2f(800, 100));
                    song.play();
                    song.setLoop(true);
                }
            window.draw(play);
            window.draw(playw);
            if (clackclick.getElapsedTime().asSeconds() > 0.3)
            {
                in.checkMouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y, Mouse::isButtonPressed(Mouse::Left), instructions);
            }
            window.draw(in);
            window.draw(inw);

            clickclack.restart();
        }

        if (!instructions)
        {
            window.draw(helppage);
            if (clickclack.getElapsedTime().asSeconds() > 0.3)
                backy.checkMouse(Mouse::getPosition(window).x, Mouse::getPosition(window).y, Mouse::isButtonPressed(Mouse::Left), goback);
            if (!goback)
            {
                instructions = true;
                goback = true;
                clackclick.restart();
            }
            window.draw(backy);
            window.draw(backw);

        }




        window.display();   //displays everything on the video card to the monitor
    }   //ends the game loop

    return 0;
}
