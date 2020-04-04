#ifndef SPHERE_H
#define SPHERE_H
#include "mypoint.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>
#include "player.h"
#include <QImage>
#include <QGLWidget>
#include <ctime>

class Sphere
{
public:
    Sphere(myPoint p, float r);
    void draw(float time_);
    void draw2D(float offX, float offY, float scale);
    void detect(Player p);
    bool isFound() {return found;}
    myPoint getPos() {return pos;}
private:
    float color[3];//couleur de la sphere
    myPoint pos;//Point du centre de la sphere
    float radius; //rayon de la sphere
    GLUquadric* quadric ;
    float found = false; //booleen indiquant si la boule est recuperee
    GLuint texMap;

};

#endif // SPHERE_H
