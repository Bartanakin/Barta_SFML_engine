#include"PhisicObject.h"
#include<cmath>

const float PhisicObject::g = 9.81f;
const float PhisicObject::metersToPx = 100.f;
PhisicObject::PhisicObject(float spriteX, float spriteY,Hitbox _hitbox, Texture& _t, Mass _mass, Font& _f, std::string _text, int _letterSize )
:Object(spriteX, spriteY, _hitbox, _t, _f, _text, _letterSize),
mass(_mass),
velocity(0,0),
resultantForse(0,_mass.getValue()*g),
dynamicsAvailability(false),
movingAvailability(false){
    moveTimer.restart();
}
void PhisicObject::setPosition(float x, float y){
    /*
        @returns void 
        Sets the position given by parameters both Object and mass.
    */
    Object::setPosition(x,y);
    mass.setPosition(Vector2f(x,y));
}
void PhisicObject::setRotation( float angle ){
    /*
        @returns void 
        Sets the Rotation given by parameter to both Object and mass.
    */
    Object::setRotation(angle);
    mass.setRotation(angle);
}
void PhisicObject::setScale( float factorX, float factorY ){
    /*
        @returns void 
        Sets the Scale given by parameters to both Object and mass.
    */
    Object::setScale(factorX,factorY);
    mass.setScale(factorX,factorY);
}
void PhisicObject::setOrigin(float x, float y){
    /*
        @returns void 
        Sets the position of origin point by values given by parameters of both Object and mass.
    */
    Object::setOrigin(x,y);
    hitbox.move( - x + Sprite::getOrigin().x, - y + Sprite::getOrigin().y );
    mass.setOrigin(x,y);
}
void PhisicObject::setOrigin( Vector2f v ){
    /*
        @returns void 
        Sets the position of origin point by values given by parameters of both Object and mass.
    */
    setOrigin( v.x, v.y );
}
void PhisicObject::move(float x, float y){
    /*
        @returns void 
        Moves both Object and mass by distance given by parameters.
    */
    Object::move(x,y);
    mass.move(x,y);
}
void PhisicObject::scale( float factorX, float factorY ){
    /*
        @returns void 
        Scales both Object and mass by factors given by parameters.
    */
    Object::setScale(factorX,factorY);
    mass.setScale(factorX,factorY);
}
void PhisicObject::rotate( float angle ){
    /*
        @returns void 
        Rotates both Object and mass by angle given by parameter.
    */
    Object::rotate(angle);
    mass.rotate(angle);
}

void PhisicObject::checkMove(){
    Time t = moveTimer.restart();
    //std::cout << velocity.y << " ";
    if(!dragged){
        float vx0 = velocity.x;
        float vy0 = velocity.y;
        move((velocity.x * t.asSeconds())*metersToPx, (velocity.y * t.asSeconds())*metersToPx); /// Movement of the object
        velocity.x = velocity.x + resultantForse.x * t.asSeconds() / mass.getValue(); /// Influence of acceleration on the velocity
        velocity.y = velocity.y + resultantForse.y * t.asSeconds() / mass.getValue(); /// Influence of acceleration on the velocity
        bool f1 = false;
        Object *buffObj2 = this->getNextObject(); // iterator of the inner loop
            if (this->getCollisionAvailability())     // Checking if collisions are allowed.
            {
                do
                {
                    if (buffObj2->getCollisionAvailability()) // Checking if collisions are allowed to the second Object.
                    {
                        if (this->checkCollision(buffObj2))
                        {
                            f1 = true;
                            break;
                        }
                    }

                    buffObj2 = buffObj2->getNextObject(); // incrementing inner loop
                } while (buffObj2 != this);
            }
        if( f1 ){

        }
    }
}

void PhisicObject::checkDynamics(float frictionRatio){
    Time t = dynamicsTimer.restart();
    if(!dragged && (velocity.x!=0 || velocity.y!=0)){ /// Friction
         float friction = mass.getValue()*g*frictionRatio;
         float velocity0 = sqrt(pow(velocity.x,2)+pow(velocity.y,2));
         resultantForse.x = -(friction*velocity.x)/velocity0;
         resultantForse.y = -(friction*velocity.y)/velocity0;
       // std::cout <<velocity.x << " " << friction << " " << velocity0 << std::endl;
    }
}

void PhisicObject::setMovingAvailability(bool f1){
    if( f1 != movingAvailability){
        velocity.x = 0;
        velocity.y = 0;
        moveTimer.restart();
    }
    movingAvailability = f1;
}
bool PhisicObject::getMovingAvailability(){
    return movingAvailability;
}

void PhisicObject::setDynamicsAvailability(bool f1){   
    movingAvailability = f1;
}
bool PhisicObject::getDynamicsAvailability(){
    return dynamicsAvailability;
}

void PhisicObject::setVelocity(Vector2f v){
    velocity = v;
}
Vector2f PhisicObject::getVelocity(){
    return velocity;
}

PhisicObject::~PhisicObject()
{
    
}
