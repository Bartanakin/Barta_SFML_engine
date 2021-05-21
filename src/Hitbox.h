#ifndef Hitbox_h
#define Hitbox_h

#include <vector>
#include "Line.h"
#include "MyMatch.h"
using namespace sf;

class Hitbox
{
public:
    // Type of Shape of the Hitbox.
    enum Shape{
        // Custom shape consisting of straght lines.
        BezierCurves = 0,
        // A rectangle parallel to the axises.
        Rectangle = 1,
        // A circle. 
        Circle = 2,
        // The same as the Sprite rectangle.
        DefaultRectangle = 3,
        // The same as the Sprite rectangle but circle shape.
        DefaultCircle = 4
    };
    int type; 

    // The top left point's coordinates.
    float top;
    float left;
    // The size of the hitbox.
    float width;
    float height;
    // The radius
    float radius;
    // The number of lines that the hitbox consist of.
    int lengthOfSource;
    // The vector of those lines.
    std::vector<Vector2f> points;

    // Standard constructor.
    Hitbox(int _type = 0,float _left = 0,float _top = 0,float _width_or_radius = 0,float height = 0 );
    // Debug function.
    void writeLines();
    void writeRect();
    // Circle Shape functions
    Vector2f getCenter();
    //float getRadius();
    // Functions reffering to Transform class.
    void setTransform( Transform& transform );
    void move( float x, float y );
    void scale( float factorX, float factorY );
    void rotate( float angle );
    // Loading Hitbox from file.
    bool loadFromFile( std::string source );
    // Point containing handling funcions. 
    bool isWithinHitbox(float,float);
    bool isWithinRectangle(float,float);
    bool isWithinCircle(float,float);
    bool isWithinBezierCurves(float,float);
    // Collision handling functions.
    bool checkCollision( Hitbox&,float,float);
    bool checkCollRectRect( Hitbox&,float,float);
    bool checkCollCirCir( Hitbox&,float,float);
    bool checkCollBeziBezi( Hitbox&,float,float);
    bool checkCollBeziCir( Hitbox&,float,float);
    bool checkCircleAndLineCrossing( Line& );

    // Functions reffering to Rectangle class.

    Rect<float> getRect();

    ~Hitbox();

};
#endif
