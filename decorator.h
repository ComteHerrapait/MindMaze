#ifndef DECORATOR_H
#define DECORATOR_H
#include <iostream>
#include <mypoint.h>
#include <QGLWidget>
#include <QtOpenGL>
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include <QImage>

using namespace std;

class Decorator
{
public:
    Decorator(myPoint corner1_, myPoint corner2_);
    void draw();
private:
    myPoint p1,p2,p3,p4;
    GLuint texMap;
    int norm[3] = {0,0,0};

};

#endif // DECORATOR_H
