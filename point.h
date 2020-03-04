#ifndef POINT_H
#define POINT_H
struct Point {
    float x,y,z;
    Point(float X, float Y, float Z) { x=X; y=Y; z=Z;}
    Point() {x=0.0f; y=0.0f; z=0.0f;}
};
#endif // POINT_H
