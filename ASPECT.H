#ifndef ASPECT
#define ASPECT

/// "Aspect" Class

#include <SFML/Graphics.hpp> //includes SFML libraries
#include <math.h>
#include <Box2D/Box2D.h>


using namespace sf; //for graphics

class Aspect : public VertexArray
{
    public :
        Aspect(PrimitiveType p1)
        {
            this->setPrimitiveType(p1);
        }

        void addVertex(Vertex vertex)
        {
            this->append(vertex);
        }

    private :


};

#endif // Aspect
