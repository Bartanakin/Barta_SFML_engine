#include"Family.h"

Family::Family(std::string _name = "")
:Transformable(),
numberOfObjects(0),
objects(),
translation(0,0),
name(_name)
{
    /*
        Default constructor.
    */
}

Family::~Family(){
    /*
        Default destructor.
    */
}

void Family::move(float x, float y){
    /*
        @returns void.
        Moves all Objects in the family.
    */
    for( int i = 0; i < numberOfObjects; i++ ){
        objects[i] -> move(x,y);
    }
    Transformable::move(x,y);
}
void Family::setPosition(float x, float y){
    /*
        @returns void.
        Sets position to all Objects in the family.
        Keeps the distances between Objects.
    */
    for( int i = 0; i < numberOfObjects; i++ ){
        objects[i] -> setPosition(x + objects[i] -> Sprite::getPosition().x - Transformable::getPosition().x,y + objects[i] -> Sprite::getPosition().y - Transformable::getPosition().y );
    }
    Transformable::setPosition(x,y);
}
void Family::scale(float xFactor, float yFactor){
    /*
        @returns void.
        Sets scale to all Objects in the family.
        Scales the distances between Objects also.
    */
    for( int i = 0; i < numberOfObjects; i++ ){
        objects[i] -> move( ( xFactor - 1 )*( objects[i] -> Sprite::getPosition().x - Transformable::getPosition().x ) , ( yFactor - 1 )*( objects[i] -> Sprite::getPosition().y - Transformable::getPosition().y ) );
        objects[i] -> scale(xFactor,yFactor);
    }
    Transformable::scale(xFactor,yFactor);
}


