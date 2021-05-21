
#include <fstream>
#include "Hitbox.h"
#include <cmath>
#include <iostream>

using namespace sf;
Hitbox::Hitbox(int t, float xt, float yt, float w_or_r, float h)
:type(t),
top(xt),
left(yt),
width(w_or_r),
height(h),
radius(0),
lengthOfSource(4)
{
    /* 
        Standard constructor.
        If the type is Circle sets length of source to 0.
        If it is a rectangle creates points.
    */
    if(type == Shape::Circle){
        lengthOfSource = 0;
        radius = w_or_r;
        width = w_or_r*2;
        height = w_or_r*2;
    }
    else{        
        // Sets points coordinates.
        points.push_back( Vector2f(xt, yt) ); 
        points.push_back( Vector2f(xt + w_or_r, yt) );
        points.push_back( Vector2f(xt + w_or_r, yt + h) );
        points.push_back( Vector2f(xt, yt + h) );
    }
}
void Hitbox::writeLines(){
    /*
        @returns void
        Function left for debugging.
    */
    
    for( int i = 0; i < lengthOfSource; i++ ){
        std::cout << i << " ";
        std::cout << points[i].x << " ";
        std::cout << points[i].y << std::endl;
    }
}
void Hitbox::writeRect(){
    /*
        @returns void
        Function left for debugging.
    */
    
        std::cout  << "Rect:  ";
        std::cout << left << " ";
        std::cout << top << " ";
        std::cout << width << " ";
        std::cout << height << std::endl;
}
Vector2f Hitbox::getCenter(){
    /*
        @returns the coordinates of the middle of the hitbox.
    */
   return Vector2f(left + width/2, top + height/2 );
}
void Hitbox::setTransform( Transform& transform ){
    /*
        @returns void.
        Executes the transfrom command.
        Resets the global rectangle.
    */
    FloatRect r1 = transform.transformRect( FloatRect(top,left,width,height) );
    Transform t2;
    t2.translate( left - r1.left, top - r1.top);
    for( int i = 0; i < lengthOfSource; i++ ){
        points[i] = transform.transformPoint(points[i]);
        points[i] = t2.transformPoint(points[i]);
    }
    width = r1.width; 
    height = r1.height;
}
void Hitbox::move(float x, float y){
    /*
        @returns void.
        Moves the Hitbox by values given by parameters.
    */
    Transform transform;
    transform.translate(x,y);
    setTransform(transform);
    
}
void Hitbox::scale( float factorX, float factorY ){
    /*
        @returns void.
        Sets scale of the Hitbox by values given by parameters.
    */
    if( type == Circle ){
        factorY = factorX;
    }
    Transform transform;
    transform.scale(factorX,factorY);
    setTransform(transform);
    radius = radius*factorX;
}
void Hitbox::rotate( float angle ){
    /*
        @returns void.
        Rotates the Hitbox by angle given by parameter.
    */ 
    
    Transform transform;
    transform.rotate( angle );
    setTransform(transform);
    // If we rotate an parallel rectangle then we have to change its type to BezierCurves.
    if( type == Rectangle && static_cast<int>(angle) % 90 != 0 ){
        type = BezierCurves;
    }
}
bool Hitbox::loadFromFile(std::string path){
    /*
        @returns true if the hitbox file exists and false if not.
        Loads points' coordinates from source file.
        It saves them in objects Vector class.
    */ 
    std::ifstream source(path); 
    if(source){ //TODO // 
        // Cleares default lines.
        for( int i = 0; i < lengthOfSource; i++ ){
            points.pop_back();
        }
        // First loads the size of hitbox.
        int _lengthOfSource;
        source >> _lengthOfSource;
        lengthOfSource = _lengthOfSource;
        // Looking for the nearest coordinates and the furthest for optimalisation of collision system.
        float maxx;
        float minx;
        float maxy;
        float miny;
        // Saving first point .
        float firstPointX;
        float firstPointY;   
        source >> firstPointX;
        maxx = firstPointX;
        minx = firstPointX;
        source >> firstPointY;
        maxy = firstPointY;
        miny = firstPointY;
        points.push_back(Vector2f(firstPointX,firstPointY));
        // Buffors
        float c1;
        float c2;
        for( int i = 1; i < lengthOfSource; i++ ){
            source >> c1;
            source >> c2;
            points.push_back(Vector2f(c1,c2));

            // Checking if values are extremal.
            if( c1 > maxx ){
                maxx = c1;
            }
            else if( c1 < minx ){
                minx = c1;
            }
            if( c2 > maxy ){
                maxy = c2;
            }
            else if( c2 < miny ){
                miny = c2;
            }
            
        }
        // Saving the extremals.
        top = minx;
        left = miny;
        width = maxx - minx;
        height = maxy - miny;
        // Closing stream buffors.
        source.close();
        return true;
    }
    else{
        return false;
    }

}
bool Hitbox::isWithinHitbox(float x, float y){
    /*
        @returns true if the point given by parameters is inside the hitbox and false if not.
        Switches between types of Hitbox.
    */ 
    switch(type){
    
    case Shape::BezierCurves: /// Bezier's curves

        return isWithinBezierCurves(x,y);

    break;
    case Shape::Rectangle: /// Rectangle
        
        return isWithinRectangle(x,y);

    case Shape::Circle: /// Circle and Circle
        
        return isWithinCircle(x,y);

    break;

    }
    return false;
}
bool Hitbox::isWithinRectangle(float x, float y){
    /*
        @returns true if the point given by parameters is inside the hitbox and false if not.
        Can be proccessed if this Hitbox type is Rectangle or BezierCurves.
    */
    //std::cout << x   << " " << y << std::endl;
    if( x >= top &&
        x <= top + width &&
        y >= left &&
        y <= left + height){
        return true;
    }
    else{
        return false;
    }
}
bool Hitbox::isWithinCircle(float x, float y){
    /*
        @returns true if the point given by parameters is inside the hitbox and false if not.
        Can be proccessed if this Hitbox type is Circle.
    */
    Vector2f middle = getCenter();
    if( pow((x-middle.x),2)+pow((y-middle.y),2)<=radius*radius){
        return true;
    }
    else{
        return false;
    }
}
bool Hitbox::isWithinBezierCurves(float x, float y){
    /*
        @returns true if the point given by parameters is inside the hitbox and false if not.
        Can be proccessed if this Hitbox type is BezierCurves.
    */
    
    if( isWithinRectangle(x,y) ){ // To optimize the game first checks if the point is inside the Rectangle.
        /*
            Creates a line that one end is in the point given by parameters 
            and the second one is...
        */
        Line firstLine;
        if( x != top && y != left ){
            // .. in the left top corner...
            firstLine = Line(Vector2f(x,y),Vector2f(top,left));                    
        }
        else{
            // ... or in the right down corner.
            firstLine = Line(Vector2f(top + width, left+ height), Vector2f(x,y));
        }
        // Note: the is little chance the algoritm doesn't work when the created line crosses a point //TODO
        // in which one of the Lines in Hitbox ends.
        int cnt = 0; // Counter of crossings.
        for( int i = 0; i < lengthOfSource - 1; i++ ){
            Line l( points[i], points[ i + 1 ] );
            if( l.checkCrossing(firstLine,0,0)){
                cnt++;
             }
        }
        Line l(points[0],points[ lengthOfSource - 1 ] );
        if( l.checkCrossing(firstLine,0,0) ){
            cnt++;
        }
        // If the Line crosses Hitbox lines even times then the point is outside the Hitbox.
        // Else, inside the Hitbox.
        if( cnt % 2 == 1 ){
            return true;
        }
    }
    return false;
}
bool Hitbox::checkCollision( Hitbox& secondHitbox, float xd, float yd){
    /*
        @returns true if this Hitbox and the second given by parameter translated by vector have joint ponits and false if not.
        Switches between types of Hitbox.
    */
    if( type == Shape::Rectangle && secondHitbox.type == Shape::Rectangle ){ // 2x Rectangle
        return checkCollRectRect( secondHitbox, xd, yd );
    }
    else if( type == Shape::Rectangle || secondHitbox.type == Shape::Rectangle ){ // second Rectangle
        if( type == Shape::Circle ){ // first Circle
            return checkCollBeziCir( secondHitbox, xd, yd );
        }
        else if( type == Shape::BezierCurves ){ // first BezierCurves
            return checkCollBeziBezi( secondHitbox, xd, yd );
        }
    }
    if( type == Shape::Circle && secondHitbox.type == Shape::Circle ){   // 2x Circle 
        return checkCollCirCir( secondHitbox, xd, yd );
    }
    else if( type == Shape::Circle || secondHitbox.type == Shape::Circle ){  // second Circle        
        return checkCollBeziCir( secondHitbox, xd, yd );
    }
    if( type == Shape::BezierCurves && secondHitbox.type == Shape::BezierCurves ){   // 2x BezierCurves 
        return checkCollBeziBezi( secondHitbox, xd, yd );
    }
    else if( type == Shape::BezierCurves || secondHitbox.type == Shape::BezierCurves ){  // second BezierCurves
        
        if( type == Shape::Rectangle ){ // first Rectangle
            return checkCollBeziBezi( secondHitbox, xd, yd );
        }
        else if( type == Shape::Circle ){ // first Circle
            return checkCollBeziCir( secondHitbox, xd, yd );
        }
    }
    return false;
}
bool Hitbox::checkCollRectRect( Hitbox& secondHitbox, float xd, float yd){
    /*
        @returns true if this Hitbox and the second given by parameter translated by vector have joint ponits and false if not.
        Can be proccessed for two Rectanlge or two BezierCurves types.
    */

    if( secondHitbox.top <= top + width + xd &&
        secondHitbox.top + secondHitbox.width >= top + xd &&
        secondHitbox.left <= left + height + yd &&
        secondHitbox.left + secondHitbox.height >= left + yd ){
        return true;
    }
    else{
        return false;
    }
}
bool Hitbox::checkCircleAndLineCrossing( Line& l ){
    /*
        @returns true if this Hitbox and the line given by parameter have joint ponits and false if not.
        Can be proccessed for Circle type.
    */
    Vector2f middle = getCenter();
    float A = l.A();
    float B = l.B();
    float C = l.C();
    ma::Solutions sx;
    ma::Solutions sy;
    if( A == 0 && B == 0 ){
        return false;
    }
    else if( A == 0 ){
        sx = ma::quadratic(1, -2*middle.x, middle.x*middle.x + C*C/( B*B ) + 2*C*middle.y/B + middle.y*middle.y - radius*radius );
    }
    else if( B == 0 ){
        sy = ma::quadratic(1, -2*middle.y, middle.y*middle.y + C*C/( A*A ) + 2*C*middle.x/A + middle.x*middle.x - radius*radius );
    }
    else{
        sx = ma::quadratic( 1 + ( A*A )/( B*B ), 2*( -middle.x + (A*C)/( B*B ) + (middle.y*A)/B ), (C*C)/( B*B ) + 2*(middle.y*C)/B + middle.y*middle.y + middle.x*middle.x - radius*radius ); 
    }
    if( sx.solutionExist && sx.numberOfSolutions != 0){
        for( int i = 0; i < sx.numberOfSolutions; i++ ){             
            if( sx.x[i] >= l.v1.x && sx.x[i] <= l.v2.x ){
                return true;
            } 
        }
    }
    if( sy.solutionExist && sy.numberOfSolutions != 0 ){  
        for( int i = 0; i < sy.numberOfSolutions; i++ ){
            if( (sy.x[i] >= l.v1.y && sy.x[i] <= l.v2.y) || (sy.x[i] <= l.v1.y && sy.x[i] >= l.v2.y)){
                return true;
            } 
        }
    }
    return false;
}
bool Hitbox::checkCollCirCir( Hitbox& secondHitbox, float xd, float yd){
    /*
        @returns true if this Hitbox and the second given by parameter translated by vector have joint ponits and false if not.
        Can be proccessed for two Circle types.
    */
    
    Vector2f middle1 = getCenter();
    Vector2f middle2 = secondHitbox.getCenter();
    if( ma::distanceOfTooPoints(middle1.x,middle1.y,middle2.x,middle2.y) <= radius + secondHitbox.radius ){
        return true;
    }
    return false;

}
bool Hitbox::checkCollBeziCir( Hitbox& secondHitbox, float xd, float yd){
    /*
        @returns true if this Hitbox and the second given by parameter translated by vector have joint ponits and false if not.
        Can be proccessed for one Circle and one BezierCurves type.
    */
    if( ( type == Rectangle || type == BezierCurves ) && secondHitbox.type == Circle ){
        for(int i = 0; i < lengthOfSource - 1; i++ ){
            // Chcecking if the Circle crosses any lines of this Hitbox.
            Line _line( points[i] + Vector2f(xd,yd), points[i + 1] + Vector2f(xd,yd) );
            if( secondHitbox.checkCircleAndLineCrossing( _line ) ){
                return true;
            }
        }
        Line _line( points[0] + Vector2f(xd,yd), points[lengthOfSource - 1] + Vector2f(xd,yd) );
        // Checking if the middle of the Circle is inside this Hitbox. 
        if( type == Rectangle ){
            if( isWithinRectangle(secondHitbox.top + secondHitbox.width/2 - xd, secondHitbox.left + secondHitbox.width/2 - yd)){
                return true;
            }
        }
        else{
            if( isWithinBezierCurves(secondHitbox.top + secondHitbox.width/2 - xd, secondHitbox.left + secondHitbox.width/2 - yd)){
                return true;
            }
        }
        
    }
    else if( type == Circle && ( secondHitbox.type == Rectangle || secondHitbox.type == BezierCurves ) ){
        // If this Hitbox is Circle type then inverse sequence and go back to whis function.
        return secondHitbox.checkCollBeziCir(*this,-xd,-yd);
    }
    return false;
}
bool Hitbox::checkCollBeziBezi(Hitbox &secondHitbox, float xd, float yd)
{
    /*
        @returns true if this Hitbox and the second given by parameter translated by vector have joint ponits and false if not.
        Can be proccessed for two BezierCurves types.
    */
    // First checks if the Rectangles colide.
    if (checkCollRectRect(secondHitbox, xd, yd))
    {
        // If any line in the first Hitbox crosses with a line from the second Hitbox then they colide.
        for (int i = 0; i < lengthOfSource - 1; i++)
        {
            Line l1( points[i], points[i+1] );
            for (int j = 0; j < secondHitbox.lengthOfSource - 1; j++)
            {
                Line l2( secondHitbox.points[j] - Vector2f(xd,yd), secondHitbox.points[j + 1] - Vector2f(xd,yd));
                if (l1.checkCrossing(l2) )
                {
                    return true;
                }
            }
            Line l2( secondHitbox.points[0] - Vector2f(xd,yd), secondHitbox.points[secondHitbox.lengthOfSource - 1] - Vector2f(xd,yd));
            if(l1.checkCrossing(l2) ){
                return true;
            }
        }
        Line l1( points[0], points[lengthOfSource - 1] );
            for (int j = 0; j < secondHitbox.lengthOfSource - 1; j++)
            {
                Line l2( secondHitbox.points[j] - Vector2f(xd,yd), secondHitbox.points[j + 1] - Vector2f(xd,yd));
                if (l1.checkCrossing(l2) )
                {
                    return true;
                }
            }
            Line l2( secondHitbox.points[0] - Vector2f(xd,yd), secondHitbox.points[secondHitbox.lengthOfSource - 1] - Vector2f(xd,yd));
            if(l1.checkCrossing(l2) ){
                return true;
            }
        // If no two lines cross but the first point of one of the Hitboxes is iside the second one then they colide.
        if (secondHitbox.isWithinBezierCurves(points[0].x + xd, points[0].y + yd))
        {
            return true;
        }
        if (isWithinBezierCurves(secondHitbox.points[0].x - xd, secondHitbox.points[0].y - yd))
        {
            return true;
        }
    }
    return false;
}
Rect<float> Hitbox::getRect(){
    /*
        @returns the Rectangle which is designated by the extremum points.
    */
    if( type == Shape::BezierCurves ){
        float _left = points[0].x;
        float _top = points[0].y;
        float _right = points[0].x;
        float _bottom = points[0].y;
        for(int i = 1; i < lengthOfSource; i++ ){
            if( points[i].x < _left){
                _left = points[i].x;
            }
            else if ( _right < points[i].x ){
                _right = points[i].x;
            }
            
            if( points[i].y < _top){
                _top = points[i].y;
            }
            else if ( _bottom < points[i].y ){
                _bottom = points[i].y;
            }
        }
        return Rect<float>(_left,_top,_right - _left, _bottom - _top );
    }
    else{
        return Rect<float>(left,top,width, height );
    }
}
Hitbox::~Hitbox(){
    /*
        Default destructor.
    */
}