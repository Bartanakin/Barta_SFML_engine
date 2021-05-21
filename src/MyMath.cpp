#include"MyMatch.h"
#include<math.h>

using namespace ma;
Solutions::Solutions()
:solutionExist(false),
numberOfSolutions(0){}

Solutions::Solutions(bool s, int n, float x1, float x2)
:solutionExist(s),
numberOfSolutions(n){
    x[0] = x1;
    x[1] = x2;
}

ma::Solutions::Solutions(const Solutions& s2)
    : solutionExist(s2.solutionExist),
    numberOfSolutions(s2.numberOfSolutions)
{
    x[0] = s2.x[0];
    x[1] = s2.x[1];
}


float ma::distanceOfTooPoints(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}
float ma::distanceLineAndPoint(float A, float B, float C, float x, float y){
    return( fabsf( A*x + B*y + C )/sqrt( pow(A,2) + pow(B,2) ) );
}

Solutions ma::linear(float a, float b){
    if( a == 0 && b == 0 ){
        return Solutions(true,0);
    }
    if( a == 0 && b != 0 ){
        return Solutions(false,0);
    }
    else{
        return Solutions(true,1, -b / a);
    }
}
Solutions ma::quadratic(float a, float b, float c){
    if( a == 0 ){
        return linear(b,c);
    }
    double delta = pow(b,2) - 4*a*c;
    if( delta < 0 ){
        return Solutions(false,0,NULL);
    }
    if( delta == 0 ){      
        return Solutions(true,1, -b / (2 * a));
    }
    else{
        delta = sqrt(delta);   
        return Solutions(true,2, (-b - delta) / (2 * a), (-b + delta) / (2 * a));
    }
}
// todo
/*
Solutions ma::twoCircles(float x1, float y1, float r1, float x2, float y2, float r2){
    //float y = ( 2*(y1 - y2))
    //Solutions s = quadratic(1, 2*x2, x2*x2 - r2*r2 + pow( - y2, 2));
    return Solutions(false,0);
}

Solutions ma::ellipseAndLine( float a, float b, float x0, float y0, float A, float B, float C ){ 
    Solutions s1 = quadratic(b + (a*A*A)/(B*B), (2*a*C)/B + 2*a*y0 - 2*x0, b*x0*x0 + a*(C/B + y0*y0 - b) );
    if( s1.solutionExist ){
        //if()
        s1.xy = new Point[2];
    }
    return Solutions(false,0);
} 
*/
Solutions::~Solutions(){

}