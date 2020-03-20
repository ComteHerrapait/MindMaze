#include "player.h"
#include <math.h>
#include <iostream>
using namespace std;

Player::Player(Point position, Point lookingAt)
{
    pos = position;
    target = lookingAt;
}

void Player::move(float forward, float rightward)
{
    float vectX = target.x - pos.x;
    float vectZ = target.z - pos.z;
    float norm = sqrt(vectX * vectX + vectZ * vectZ);

    pos.x += forward * vectX / norm;
    pos.z += forward * vectZ / norm;
    target.x += forward * vectX / norm;
    target.z += forward * vectZ / norm;

    pos.x += rightward * - vectZ / norm;
    pos.z += rightward * vectX /norm;
    target.x += rightward * - vectZ / norm;
    target.z += rightward * vectX /norm;
}
void Player::look(float horizontal, float vertical = 0.0f){
    //float cv=cos(vertical* PI / 180.0), sv=sin(vertical* PI / 180.0);
    float ch=cos(horizontal* PI / 180.0), sh=sin(horizontal* PI / 180.0);

    float dx = target.x - pos.x;
    //float dy = target.y - pos.y;
    float dz = target.z - pos.z;

    target.x -= pos.x;
    target.z -= pos.z;

    float newX = dx * ch - dz * sh;
    float newZ = dx * sh + dz * ch;

    target.x = newX + pos.x;
    target.z = newZ + pos.z;
}

void Player::foundSpheres(){
    achievement = true;
}

bool Player::CheckCollision(Wall w){
    float HitBoxWidth = 0.2;
    Point end_1 = w.getEnd1();
    Point end_2 = w.getEnd2();
    Point milieu = Point(   (end_1.x + end_2.x)/2,
                            (end_1.y + end_2.y)/2,
                            (end_1.z + end_2.z)/2   );
    float length;
    if (end_1.z == end_2.z){ //mur selon l'axe X
        length = abs(end_1.x - end_2.x);
        if (abs(pos.z - milieu.z ) < HitBoxWidth
                && abs(pos.x - milieu.x) < ( length/2.0 + HitBoxWidth)    ){
            return true;
        }
    } else if (end_1.x == end_2.x){ // mur selon l'axe Z
        length = abs(end_1.z - end_2.z);
        if (abs(pos.x - milieu.x ) < HitBoxWidth
                && abs(pos.z - milieu.z) < ( length/2.0 + HitBoxWidth)    ){
            return true;
        }
    }
    return false;
}

void Player::moveWithCollisions(float forward, float rightward, vector<Wall *> walls){
    move(forward,rightward);
    for(Wall * w: walls){
        if (CheckCollision(*w)){
            move(-forward,-rightward);
            break;
        }
    }
}
void Player::draw2D(float offX, float offY, float scale){
    float r = 0.6 * scale;
    float x = offX + pos.x*scale;
    float y = offY + pos.z*scale; //on prend pos.z car en 3D le y est la verticale
    glColor3f(1.0, 0.0, 0.0);
    // disque
    glBegin( GL_TRIANGLE_FAN );
    glVertex2f( x, y );
    for( float i = 0; i <= 2 * PI + 0.1; i += 0.1 )
    {
        glVertex2f( x + sin( i ) * r, y + cos( i ) * r );
    }
    glEnd();

    // ligne
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2i(x,y);
    glVertex2i(offX + target.x*scale,offY + target.z*scale);
    glEnd();
}
