#ifndef PLAYER_H
#define PLAYER_H
#include "mypoint.h"
#include <vector>
#include <math.h>
#include <wall.h>
#define PI 3.14159265


class Player
{
public:
    //Player() : Player( Point(0,0,0), Point(1,0,0) ) {}
    Player(myPoint position, myPoint lookingAt);
    void move(float forward, float rightward); //movement of the Player
    void moveWithCollisions(float forward, float rightward, std::vector<Wall *> walls); //movement of the Player with collisions
    void moveWithAnimations(int forward, int rightward, int animCount, vector<Wall *> walls);
    void look(float angle); //change head orientation
    void lookWithAnimations(int angle, int animCount);
    void foundSpheres();
    myPoint getPos() {return pos;}
    myPoint getTarget() {return target;}
    bool getAchievement() {return achievement;}
    bool CheckCollision(Wall w);
    void draw2D(float offX, float offY, float scale);
    void continueMove();
    void roundPosition();
    bool isMoving() { return animationsLeft > 0;}
private :
    myPoint pos ; //position of the player
    myPoint target ; //position the player is looking at
    bool achievement = false; //store if the player has succeded at the mission (TBD)
    int animationsLeft;
    vector<double> stepSize{0,0,0};//forward, rightward and looking angle

};

#endif // PLAYER_H
