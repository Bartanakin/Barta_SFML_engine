#include"Mass.h"

Mass::Mass()
:Transformable::Transformable()
{
    /*
        Default constructor.
    */
}
Mass::Mass(float _value, Vector2f _center )
:Transformable::Transformable(),
value(_value),
center(_center){
    /*
        Standard constructor.
    */
}
void Mass::setPosition(Vector2f v){
    /*
        @returns void 
        Sets the position given by parameters to the mass center.
    */
    Transformable::setPosition(v);
    Transform t;
    t.translate( v - getPosition() );
    setCenter( t.transformPoint( getCenter()) );
}
void Mass::setRotation( float angle ){
    /*
        @returns void 
        Sets the Rotation given by parameter to the mass center.
    */
    Transformable::setRotation(angle);
    Transform t;
    t.rotate( angle - getRotation() );
    setCenter( t.transformPoint( getCenter()) );
}
void Mass::setScale( float factorX, float factorY ){
    /*
        @returns void 
        Sets the Scale given by parameters to the mass center.
    */
    Transformable::setScale(factorX, factorY);
    Transform t;
    t.scale( Vector2f(factorX, factorY) - getScale() );
    setCenter( t.transformPoint( getCenter()) );
}
void Mass::setOrigin(float x, float y){
    /*
        @returns void 
        Sets the position of origin point by values given by parameters of the mass center.
    */
}
void Mass::setOrigin( Vector2f v ){
    /*
        @returns void 
        Sets the position of origin point by values given by parameters of the mass center.
    */
    setOrigin( v.x, v.y );
}
void Mass::move(float x, float y){
    /*
        @returns void 
        Moves the mass center by distance given by parameters.
    */
    Transformable::move(x,y);
    Transform t;
    t.translate( x,y );
    setCenter( t.transformPoint( getCenter()) );
}
void Mass::scale( float factorX, float factorY ){
    /*
        @returns void 
        Scales the the mass center by factors given by parameters.
    */
    Transformable::scale(factorX,factorY);
    Transform t;
    t.scale( factorX,factorY );
    setCenter( t.transformPoint( getCenter()) );
}
void Mass::rotate( float angle ){
    /*
        @returns void 
        Rotates the mass center by angle given by parameter.
    */
    Transformable::rotate(angle);
    Transform t;
    t.rotate( angle );
    setCenter( t.transformPoint( getCenter()) );
}

float Mass::getValue(){
    /*
        @returns the value of the mass.
    */
   return value;
}
void Mass::setValue(float _value){
    value = _value;
}
Vector2f Mass::getCenter(){
    return center;
}
void Mass::setCenter(Vector2f _center){
    center = _center;
}
Mass Mass::findMassCenter(Mass* m2, Vector2f distance ){
    /*
        @returns a new mass object which value is a sum and the center is a new center of mass.
        First argument is a pointer to the second Mass object and the second is the vector from this origin of Mass owner
        to the second.
    */

    Mass m;
    m.setValue( this -> getValue() + m2 -> getValue() );
    m.setCenter( Vector2f((this -> getValue() * this -> getCenter().x + m2 -> getValue() * (m2 -> getCenter().x + distance.x))/(m.getValue()),(this -> getValue() * this -> getCenter().y + m2 -> getValue() * (m2 -> getCenter().y + distance.y))/(m.getValue())) );
    return m;
}
