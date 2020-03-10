#ifndef WALL_H
#define WALL_H
#include "point.h"
#include "player.h"
#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <QImage>
#include <QtOpenGL>

using namespace std;

class Wall
{
public:
    Wall(Point p1, Point p2);
    void draw();
    bool CheckCollision(Player p);
private:
    Point end_1 ;
    Point end_2 ;
    float width = 0.05;
    float HitBoxWidth = 0.3;
    float height = 2.0;
    GLuint texMap;
};

#endif // WALL_H
