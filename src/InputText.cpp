#include <SFML/Graphics.hpp>
#include "InputText.h"
#include "Hitbox.h"
#include <string>
#include <iostream>

using namespace sf;

InputText::InputText(  int mTS, float spriteX,float spriteY,Hitbox sh,Texture& t,Font& f,std::string text,int chS)
:Object::Object(spriteX,spriteY,sh,t,f,text,chS),
writtenText(text),
focused(false),
maxTextSize(mTS)
{
    /*
        Standard constructor.
        Erases text if is longer than the max size.
    */
    writtenText.reserve(maxTextSize);
    while(text.length() > maxTextSize){
        text.erase(text.length()-1,1);
    }
    Text::setString(writtenText);
    setTextPosition(TextPosition::Center);
}
void InputText::addLetter(char letter){
    /*
        @returns void,
        Adds letter given by parameter.
        If the letter is a backspace it pops the string.
    */
    if( letter == 8 ){ /// 8 - id of the Backspace key in the ASCI coding.
        deleteLetter();
    }
    else{
        if(writtenText.length() < maxTextSize){
            writtenText.push_back(letter);
            setString(writtenText);
        } 
    } 
}
void InputText::deleteLetter(){
    /*
        @returns void.
        Deletes the last letter.
    */
    if(writtenText.length() > 0){
        writtenText.erase(writtenText.length()-1,1);
        setString(writtenText);
    }
}
void InputText::setString(std::string n){
    /*
        @returns void,
        Resets the text to writtenText.
    */
    writtenText = n;
    Object::setString(n);
}
void InputText::checkInputText(const Event &event){
    /*
        @returns void.
        Checks if user wants to input a text.
        Calls standars function where the boz gets focused on left click and loses focus on left click outside the box.
    */
    checkInputText( event, Object::onClick(event, Mouse::Left), Object::onDeClick(event) );
}
void InputText::checkInputText(const Event &event, bool onFocus, bool onDeFocus){
    /*
        @returns void.
        Checks if user wants to input a text.
        The box gets focused or loses focus depending from the parameters.
    */
    bool clicked = false;
    if(!focused){
        if(onFocus){
            focused = true;
        }
    }
    else{
        if(onDeFocus){
            focused = false;
        }
        else if( event.type == event.TextEntered ){
            addLetter(event.text.unicode);
        }       
    }
}
InputText::~InputText(){
    /*
        Default destructor.
    */
}