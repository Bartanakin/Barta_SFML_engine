#include "game.h"

Game::Game()
    :window(nullptr),
    //videoMode(VideoMode::getDesktopMode().height,VideoMode::getDesktopMode().width),
    videoMode(0,0)
{
    // Saving the window size
    videoMode.width = VideoMode::getDesktopMode().width;
    videoMode.height = VideoMode::getDesktopMode().height;
    // window allocated dynamicly
    window = new RenderWindow( videoMode, "Test Silnika", Style::Fullscreen);
    // Setting the frame rate to decrease CPU and GPU 
    window->setFramerateLimit(60); 
    // Loading resources
    loadFromFiles();
    // Creating starting Objects
    initObjects();   
}
void Game::loadFromFiles(){
    /*
        @returns void
        Loads resources from files.
        If a file doesn't exist an exeption is thrown and aplication ends.
    */
    try
    {
        if (!f_arial.loadFromFile("fonts/arial.ttf"))
        {
            throw std::runtime_error("Font not found: \"fonts/arial.ttf\"");
        }
        if (!t_redBall.loadFromFile("images/redBall.png"))
        {
            throw std::runtime_error("Sprite not found: \"images/redBall.png\"");
        }
        if (!t_redButton.loadFromFile("images/redButton.png"))
        {
            throw std::runtime_error("Sprite not found: \"images/redButton.png\"");
        }
        if (!t_greenButton.loadFromFile("images/greenButton.png"))
        {
            throw std::runtime_error("Sprite not found: \"images/greenButton.png\"");
        }
        if (!t_yellowTriangle.loadFromFile("images/yellowTriangle.png"))
        {
            throw std::runtime_error("Sprite not found: \"images/yellowTriangle.png\"");
        }
        if (!hbx_yellowTriangle.loadFromFile("hitbox/yellowTriangleHBX.txt"))
        {
            throw std::runtime_error("Hitbox not found: \"hitbox/yellowTriangleHBX.txt\"");
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << std::endl
                  << e.what();
        window->close();
    }
}
void Game::initObjects(){
    /*
        @returns void
        Initializes all Objects created on the beginning of the game.
    */
    exitButton = new Object(
        videoMode.width - t_redButton.getSize().x,
        videoMode.height - t_redButton.getSize().y,
        Hitbox(Hitbox::Shape::DefaultRectangle),
        t_redButton,
        f_arial,
        "exit");
    button1 = new PhisicObject(
        700.f,
        700.f,
        Hitbox(Hitbox::Shape::DefaultCircle),
        t_redBall,
        Mass(1,Vector2f(20.5f,20.5f)),
        f_arial,
        "button1");
        button1 -> setMovingAvailability(true);
        //button1->setDraggingAvailability(true);
    button2 = new PhisicObject(
        700.f,
        900.f,
        Hitbox(Hitbox::Shape::DefaultRectangle),
        t_redButton,
        Mass(1,Vector2f(65.5f,51.5f)),
        f_arial,
        "button2");
    //button2->setDraggingAvailability(true);
        /*
    button3 = new Object(
        700.f,
        700.f,
        hbx_yellowTriangle,
        t_yellowTriangle,
        f_arial,
        "button3");*/
}
bool Game::getWindowIsOpen()
{
    /*
        @returns true if the window is open if not returns false
    */
    return window -> isOpen();
}
void Game::renderFrame()
{
    /*
        @returns void
        Rendering the frame.
    */
    window->clear(); // clearing the previous frame

    if (Object::getFirstObject() != nullptr) // Don't look for Object when the list is empty.
    {
        Object *buffObj = Object::getFirstObject(); // iterator
        do
        {
            // Checking if Object has information about a Texture and a Font.
            if (buffObj->getTexture() != nullptr)
            {
                window->draw((Sprite)*buffObj); // First the Sprite is drown.
            }
            if (buffObj->getFont() != nullptr)
            {
                window->draw((Text)*buffObj); // Secondly, the Text.
            }
            buffObj = buffObj->getNextObject(); // incrementing
        } while (buffObj != Object::getFirstObject());
    }

    /*
        Notes:
        All Objects should be ordered in the list by the "z" values ascending.
        If two Objects have the same value "z" then there is undefined which will be drawn first.
    */

    window->display();
}
void Game::checkEvents()
{
    /*
        @returns void
        Events handling.
    */
    while (window->pollEvent(event)) // Checking if an event was captured.
    {   
        // Closing the window with "X" in the right top corner.
        // When window is in full screen mode it doesn't have effect .
        if (event.type == Event::Closed)
        {
            window->close(); 
        }
        // Closing the window with a button in the right bottom corner.
        if (exitButton->onClick(event, Mouse::Left))
        {
            window->close();
        }
        // This is place for game logic events.

        if (Object::getFirstObject() != nullptr) // Don't look for Objects when the list is empty.
        {
            Object *buffObj = Object::getFirstObject(); // iterator
            do
            {
                // Loop searches for Objects that can be dragged or text can be wriiten on them.
                if (buffObj->getDraggingAvailability())
                {
                    buffObj->onDrag(event);
                }
                buffObj->checkInputText(event);

                buffObj = buffObj->getNextObject(); // incrementing
            } while (buffObj != Object::getFirstObject());
        }
    }
}
void Game::update()
{
    /*
        @returns void
        Game logic handling.
    */
    if(!(button1 -> getVelocity() == Vector2f(0,0))){
        std::cout << button1 -> Sprite::getPosition().x << " " << button1 -> Sprite::getPosition().y << std::endl;
    }
    if (Object::getFirstObject() != nullptr) // Don't look for Objects when the list is empty.
    {
        Object *buffObj = Object::getFirstObject(); // iterator of the outer loop
        do
        {

            // Collision handling. // TOTEST
            Object *buffObj2 = buffObj->getNextObject(); // iterator of the inner loop
            if (buffObj->getCollisionAvailability())     // Checking if collisions are allowed.
            {
                do
                {
                    if (buffObj2->getCollisionAvailability()) // Checking if collisions are allowed to the second Object.
                    {
                        
                        if (buffObj->checkCollision(buffObj2))
                        {
                            buffObj -> setVelocity(Vector2f(0,0));
                            buffObj2 -> setVelocity(Vector2f(0,0));
                        }
                        
                    }

                    buffObj2 = buffObj2->getNextObject(); // incrementing inner loop
                } while (buffObj2 != buffObj);
            }
            // Loop checks if any physic events or collisions occur.

            if (buffObj->getMovingAvailability()) // Checking if move colocated with velocity is allowed for this Object.
            {
                buffObj->checkMove();
            }

            if (buffObj->getDynamicsAvailability()) // Checking if dynamic systeam is allowed for this Object.
            {
                buffObj->checkDynamics(3);
            }

            ///////////

            buffObj = buffObj->getNextObject(); // incrementing outer loop
        } while (buffObj != Object::getFirstObject());
    }
}
Game::~Game(){
    delete exitButton;
    delete button1;
    delete button2;
    //delete button3;
    delete window;
}