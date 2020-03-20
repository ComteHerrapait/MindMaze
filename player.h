#ifndef PLAYER_H
#define PLAYER_H
#include "point.h"
#include <vector>
#include <math.h>
#include <wall.h>
#define PI 3.14159265


class Player
{
public:
    //Player() : Player( Point(0,0,0), Point(1,0,0) ) {}
    Player(Point position, Point lookingAt);
    void move(float forward, float rightward); //movement of the Player
    void moveWithCollisions(float forward, float rightward, std::vector<Wall *> walls); //movement of the Player with collisions
    void look(float vertical, float horizontal); //change head orientation
    void foundSpheres();
    Point getPos() {return pos;}
    Point getTarget() {return target;}
    bool getAchievement() {return achievement;}
    bool CheckCollision(Wall w);
    void draw2D(float offX, float offY, float scale);
private :
    Point pos ; //position of the player
    Point target ; //position the player is looking at
    bool achievement = false; //store if the player has succeded at the mission (TBD)

};

#endif // PLAYER_H
