#include "surface.h"

Surface::Surface(bool _isFloor)
{
    isFloor = _isFloor;
    if (_isFloor){
        height = 0.0f;
    } else {
        height = 2.0f;
    }
}

void Surface::draw(){
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex3f(0, height, 0);
    glColor3ub(255, 0, 255);
    glVertex3f(20, height, 0);
    glColor3ub(255, 255, 0);
    glVertex3f(20, height, 12);
    glColor3ub(0, 255, 255);
    glVertex3f(0, height, 12);
    glEnd();
}
