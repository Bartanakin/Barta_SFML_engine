#ifndef Family_h
#define Family_h

#include"Object.h"

class Family :public Transformable{
    /*
        Virtual class that makes iot easier to cope with sets of Objects.
    */
private:

    // Number of objects in the family.
    int numberOfObjects;
    // The objects.
    std::vector<Object*> objects;
    // The origin point of th family.
    Vector2f translation;

public:
    // The name added to every object in the family.
    const std::string name;

    // Standard constructor.
    Family(std::string _name);
    // Deafault destructor.
    ~Family();
    // Object control functions.
    void move(float x, float y);
    void setPosition(float x, float y);
    void scale(float xFactor, float yFactor);


    // Transformable class functions.

};

#endif