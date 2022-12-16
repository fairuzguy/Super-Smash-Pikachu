#ifndef CAMERA
#define CAMERA

/// "Camera" Class

#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>
#include <Box2D/Box2D.h>

/// Notice: This class was originally for producing a moving "camera" view, but window.setView(Camera) does not work.
/// So, I've made a function class out of it that helps with calculations for distortions of the 3D world.

using namespace sf; //for graphics

class Camera
{
    public :

        float findDx(float x1, float x2)
        {
            if (x2 - x1 >= 0)
                return (x2 - x1);
            else
                return (x1 - x2);
        }
        float findDy(float y1, float y2)
        {
            if (y2 - y1 >= 0)
                return (y2 - y1);
            else
                return (y1 - y2);
        }
        float findDt(float x1, float x2, float y1, float y2)
        {
            return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        }

    private :
        /// I realize now this is a really useless class

};

#endif // Camera

