#ifndef MyMath_h
#define MyMath_h

namespace ma{
    struct Point
    {
        float x;
        float y;
    };
    
    class Solutions{
    public:
        bool solutionExist;
        int numberOfSolutions;                      
        float x[2];
        //Point xy[2];

        Solutions();
        Solutions(bool, int, float = 0.f, float = 0.f);
        Solutions(const Solutions&);
        ~Solutions();
    };
    float distanceOfTooPoints(float x1, float y1, float x2, float y2);
    float distanceLineAndPoint(float A, float B, float C, float x, float y);
    Solutions linear(float a, float b); // a*x + b = 0
    Solutions quadratic(float a, float b, float c); // a*x^2 + b*x + c = 0
    //Solutions twoCircles(float x1, float y1, float r1, float x2, float y2, float r2);
    //Solutions ellipseAndLine(float a, float b, float x0, float y0, float A, float B, float C );// (x-x0)^2/a + (y - y0)^2 = 1, A*x + B*y + C = 0
};

#endif
