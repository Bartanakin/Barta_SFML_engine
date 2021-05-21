#ifndef Object_h
#define Object_h

#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace sf;

class Object :public Sprite, public Text
{
private:
    
    // Variable used to identify Objects.
    static int id;
    // Pointer to the first Object in the list.
    static Object* firstObject;
    // Position of the Object in the privious frame when dragged
    Vector2f initialDrag;
    // Actual hitbox of the Object.
    // This is a copy of the real Hitbox variable.
    public:
    Hitbox hitbox;
    Hitbox* hitboxPointer;
    // Variables which allow some functions:
    bool draggingAvailability; // Dragging.
    bool collisionAvailability; // Collisions.
    // Value by which the Objects are ordered in the list what allows to control the sequence of drawing of them.
    int z;
    // Pointer to the next Object in the list.
    // If this Object is not in the list the pointer indicates null.
    // If this Object is the only Object in the list the pointer indicates this Object.
    Object *nextObject;
    // The id of the Object. 
    std::string name;
    // Functions controlling the attachment the Object to the list.
    void addToList();
    void removeFromList();

protected:

    // Enumeration of placement of the Text relatively to the Sprite...
    enum TextPosition{
        Center = 1
    };
    // ... and the variable telling which Text placement is now.
    int textPos;
    // Tells if the Object is being dragged. 
    bool dragged;

public:

    // Default constructor.
    Object();// TODO
    // Standard constructor 
    Object(float xPosition,float yPosition,Hitbox _hitbox,Texture& _texture,Font& _font,std::string writtenText="",int letterSize= 20);
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
    Vector2f getGlobalCenter();
    // Functions handling dragging system.   
    virtual void onDrag( const Event& mainEventVariable);
    virtual void onDrag( const Event& mainEventVariable, bool onPickUp, bool onDrop );
    // Function setting the textPostion ( see enumeration ) 
    void setTextPosition(int _textPostion );
    // Function setting new z value. It also may change sequence of the Objects in the list.
    void setZ(int new_z);
    // Hitbox functions
    bool checkCollision(Object* pointerToTheSecondObject);
    bool isWithinHitbox(float x,float y);
    // Event functions.
    bool onClick(const Event& mainEventVariable,Mouse::Button);
    bool onPress(const Event& mainEventVariable,Keyboard::Key);
    bool onDeClick(const Event& mainEventVariable);
    bool onRelease(const Event& mainEventVariable, Mouse::Button b = Mouse::Left);
    bool onRelease(const Event& mainEventVariable, Keyboard::Key);
    bool onHover(const Event& mainEventVariable);
    
    // Access funcions
    void setDraggingAvailability(bool);
    bool getDraggingAvailability();

    void setCollisionAvailability(bool);
    bool getCollisionAvailability();

    Object* getNextObject();
    std::string getName(); 
    static Object* getFirstObject();

    // PhysicObject
    virtual void setMovingAvailability(bool);
    virtual bool getMovingAvailability();

    virtual void setDynamicsAvailability(bool);
    virtual bool getDynamicsAvailability();

    virtual void setVelocity(Vector2f v);
    virtual Vector2f getVelocity();

    virtual void checkDynamics(float);
    virtual void checkMove();
    
    // InputText functions 
    virtual void checkInputText(const Event&); 

    // Default destructor
    ~Object();
};
#endif
