#ifndef Mass_h
#define Mass_h
#include <SFML/Graphics.hpp>
using namespace sf;
class Mass :public Transformable{

    // The value of the mass
    float value;
    // The center of the mass relative to the owner's position.
    Vector2f center;
    
    public:
    // Access functions
    Mass();
    Mass(float _value, Vector2f _center );
    // Functions reffering to inherited class.
    void setPosition( Vector2f v );
    void setRotation( float angle );
    void setScale( float factorX, float factorY );
    void setOrigin( float x, float y );
    void setOrigin( Vector2f v );
    void move( float x, float y);
    void scale( float factorX, float factorY );
    void rotate( float angle );
    void setString(std::string);
    float getValue();
    void setValue(float _value);

    Vector2f getCenter();
    void setCenter(Vector2f _center);

    // Othe functions

    Mass findMassCenter(Mass* m2, Vector2f distance );
};

#endif