//#include <SFML/Graphics.hpp>

#include "Object.h"
using namespace sf;

int Object::id = 0;
Object* Object::firstObject = nullptr;
void Object::addToList(){

    /*
        @returns void
        Adds this Object to the list.
        If the static "firstObject" is null pointer then creates a new list and this Object is the first Object in the list.
        If the Object given by parameter is in the list already, nothing happens.
    */
    // Creating a new list.
    bool f1 = true;
    if( firstObject == nullptr ){
        // Case when this is the first Object in the list.
        nextObject = this;
        firstObject = this;
    }
    else
    {
        Object *buffObj = firstObject; // iterator
        do
        {
            if (buffObj == this)
            {
                // If the Object given by parameter is in the list already set flag to false.
                f1 = false;
                break;
            }
            buffObj = buffObj->nextObject; //incrementing
        }while (buffObj != firstObject); // Note: "do .. while" because I need check the first Object too.
    }
    if (f1)
    {        
        Object *buffObj = firstObject; // iterator
        if( z < firstObject -> z ){ // Chcecking if this Object's "z" is smaller than the first Object's one.
            while( buffObj -> nextObject != firstObject ){
                // Increments until it finds the last Object in the list.
                buffObj = buffObj -> nextObject; // incrementing
            }
            // Then sets this Object as first Object.        
           firstObject = this;
        }
        else{
            // This loop insert this Object in place so that the "z" values are ordered ascending.
            while (z >= buffObj->nextObject->z && buffObj->nextObject != firstObject)
            {
                // Increments until it finds an Object with a greater "z" or until the end of the list.
                buffObj = buffObj->nextObject; // incrementing
            }
        }

        // Adding this Object between "buffObj" and "buffObj -> nextObject".
        this -> nextObject = buffObj -> nextObject;
        buffObj -> nextObject = this;
    }
}
void Object::removeFromList()
{   
    /*
        @returns void
        When there are more than one Objects removes this Object from the list.
    */
    Object *buffOb = nextObject; // iterator
    if ( this == nextObject ) // When there is only one Object in the list left sets the first Object pointer to NULL.
    {
        firstObject = nullptr;
    }
    else
    {
        while (buffOb->nextObject != this) // Looking for this Object in the list...
        {
            buffOb = buffOb->nextObject; // incrementing 
        }
        buffOb->nextObject = nextObject; //  ... and switching nextObject.
    }
}

