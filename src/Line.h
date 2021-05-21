#ifndef Line_h
#define Line_h

#include <SFML/Graphics.hpp>
using namespace sf;

class Line
{
public:
    Vector2f v1;
    Vector2f v2;

    Line();
    Line(Vector2f v1,Vector2f v2);
    float A(float=0,float=0);
    float B(float=0,float=0);
    float C(float=0,float=0);
    bool checkPoint(float x, float y);
    bool checkCrossing(  Line&, float xd=0, float yd=0 );

};
#endif

