/*
* Name: Susan Yuen
* MacID: yuens2
* Student ID: 001416198
*/

#ifndef __RULESOFLIFE_H__
#define __RULESOFLIFE_H__

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "Draw.h"

#include <unistd.h>

using namespace std;

class RulesOfLife
{
public:
    RulesOfLife(Draw);
    void updateGrid();                          //updates the grid and calls game rule function
    void randomizeGrid();                       //randomizes a grid
    void alternateLifeOrDeath(int, int, int);   //handles mouse clicks to turn on/off cells
    void reset();                               //resets all cells to dead

private:
    Draw draw;
    void deathRules();                              //holds rules of the game (cell life and death)
    int numberOfLiveNeighbours(pair<int, int>);     //returns number of live neighbours around specified cell
    static const int GRID_SIZE = 100;               //size of grid (based on number of cells)
};

#endif