Object::Object(float spriteX,float spriteY,Hitbox hbx,Texture& t,Font& f,std::string text,int chS)
:Sprite::Sprite(),
Text::Text(),
textPos(TextPosition::Center),
initialDrag(0,0),
dragged(false),
hitbox(hbx),
draggingAvailability(false),
collisionAvailability(true),
z(10000)
{   
    /*
        The frequentliest used constuctor.
        Sets all allow flags to false and the Text parameters. Saves pointers to font and texture.
        Adds Object to the list. Adds the id name. Checks if the hitbox is defined.
    */
    Sprite::setTexture(t);
    Text::setFont(f);
    #pragma warning(suppress : 4996) Text::setColor(Color(255,255,255));
    Text::setCharacterSize(chS);
    Text::setLineSpacing(0);
    Sprite::setPosition(spriteX,spriteY);
    Text::setPosition(spriteX,spriteY);

    // If we want to create a default hitbox we send Rectangle shape and the parameters of the Sprite.
    if( hbx.type == 3 ){
        ///TODO change to pointer.
        hitbox = Hitbox(Hitbox::Shape::Rectangle, 0, 0, Sprite::getGlobalBounds().width, Sprite::getGlobalBounds().height);
    }
    else if( hbx.type == 4 ){
        ///TODO change to pointer.
        hitbox = Hitbox(Hitbox::Shape::Circle, 0, 0, Sprite::getGlobalBounds().width/2);
    }
    // The most important line. Adds the Object to the list.
    addToList();
    name = "object" + std::to_string(id);
    setString(text);
    // Incrementing static variable to identify each Object.
    id++;
}
void Object::setPosition(float x, float y){
    /*
        @returns void 
        Sets the position given by parameters both Text and Sprite.
    */
    Text::setPosition(x,y);
    Sprite::setPosition(x,y);
}
void Object::setRotation( float angle ){
    /*
        @returns void 
        Sets the Rotation given by parameter to Hitbox, Text and Sprite.
    */
    Text::setRotation(angle);
    Sprite::setRotation(angle);
    hitbox.rotate( angle - Sprite::getRotation() );
}
void Object::setScale( float factorX, float factorY ){
    /*
        @returns void 
        Sets the Scale given by parameters to Hitbox, Text and Sprite.
    */
    Text::setScale( factorX, factorY );
    Sprite::setScale( factorX, factorY );
    // Chcecking if the factors are not equal 0.
    Vector2f newScale = Sprite::getScale();
    if( newScale.x != 0 ){
        newScale.x = factorX/newScale.x;
    }
    else
    {
        newScale.x = 0;
    }
    
    if( newScale.y != 0 ){
        newScale.y = factorY/newScale.y;
    }
    else
    {
        newScale.y = 0;
    }    
    hitbox.scale( newScale.x,newScale.y );
}
void Object::setOrigin(float x, float y){
    /*
        @returns void 
        Sets the position of origin point by values given by parameters of Hitbox, Text and Sprite.
    */
    hitbox.move( - x + Sprite::getOrigin().x, - y + Sprite::getOrigin().y );
    Text::setOrigin(x,y);
    Sprite::setOrigin(x,y);
}
void Object::setOrigin( Vector2f v ){
    /*
        @returns void 
        Sets the position of origin point by values given by parameters of Hitbox, Text and Sprite.
    */
    setOrigin( v.x, v.y );
}
void Object::move(float x, float y){
    /*
        @returns void 
        Moves both Text and Sprite by distance given by parameters.
    */
    Text::move(x,y);
    Sprite::move(x,y);
}
void Object::scale( float factorX, float factorY ){
    /*
        @returns void 
        Scales the Hitbox, Text and Sprite by factors given by parameters.
    */
    hitbox.scale( factorX, factorY );
    Sprite::scale( factorX, factorY );
    Text::scale( factorX, factorY );
    setTextPosition(textPos);
}
void Object::rotate( float angle ){
    /*
        @returns void 
        Rotates the Hitbox, and Sprite by angle given by parameter.
    */
    hitbox.rotate( angle );
    Sprite::rotate( angle );
    Text::rotate( angle );    
    setTextPosition(textPos);
}
 void Object::setString(std::string text){
     /*
        @returns void 
        Sets the Text to the text given by parameter and formats the text position to the one saved in textPos.
    */
     Text::setString(text);
     setTextPosition(textPos);
 }
 void Object::onDrag(const Event &event){
     /*
        @returns void 
        Deafault function checking if this Object is being dragged.
        The Object is picked up when is cklicked by left button and dropped when released.
    */
    onDrag(event,onClick(event, Mouse::Left), onRelease(event) );
}
void Object::onDrag(const Event &event, bool onPickUp, bool onDrop ){
     /*
        @returns void 
        Standard function checking if this Object is being dragged.
        The Object is picked up when onPickUp is true and dropped when onDrop os true.       
    */
    //Time t = dragTimer.restart();//TODO
    if(dragged && onDrop){
        //velocity.x = (event.mouseMove.x-initialDrag.x)/t.asSeconds();
        //velocity.y = (event.mouseMove.y-initialDrag.y)/t.asSeconds();
    }
    
    if(onPickUp){ // Chcecking if the Object has been picked up.
        // Then dragging starts. So we save the initial mouse position and pick the Object up on the top level of the view.
        dragged = true;
        initialDrag.x = event.mouseButton.x;
        initialDrag.y = event.mouseButton.y;
        setZ(30000);
    }
    else if(dragged){ // Chcecking if the Object is being dragged.
        if(onDrop){ // Chcecking if the Object has been dropped.
            // Then dragging ends and the Object goes back on its level.
            dragged = false;
            setZ(10000);
        }
        else{
            move(event.mouseMove.x-initialDrag.x,event.mouseMove.y-initialDrag.y);    /// Displacement between current mouse position and object's initial position.
            initialDrag.x = event.mouseMove.x; /// Saving object's initial position.
            initialDrag.y = event.mouseMove.y; /// Saving object's initial position.
        }
    }
}
void Object::setTextPosition(int mode){
    /*
        @returns void 
        Formats the text position relatively to the Sprite.
        The place when the text has to be placed is defined by the parameter ( see enumaration ).     
    */
    textPos = mode;
    switch(mode){
    case TextPosition::Center:
        Vector2f p1(Sprite::getLocalBounds().left + Sprite::getLocalBounds().width/2 - Text::getLocalBounds().width/2,
                      Sprite::getLocalBounds().top+ Sprite::getLocalBounds().height/2 -  Text::getLocalBounds().height/2-getCharacterSize()*0.28);
        p1 = Sprite::getTransform().transformPoint(p1);
        Text::setPosition(p1);
    break;//-Text::getLocalBounds().width/2-Text::getLocalBounds().height/2
    }
}
void Object::setZ(int _z){
    /*
        @returns void 
        Changes the "z" value and puts this Object in the correct place in the list so that the "z" values were ordered ascending.    
    */
    if( z != _z){
        removeFromList();
        z = _z;
        addToList();
    }
}
bool Object::checkCollision(Object* secondObj){
    /*
        @returns true when collision between this and the Object given by parameter has occured and false when not.
        The function changes absolute position of the objects to relative position where the (0,0) point is
        in the second Object's Hitbox translation point.
    */
    return hitbox.checkCollision(   
        secondObj -> hitbox, 
        Sprite::getPosition().x - secondObj -> Sprite::getPosition().x, 
        Sprite::getPosition().y - secondObj -> Sprite::getPosition().y 
    );
}
bool Object::isWithinHitbox(float x, float y){
    /*
        @returns true when the point given by parameters is inside this Object and false when not.
        The function changes absolute position of the object and the point to relative position where the (0,0) point is
        in this Object's Hitbox translation point.
    */
    return hitbox.isWithinHitbox(x - Sprite::getGlobalBounds().left,y - Sprite::getGlobalBounds().top);
}
bool Object::onClick(const Event &event, Mouse::Button b){
    /*
        @returns true when the Object has been clicked by the button given by parameter and false when not.
    */
    if(event.type == Event::MouseButtonPressed && event.mouseButton.button == b &&
       isWithinHitbox(event.mouseButton.x, event.mouseButton.y)){
            return true;
       }
       return false;
}
bool Object::onPress(const Event &event, Keyboard::Key k){
    /*
        @returns true when the Object has been clicked by the key button given by parameter and false when not.
    */
    if(event.type == Event::KeyPressed && event.key.code == k && 
        isWithinHitbox(event.mouseButton.x, event.mouseButton.y) ){
            return true;
       }
       return false;
}
bool Object::onRelease(const Event &event, Mouse::Button b ){
    /*
        @returns true when the button given by parameter has been released and false when not.
    */
    if( event.type == Event::MouseButtonReleased && event.mouseButton.button == b ){
            return true;
       }
       return false;
}
bool Object::onRelease(const Event &event, Keyboard::Key k ){
    /*
        @returns true when the key button given by parameter has been released and false when not.
    */
    if( event.type == Event::KeyReleased && event.key.code == k ){
            return true;
       }
       return false;
}
bool Object::onDeClick(const Event &event){
    /*
        @returns true when the button given parameter has been cklicked but not on this Object and false when it's diffrent.
    */
    if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left &&
       !isWithinHitbox(event.mouseButton.x, event.mouseButton.y)){
            return true;
       }
       return false;
}
bool Object::onHover(const Event &event){
    /*
        @returns true when the mouse is placed over the Object and false when not.
    */
    if(event.type == Event::MouseMoved &&
       isWithinHitbox(event.mouseMove.x, event.mouseMove.y)){
            return true;
        }
        return false;
}
Vector2f Object::getGlobalCenter(){
    /*
        @return the center of the Object in the global coordinate system
    */
   return Vector2f( Sprite::getGlobalBounds().left + Sprite::getGlobalBounds().width/2, Sprite::getGlobalBounds().top + Sprite::getGlobalBounds().height/2 );
}

