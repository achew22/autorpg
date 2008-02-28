#ifndef POINT_H
#define POINT_H

class Point
{
public:
    double x;
    double y;
    Point();
    Point(double a, double b);
    Point operator =(Point toEqual);
    bool operator ==(Point toEqual);
    bool operator !=(Point toEqaul);
};

#endif
