#ifndef POINT_H
#define POINT_H
#include <cmath>

struct Point {
    float x,y,z;
    Point(float X, float Y, float Z) { x=X; y=Y; z=Z;}
    Point() {x=0.0f; y=0.0f; z=0.0f;}
    float distanceTo(Point p2)
    {
        return sqrt(pow((p2.x - this->x),2)+
                    pow((p2.y - this->y),2)+
                    pow((p2.z - this->z),2));
    }
};
#endif // POINT_H
