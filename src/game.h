#ifndef Game_h
#define Game_h

//#include <SFML/Graphics.hpp>
#include "InputText.h"
#include <stdexcept>
#include "PhisicObject.h"

/* 
    Wrraper class.
*/
class Game{
    // Pointer to the game window
    RenderWindow* window;
    // videoMode contains information about windowSize
    VideoMode videoMode;
    // Event's class member
    Event event;
    // Textures, Fonts and Hitboxes
    Font f_arial;
    Texture t_redBall;
    Texture t_redButton;
    Texture t_greenButton;
    Texture t_yellowTriangle;
    Hitbox hbx_yellowTriangle;
    
    // Objects
    Object* exitButton;
    PhisicObject* button1;
    PhisicObject* button2;
    PhisicObject* button3;

    // Initialization

    // Textures, Fonts and Hitboxes.
    void loadFromFiles();
    // Objects
    void initObjects();

public:
    // Constructor and destructor
    Game();
    ~Game();

    // Functions 
    bool getWindowIsOpen();
    void checkEvents();
    void update();
    void renderFrame();
};


#endif
