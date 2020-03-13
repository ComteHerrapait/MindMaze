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
    Surface(bool isFloor,int length = 10, int width = 6);
    void draw();
private :
    float height;
    GLuint texMap;
    int LENGTH, WIDTH;
};

#endif // SURFACE_H
