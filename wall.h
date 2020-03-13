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
    Wall(Point p1, Point p2, bool edge = false);
    void draw();
    Point getEnd1() {return end_1;}
    Point getEnd2() {return end_2;}
    bool isOnTheEdge() {return onTheEdge;}
private:
    Point end_1 ;
    Point end_2 ;
    float width = 0.05;//moitié de l'épaisseur totale
    float height = 2.0;
    GLuint texMap;
    bool onTheEdge = false;
};

#endif // WALL_H
