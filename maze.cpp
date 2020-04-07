/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
 *
 * C++ implementation by C. Ducottet
**/

#include<iostream>
#include <vector>
#include <ctime>
#include "cell.h"
#include "maze.h"

using namespace std;

Maze::Maze(int width, int height)
    : grid_(height,vector<Cell>(width)), width_(width), height_(height)
{

}

void Maze::reinit()
{
    grid_=vector<vector<Cell>>(height_,vector<Cell>(width_));
}

void Maze::addFrontier(PointInt p, list<PointInt> &frontier)
{
    if (p.first>=0 && p.second>=0 && p.second<height_ && p.first<width_
            && grid_[p.second][p.first].getValue()==0) {
        grid_[p.second][p.first].setValue(Cell::FRONTIER);
        frontier.push_back(p);
    }
}


void Maze::mark(PointInt p, list<PointInt> &frontier)
{
    grid_[p.second][p.first].setValue(Cell::MARKED);
    addFrontier(PointInt(p.first-1, p.second),frontier);
    addFrontier(PointInt(p.first+1, p.second),frontier);
    addFrontier(PointInt(p.first, p.second-1),frontier);
    addFrontier(PointInt(p.first, p.second+1),frontier);
}


list<PointInt> Maze::neighbors(PointInt p)
{
    list<PointInt> n;
    if (p.first>0 && grid_[p.second][p.first-1].getValue()==Cell::MARKED)
        n.push_back(PointInt(p.first-1, p.second));
    if (p.first+1<width_ && grid_[p.second][p.first+1].getValue()==Cell::MARKED)
        n.push_back(PointInt(p.first+1, p.second));
    if (p.second>0 && grid_[p.second-1][p.first].getValue()==Cell::MARKED)
        n.push_back(PointInt(p.first, p.second-1));
    if (p.second+1<height_ && grid_[p.second+1][p.first].getValue()==Cell::MARKED)
        n.push_back(PointInt(p.first, p.second+1));
    return n;
}


Cell::Direction Maze::direction(PointInt f, PointInt t)
{
    if (f.first<t.first) return Cell::E;
    else if (f.first>t.first) return Cell::W;
    else if (f.second<t.second) return Cell::S;
    else return Cell::N;
}


void Maze::display(bool pause)
{
    int i,j;
    string cell[3]={"..","  ","()"};

    if (pause) system("cls"); // use "clear" under linux

    // Print the first line
    for (j=0;j<width_;j++) cout<<"+--";
    cout<<'+'<<endl;

    // Print other lines
    for (i=0;i<height_;i++) {
        // Beginning of line
        cout<<'|';
        // Print cells
        for (j=0;j<width_;j++) {
            cout<<cell[grid_[i][j].getValue()];
            if (grid_[i][j].isFrontier(Cell::E)) cout<<'|';
            else cout<<' ';
        }
        cout<<endl;
        // Beginning of line
        cout<<'+';
        // Print horizontal frontier
        for (j=0;j<width_;j++) {
            if (grid_[i][j].isFrontier(Cell::S)) cout<<"--";
            else cout<<"  ";
            cout<<'+';
        }
        cout<<endl;
    }

    if (pause) {
        cout<<"Press ENTER to continue....."<<endl;
        cin.ignore(1);
    }
}

void Maze::generate(bool show)
{
    list<PointInt> frontier;

    // Initialize cells if the maze was already generated
    reinit();

    // Initialize random generator
    srand (time(NULL));

    // Mark a random cell and add the frontier cells to the list
    mark(PointInt(rand() % width_, rand() % height_),frontier);

    // Display
    if (show) display(false);

    while(!frontier.empty()) {

        // Take a random frontier cell f (from)
        auto randPos=frontier.begin();
        advance(randPos,rand() % frontier.size());
        PointInt f=*randPos;
        frontier.erase(randPos);

        // Take a random neighbor t (to) of that cell
        list<PointInt> n=neighbors(f);
        randPos=n.begin();
        advance(randPos,rand() % n.size());
        PointInt t=*randPos;

        // Carve a passage from f to t
        Cell::Direction d=direction(f,t);
        grid_[f.second][f.first].setFrontier(d,false);
        grid_[t.second][t.first].setFrontier(Cell::Direction((d+2)%4),false);

        // Mark the cell and add the frontier cells to the list
        mark(f,frontier);

        // Display
        if (show) display(false);
    }
}

vector<Wall *> Maze::get()
{
    vector<Wall *> result;
    for (int x = 0; x < height_ ; x++)
    {
        for (int y = 0; y < width_ ; y++)
        {  
            if(grid_[x][y].isFrontier(Cell::S))
            {
                Wall * w =new Wall(myPoint(2*y    ,0  ,2*(x+1)),
                                   myPoint(2*(y+1),0  ,2*(x+1)), x>=height_-1);
                result.push_back(w);
            }
            if(grid_[x][y].isFrontier(Cell::E))
            {
                Wall * w =new Wall(myPoint(2*(y+1),0  ,2*x),
                                   myPoint(2*(y+1),0  ,2*(x+1)), y>=width_-1);
                result.push_back(w);
            }
            if(x == 0)//bordure
            {
                Wall * w =new Wall(myPoint(2*y    ,0  ,2*(x)),
                                   myPoint(2*(y+1),0  ,2*(x)),true);
                result.push_back(w);
            }
            if(y == 0)//bordure
            {
                Wall * w =new Wall(myPoint(2*y,0  ,2*x),
                                   myPoint(2*y,0  ,2*(x+1)),true);
                result.push_back(w);
            }
        }
    }
    return result;
}