// Access functions
void Object::setDraggingAvailability(bool f1){
    draggingAvailability = f1;
}
bool Object::getDraggingAvailability(){
    return draggingAvailability;
}

void Object::setCollisionAvailability(bool f1){
    collisionAvailability = f1;
}
bool Object::getCollisionAvailability(){
    return collisionAvailability;
}

Object* Object::getNextObject(){    
    /*
        @returns pointer to the next Object.
    */
    return nextObject;
}
std::string Object::getName(){   
    /*
        @returns the name of the Object.
    */
    return name;
}
Object* Object::getFirstObject(){
    /*
        @returns pointer to the first Object in the list.
    */
   return firstObject;
}

// PhysicObject polyphormial functions
void Object::setMovingAvailability(bool f1){}
bool Object::getMovingAvailability(){
    return false;
}

void Object::setDynamicsAvailability(bool f1){}
bool Object::getDynamicsAvailability(){
    return false;
}

void Object::setVelocity(Vector2f v){}
Vector2f Object::getVelocity() { return Vector2f(0, 0); }
void Object::checkMove(){}

void Object::checkDynamics(float frictionRatio){}

// InputText polyphormial functions
void Object::checkInputText(const Event &event){}


Object::~Object(){
    //Default destructor.
    removeFromList();
}

 





