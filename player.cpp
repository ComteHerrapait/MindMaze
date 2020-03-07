#include "player.h"
#include <math.h>
#include <iostream>
using namespace std;

Player::Player(Point position, Point lookingAt)
{
    pos = position;
    target = lookingAt;
    cout<<"player initialized at ("<<pos.x<<", "<<pos.y<<", "<<pos.z<< ") \n"
        <<"looking at ("<< target.x << ", " << target.y << ", " << target.z<< ") done."<<endl;
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
    float cv=cos(vertical* PI / 180.0), sv=sin(vertical* PI / 180.0);
    float ch=cos(horizontal* PI / 180.0), sh=sin(horizontal* PI / 180.0);

    float dx = target.x - pos.x;
    float dy = target.y - pos.y;
    float dz = target.z - pos.z;

    target.x -= pos.x;
    target.z -= pos.z;

    float newX = dx * ch - dz * sh;
    float newZ = dx * sh + dz * ch;

    target.x = newX + pos.x;
    target.z = newZ + pos.z;


}
