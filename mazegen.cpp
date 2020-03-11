#include "mazegen.h"

MazeGen::MazeGen()
{

}

vector<Wall *> MazeGen::generateStatic(){
    vector<Wall *> result;
    vector<Point> points {
                    Point(0,0,0),
                    Point(2,0,0),
                    Point(4,0,0),
                    Point(6,0,0),
                    Point(8,0,0),
                    Point(10,0,0),
                    Point(12,0,0),
                    Point(14,0,0),
                    Point(16,0,0),
                    Point(18,0,0),
                    Point(20,0,0),
                    Point(20,0,2),
                    Point(20,0,4),
                    Point(20,0,6),
                    Point(20,0,8),
                    Point(20,0,10),
                    Point(20,0,12),
                    Point(18,0,12),
                    Point(16,0,12),
                    Point(14,0,12),
                    Point(12,0,12),
                    Point(10,0,12),
                    Point(8,0,12),
                    Point(6,0,12),
                    Point(4,0,12),
                    Point(2,0,12),
                    Point(0,0,12),
                    Point(0,0,12),
                    Point(0,0,10),
                    Point(0,0,8),
                    Point(0,0,6),
                    Point(0,0,4),
                    Point(0,0,2),
                    Point(0,0,0)
            };
    Point last;
    for (Point p : points){
        if (p.x == last.x && p.y == last.y && p.z == last.z)
            continue;
        result.push_back(new Wall(last, p));
        last = p;
    }



    return result;
}
