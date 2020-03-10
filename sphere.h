#ifndef SPHERE_H
#define SPHERE_H
#include "point.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include "player.h"
#include <QImage>
#include <QGLWidget>

class Sphere
{
public:
    Sphere(Point p, float r);
    void draw();
    void detect(Player p);
private:
    float color[3];//couleur de la sphere
    Point pos;//Point du centre de la sphere
    float radius; //rayon de la sphere
    GLUquadric* quadric ;
    float found = false; //booleen indiquant si la boule est recuperee
    GLuint texMap;

};

#endif // SPHERE_H
