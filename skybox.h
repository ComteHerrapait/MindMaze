#ifndef SKYBOX_H
#define SKYBOX_H
#include <iostream>
#include <QGLWidget>
#include <QtOpenGL>
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QImage>

class Skybox
{
public:
    Skybox(int distance);
    void draw();
private:
    GLuint texMap;
    int skyDistance;
};

#endif // SKYBOX_H
