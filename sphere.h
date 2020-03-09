#ifndef SPHERE_H
#define SPHERE_H
#include "point.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

class Sphere
{
public:
    Sphere(Point p, float r);
    void draw();
private:
    float color[3];
    Point pos;
    float radius;
    GLUquadric* quadric ;

};

#endif // SPHERE_H
