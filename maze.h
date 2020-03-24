#ifndef MAZE_H
/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
 *
 * C++ implementation by C. Ducottet
**/

#define MAZE_H

#include "cell.h"
#include <vector>
#include <list>
#include <utility>
#include "point.h"
#include "wall.h"


using namespace std;

using PointInt = pair<int,int>;

class Maze
{
private:
    vector<vector<Cell>> grid_;

    int width_;
    int height_;

    void addFrontier(PointInt p,list<PointInt> & frontier);
    void mark(PointInt p,list<PointInt> & frontier);
    list<PointInt> neighbors(PointInt p);
    Cell::Direction direction(PointInt f, PointInt t);

public:
    Maze(int width,int height);
    void reinit();
    void display(bool pause=false);
    void generate(bool show=false);
    vector<Wall *> get();
};

#endif // MAZE_H
