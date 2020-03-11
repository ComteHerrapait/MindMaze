#ifndef WALL_H
#define WALL_H
#include "point.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QImage>
#include <QtOpenGL>

using namespace std;

class Wall
{
public:
    Wall(Point p1, Point p2);
    void draw();
    Point getEnd1() {return end_1;}
    Point getEnd2() {return end_2;}
private:
    Point end_1 ;
    Point end_2 ;
    float width = 0.05;
    float height = 2.0;
    GLuint texMap;
};

#endif // WALL_H
