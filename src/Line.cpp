#include"Line.h"
#include <iostream>

using namespace std;

Line::Line(){}

Line::Line( Vector2f _v1, Vector2f _v2){
    if(_v1.x > _v2.x){
        v1.x = _v2.x;
        v2.x = _v1.x;
        v1.y = _v2.y;
        v2.y = _v1.y;
    }
    else{
        v1.x = _v1.x;
        v2.x = _v2.x;
        v1.y = _v1.y;
        v2.y = _v2.y;
    }
}
float Line::A(float xd, float yd){
    return v2.y - v1.y;
}
float Line::B(float xd, float yd){
    return v1.x - v2.x;
}
float Line::C(float xd, float yd){
    return v1.y*v2.x - v1.x*v2.y + yd*( v2.x - v1.x ) + xd*( v1.y - v2.y );
}

bool Line::checkPoint(float x, float y){
    if( x >= v1.x && x <= v2.x && y >= v1.y && y <= v2.y ){
        if( A()*x + B()*y + C() == 0 ) return true;
    }
    return false;
}

bool Line::checkCrossing( Line& line2, float xd, float yd){
    if( v2.x < line2.v1.x + xd || v1.x > line2.v2.x + xd ){
        //std::cout << "1" << std::endl;
        return false;
    }
    if( v2.y > v1.y ){
        if( line2.v2.y > line2.v1.y ){
            if( line2.v2.y + yd < v1.y || line2.v1.y + yd > v2.y){
        //std::cout << "2" << std::endl;
                return false;
            }
        }
        else{
            if( line2.v1.y + yd < v1.y || line2.v2.y + yd > v2.y){
        //std::cout << "3" << std::endl;
                return false;
            }
        }
    }
    else{        
        if( line2.v2.y  > line2.v1.y ){
            if( line2.v2.y + yd < v2.y || line2.v1.y + yd > v1.y){
        //std::cout << "4" << std::endl;
                return false;
            }
        }
        else{
            if( line2.v1.y + yd < v2.y || line2.v2.y + yd > v1.y){
        //std::cout << "5" << std::endl;
                return false;
            }
        }
    }
    float A = this -> A();
    float B = this -> B();
    float A2 = line2.A(xd,yd);
    float B2 = line2.B(xd,yd);
    float parallelCondition = A*B2 - A2*B;
    if( parallelCondition == 0 ){
        //std::cout << "6" << std::endl;
        return false;
    }
    else{
        float C = this -> C();
        float C2 = line2.C(xd,yd);
        //std::cout << "A " << A << std::endl;
        //std::cout << "A2 " << A2 << std::endl;
        //std::cout << "B " << B << std::endl;
        //std::cout << "B2 " << B2 << std::endl;
        //std::cout << "C " << C << std::endl;
        //std::cout << "C2 " << C2 << std::endl;
        float x = ( C2*B - C*B2 )/( parallelCondition );
        if( x >= v1.x && x <= v2.x && x >= line2.v1.x + xd && x <= line2.v2.x + xd ){
            if( B == 0 || B2 == 0 ){
                float y = ( C*A2 - C2*A )/( parallelCondition );
                if( v2.y > v1.y ){
                    if( y < v1.y || y > v2.y ){
                        return false;
                    }
                }
                if( v2.y < v1.y ){
                    if( y > v1.y || y < v2.y ){
                        return false;
                    }
                }
                if( line2.v2.y > line2.v1.y ){
                    if( y > line2.v2.y + yd || y < line2.v1.y + yd ){
                        return false;
                    }
                }
                if( line2.v2.y < line2.v1.y ){
                    if( y < line2.v2.y + yd || y > line2.v1.y + yd ){
                        return false;
                    }
                }
            }
        //std::cout << "A: " << A << std::endl;
        //std::cout << "B: " << B << std::endl;
        //std::cout << "C: " << C << std::endl;
        //std::cout << "A2: " << A2 << std::endl;
        //std::cout << "B2: " << B2 << std::endl;
        //std::cout << "C2: " << C2 << std::endl;
        //std::cout << "x: " << x << std::endl;
            return true;
        }
        else{
        //std::cout << "8" << std::endl;
            return false;
        }
    }
}