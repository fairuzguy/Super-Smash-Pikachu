#ifndef BUTTONS
#define BUTTONS

#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>


using namespace sf;

class Button : public RectangleShape
{
    public :
        Button(float dx, float dy, float posx, float posy, Color fil, Color out)
        {
            this->setPosition(posx, posy);
            this->setSize(Vector2f(dx, dy));
            this->setFillColor(fil);
            this->setOutlineColor(out);
            this->setOutlineThickness(2);
            outline = out;
            col = fil;
            xpos = posx;
            ypos = posy;
        }


        void checkMouse(float x, float y, bool clicky, bool &start)
        {

            if ((x >= this->getPosition().x) && (x <= this->getPosition().x + this->getSize().x) &&
                (y >= this->getPosition().y) && (y <= this->getPosition().y + this->getSize().y))
            {
                this->setOutlineColor(this->getFillColor() + Color(23, 30, -50));
                this->setOutlineThickness(4);
                this->setScale(Vector2f(1.1f, 1.1f));
                this->setPosition(xpos + this->getSize().x / 2 - this->getSize().x * 1.1 / 2, ypos + this->getSize().y / 2 - this->getSize().y * 1.1 / 2);

                if (clicky)
                {
                    //cout << "Commencing game" << endl;
                    start = false;
                }
                else
                    start = true;
            }
            else
            {
                this->setOutlineColor(outline);
                this->setOutlineThickness(2);
                this->setScale(Vector2f(1.0f, 1.0f));
                this->setPosition(xpos, ypos);
            }


        }

    private :

        Color col;
        Color outline;
        float xpos;
        float ypos;







};







#endif // BUTTONS
