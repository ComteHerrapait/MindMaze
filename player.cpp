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
