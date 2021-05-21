#ifndef PhysicObject_h
#define PhysicObject_h

#include"Object.h"
#include"Mass.h"

class PhisicObject
:public Object{

    static const float g;
    static const float metersToPx;
    Mass mass;
    Vector2f velocity;
    Vector2f resultantForse;
    bool dynamicsAvailability;
    bool movingAvailability;
    Clock moveTimer;
    Clock dynamicsTimer;

public:
    PhisicObject(float spriteX, float spriteY,Hitbox _hitbox, Texture& _t, Mass _mass, Font& _f, std::string _text = "", int _letterSize = 20 );
    // Functions reffering to inherited class.
    void setPosition( float x, float y );
    void setRotation( float angle );
    void setScale( float factorX, float factorY );
    void setOrigin( float x, float y );
    void setOrigin( Vector2f v );
    void move( float x, float y);
    void scale( float factorX, float factorY );
    void rotate( float angle );
    void setString(std::string);
    
    // Access functions
    void setMovingAvailability(bool);
    bool getMovingAvailability();

    void setDynamicsAvailability(bool);
    bool getDynamicsAvailability();

    void setVelocity(Vector2f v);
    Vector2f getVelocity();

    void checkDynamics(float);
    void checkMove();

    ~PhisicObject();
};
#endif