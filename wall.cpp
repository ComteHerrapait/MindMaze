#include "wall.h"

Wall::Wall(Point p1, Point p2)
{
    end_1 = p1;
    end_2 = p2;
}
vector<Point> createBase(Point p1, Point p2, float width){
    vector<Point> result;
    float wX, wZ;

    if (p1.z == p2.z){ //mur selon l'axe X
        if (p1.x > p2.x){
            wX = - width;
        } else {
            wX = + width;
        }
        wZ = width;
        result.push_back(Point(p2.x+wX,0,p2.z+wZ));
        result.push_back(Point(p1.x-wX,0,p1.z+wZ));
        result.push_back(Point(p1.x-wX,0,p1.z-wZ));
        result.push_back(Point(p2.x+wX,0,p2.z-wZ));
    } else if (p1.x == p2.x){// mur selon l'axe Z
        if (p1.z > p2.z){
            wZ = - width;
        } else {
            wZ = + width;
        }
        wX = width;
        result.push_back(Point(p2.x-wX,0,p2.z+wZ));
        result.push_back(Point(p1.x-wX,0,p1.z-wZ));
        result.push_back(Point(p1.x+wX,0,p1.z-wZ));
        result.push_back(Point(p2.x+wX,0,p2.z+wZ));
    }
    return result;
}
void Wall::draw(){
    vector<Point> base = createBase(end_1, end_2, width);
    Point p1,p2,p3,p4;
    p1 = base[0];
    p2 = base[1];
    p3 = base[2];
    p4 = base[3];

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

bool Wall::CheckCollision(Player p){
    Point P = p.getPos();
    Point milieu = Point(   (end_1.x + end_2.x)/2,
                            (end_1.y + end_2.y)/2,
                            (end_1.z + end_2.z)/2   );
    float length;
    if (end_1.z == end_2.z){ //mur selon l'axe X
        length = abs(end_1.x - end_2.x);
        if (abs(P.z - milieu.z ) < HitBoxWidth
                && abs(P.x - milieu.x) < ( length/2.0 + HitBoxWidth)    ){
            return true;
        }
    } else if (end_1.x == end_2.x){ // mur selon l'axe Z
        length = abs(end_1.z - end_2.z);
        if (abs(P.x - milieu.x ) < HitBoxWidth
                && abs(P.z - milieu.z) < ( length/2.0 + HitBoxWidth)    ){
            return true;
        }
    }
    return false;
}
