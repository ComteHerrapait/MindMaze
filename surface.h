#ifndef SURFACE_H
#define SURFACE_H
#include <iostream>
#include <QGLWidget>
#include <QtOpenGL>
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include <QImage>

class Surface
{
public:
    Surface(bool isFloor);
    void draw();
private :
    bool isFloor;
    float height;

};

#endif // SURFACE_H
