#ifndef WALL_H
#define WALL_H
#include "point.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Wall
{
public:
    Wall(Point p1, Point p2);
    void draw();
private:
    Point end_1 ;
    Point end_2 ;
    float width = 0.05;
    float height = 2.0;
};

#endif // WALL_H
