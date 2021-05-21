#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cmath>

using namespace std;
class Line
{
public:
    float x1;
    float x2;
    float A;
    float B;
    float C;
    Line(float xx1, float xx2, float AA, float BB, float CC){
        x1 = xx1;
        x2 = xx2;
        A = AA;
        B = BB;
        C = CC;
    }
};
float beziersCoordinate(float t, float p1, float p2, float p3, float p4){
    return pow(1 - t, 3)*p1 + 3*pow(1 - t, 2)*t*p2 + 3*(1-t)*pow(t, 2)*p2 + pow(t ,3)*p4;
}
float distance(float x1, float y1, float x2, float y2){
    return sqrt( pow(x1-x2, 2) + pow(y1-y2, 2) );
}
Line findLine(float x1, float y1, float x2, float y2){
    if( x1 == x2 ){
        return Line(y1,y2,1,0,x1);
    }
    else if( y1 == y2 ){
        return Line(x1,x2,0,1,y1);
    }
    else{
        return Line(x1,x2,(y1-y2)/(x1-x2),-1,(x2*y1-x1*y2)/(x2-x1));
    }
}
int main(){

    ifstream source("sciezka1.txt");
    string data;
    bool f1 = false;
    int m = 0;

    float px[4];
    float py[4];

    while(source >> data){
        if(!f1){
            if( data == "d=\"M")f1 = true;
        }
        else{
            if(data == "Z\""){
                 f1 = false;
            }
            else if(data != "C"){
                string yy;
                string xx;
                for(int i = 0; i < data.length(); i++){
                    if(data[i] == ','){
                        xx = data.substr(0,i);
                        yy = data.substr(i+1,string::npos);
                    }
                }
                float x = strtof(xx.c_str(),nullptr);
                float y = strtof(yy.c_str(),nullptr);


                px[m] = x;
                py[m] = y;
                m++;
                if( m == 4 ){

                    cout << "Kolejna linia: " << endl;
                    for( int j = 0; j < 4; j++){
                        cout << px[j] << " ";
                        cout << py[j] << endl;


                    }
                    ///

                    float t_pocz = 0.1;
                    float x2 = beziersCoordinate(t_pocz,px[0],px[1],px[2],px[3]);
                    float y2 = beziersCoordinate(t_pocz,py[0],py[1],py[2],py[3]);
                    while( distance(px[0],py[0],x2,y2) > 5 ){
                        t_pocz = t_pocz / 2;
                        float x2 = beziersCoordinate(t_pocz,px[0],px[1],px[2],px[3]);
                        float y2 = beziersCoordinate(t_pocz,py[0],py[1],py[2],py[3]);
                    }
                    float t = t pocz;
                    while( t < 1 ){

                        t = t + t_pocz;
                    }

                    ///
                    m = 1;
                    px[0] = px[3];
                    py[0] = py[3];
                }

            }

        }
    }
    return 0;
}
