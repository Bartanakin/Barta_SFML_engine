#ifndef InputText_h
#define InputText_h

#include <SFML/Graphics.hpp>
#include "Object.h"

using namespace sf;

class InputText :public Object
{
    /*
        Class which handles adding new text by the user.
    */
    // The text written by user.  
    std::string writtenText;
    // If true the text is being collecting from keyboard.
    bool focused;
    // The number of character able to write.
    int maxTextSize;
public:
    // Standard constructor.
    InputText(int _maxTextSize,float xPosition,float yPosition,Hitbox _hitbox,Texture& _texture,Font& _font,std::string writtenText="",int letterSize= 20);
    // Text contolling functions.
    void addLetter(char);
    void deleteLetter();
    // Functions reffering to inherited class.
    void setString(std::string);
    // Event functions.
    virtual void checkInputText(const Event&);
    virtual void checkInputText(const Event&, bool onFocus, bool onDeFocus);
    // Default destructor.
    ~InputText();
};

#endif
