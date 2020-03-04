#ifndef PLAYER_H
#define PLAYER_H
#include "point.h"


class Player
{
public:
    //Player() : Player( Point(0,0,0), Point(1,0,0) ) {}
    Player(Point position, Point lookingAt);
    void move(float forward, float rightward); //movement of the Player
    void look(float vertical, float horizontal); //change head orientation

    Point getPos() {return pos;}
    Point getTarget() {return target;}

private :
    Point pos ; //position of the player
    Point target ; //position the player is looking at
    bool achievement; //store if the player has succeded at the mission (TBD)

};

#endif // PLAYER_H
