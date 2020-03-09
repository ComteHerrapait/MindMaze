#include "wall.h"

Wall::Wall(Point p1, Point p2)
{
    end_1 = p1;
    end_2 = p2;
}

void Wall::draw(){
    Point p1,p2,p3,p4;
    float wX, wZ;


    if (end_1.z == end_2.z){ //mur selon l'axe X
        if (end_1.x > end_2.x){
            wX = - width;
        } else {
            wX = + width;
        }
        wZ = width;
        p1 = Point(end_2.x+wX,0,end_2.z+wZ);
        p2 = Point(end_1.x-wX,0,end_1.z+wZ);
        p3 = Point(end_1.x-wX,0,end_1.z-wZ);
        p4 = Point(end_2.x+wX,0,end_2.z-wZ);

    } else if (end_1.x == end_2.x){// mur selon l'axe Z
        if (end_1.z > end_2.z){
            wZ = - width;
        } else {
            wZ = + width;
        }
        wX = width;
        p1 = Point(end_2.x-wX,0,end_2.z+wZ);
        p2 = Point(end_1.x-wX,0,end_1.z-wZ);
        p3 = Point(end_1.x+wX,0,end_1.z-wZ);
        p4 = Point(end_2.x+wX,0,end_2.z+wZ);
    } else { //mur diagonal
        return ;
    }

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);//couleur

    /*    //Bottom
    glVertex3f(p1.x, 0, p1.z);
    glVertex3f(p2.x, 0, p2.z);
    glVertex3f(p3.x, 0, p3.z);
    glVertex3f(p4.x, 0, p4.z);
        //Top
    glVertex3f(p1.x, height, p1.z);
    glVertex3f(p2.x, height, p2.z);
    glVertex3f(p3.x, height, p3.z);
    glVertex3f(p4.x, height, p4.z);

    On ne voit pas le dessus et le dessous des murs
    */
        //Walls
    glVertex3f(p1.x, 0, p1.z);
    glVertex3f(p2.x, 0, p2.z);
    glVertex3f(p2.x, height, p2.z);
    glVertex3f(p1.x, height, p1.z);

    glVertex3f(p2.x, 0, p2.z);
    glVertex3f(p3.x, 0, p3.z);
    glVertex3f(p3.x, height, p3.z);
    glVertex3f(p2.x, height, p2.z);

    glVertex3f(p3.x, 0, p3.z);
    glVertex3f(p4.x, 0, p4.z);
    glVertex3f(p4.x, height, p4.z);
    glVertex3f(p3.x, height, p3.z);

    glVertex3f(p4.x, 0, p4.z);
    glVertex3f(p1.x, 0, p1.z);
    glVertex3f(p1.x, height, p1.z);
    glVertex3f(p4.x, height, p4.z);

    glEnd();

    glPopMatrix();
}
