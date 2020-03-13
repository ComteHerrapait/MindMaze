/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
 *
 * C++ implementation by C. Ducottet
**/

#ifndef CELL_H
#define CELL_H

#include <string>

using namespace std;

class Cell
{
public:
    enum Type {EMPTY,MARKED,FRONTIER};
    enum Direction {N=1,S=3,E=0,W=2};

private:
    int value_=EMPTY;
    bool frontier[4]={true,true,true,true};

public:
    int getValue() const {return value_;}
    bool isFrontier(Direction d) const {return frontier[d];}
    void setValue(int type) {value_=type;}
    void setFrontier(Direction d,bool state) {frontier[d]=state;}
};

#endif // CELL_H
