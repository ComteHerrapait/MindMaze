#ifndef WALL_H
#define WALL_H
#include "mypoint.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QImage>
#include <QtOpenGL>
#include <iostream>

using namespace std;

class Wall
{
public:
    Wall(myPoint p1, myPoint p2, bool edge = false);
    void draw();
    void draw2D(float offX, float offY, float scale);
    myPoint getEnd1() {return end_1;}
    myPoint getEnd2() {return end_2;}
    bool isOnTheEdge() {return onTheEdge;}
private:
    vector<myPoint> createBase(myPoint p1, myPoint p2, float width);
    myPoint end_1 ;
    myPoint end_2 ;
    float width = 0.05;//moitié de l'épaisseur totale
    float height = 2.0;
    GLuint texMap;
    bool onTheEdge = false;
};

#endif // WALL_H
