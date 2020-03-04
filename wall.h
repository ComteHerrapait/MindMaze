#ifndef WALL_H
#define WALL_H
#include "point.h"

class Wall
{
public:
    Wall();
    void draw();
private:
    Point end_1 ;
    Point end_2 ;
};

#endif // WALL_H
