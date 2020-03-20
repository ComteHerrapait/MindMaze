#ifndef WALL_H
#define WALL_H
#include "point.h"
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
    Wall(Point p1, Point p2, bool edge = false);
    void draw();
    void draw2D();
    Point getEnd1() {return end_1;}
    Point getEnd2() {return end_2;}
    bool isOnTheEdge() {return onTheEdge;}
private:
    vector<Point> createBase(Point p1, Point p2, float width);
    Point end_1 ;
    Point end_2 ;
    float width = 0.05;//moitié de l'épaisseur totale
    float width2D = 10;
    float height = 2.0;
    GLuint texMap;
    bool onTheEdge = false;
};

#endif // WALL_H
