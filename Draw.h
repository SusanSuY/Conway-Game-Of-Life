/*
* Name: Susan Yuen
* MacID: yuens2
* Student ID: 001416198
*/

#ifndef __DRAW_H__
#define __DRAW_H__

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <string>
#include <utility>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Draw
{
public:
    Draw();
    void setupCells();                          //initial setup; sets all cells in the grid to dead
    bool isCellAlive(int, int);                 //returns the current status (alive or dead) of cell in the specified position
    void setIsCellAlive(int, int, bool);        //sets if the cell is currently alive or dead at specified position
    void setIsNextCellAlive(int, int, bool);    //sets if the cell is alive or dead at specified position, in the next generation
    void setNextGeneration();                   //updates the current generation as the next generation
    void drawGrid();                            //draws the grid (made up of tiles)
    void fillTile(pair<int, int>, string);      //fills a tile with a specified colour (WHITE or BLACK)

private:
    void drawTile(pair<float, float>);                              //draws one tile (used to draw grid)
    pair<float, float> getCoordinates(pair<int, int> position);     //returns the coordinates of a given position
    float TILE_LENGTH;                                              //length of one tile/cell
    static const int GRID_SIZE = 100;                               //size of grid (number of cells)
    bool cellMatrix[GRID_SIZE][GRID_SIZE];                          //cell matrix that tells whether a cell is alive or not
    bool nextCellMatrix[GRID_SIZE][GRID_SIZE];                      //temporary cell matrix that holds next generation, telling whether a cell is alive or not
};

#endif
