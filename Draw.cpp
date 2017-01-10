/*
* Name: Susan Yuen
* MacID: yuens2
* Student ID: 001416198
*/

#include "Draw.h"

#include <iostream>

using namespace std;

Draw::Draw()
{
    TILE_LENGTH = 0.02;    //tile sizes
    setupCells();
}

void Draw::setupCells()
{
    //sets all cells to dead
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
        {
            cellMatrix[i][j] = false;
        }
    }
}

bool Draw::isCellAlive(int positionX, int positionY)
{
    return cellMatrix[positionX][positionY];
}

void Draw::setIsCellAlive(int positionX, int positionY, bool isAlive)
{
    cellMatrix[positionX][positionY] = isAlive;
}

void Draw::setIsNextCellAlive(int positionX, int positionY, bool isAlive)
{
    nextCellMatrix[positionX][positionY] = isAlive;
}

void Draw::setNextGeneration()
{
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
        {
            //sets current cellMatrix to nextCellMatrix
            cellMatrix[i][j] = nextCellMatrix[i][j];
        }
    }
}

void Draw::drawTile(pair<float, float> coordinates)
{
    float xoffset = coordinates.first;
    float yoffset = coordinates.second;

    glColor3f(0, 0, 0);

    glBegin(GL_LINE_LOOP);
        glVertex2f(xoffset, yoffset);
        glVertex2f(TILE_LENGTH+xoffset, yoffset);
        glVertex2f(TILE_LENGTH+xoffset, TILE_LENGTH+yoffset);
        glVertex2f(xoffset, TILE_LENGTH+yoffset);
    glEnd();
}

void Draw::drawGrid()
{
    //iterate to draw tiles for grid
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
        {
            drawTile(getCoordinates(make_pair(i,j)));
        }
    }
}

pair<float, float> Draw::getCoordinates(pair<int, int> position)
{
    int positionX = position.first;
    int positionY = position.second;

    float xcoordinate = -(TILE_LENGTH*GRID_SIZE/2)+(TILE_LENGTH*positionX);
    float ycoordinate = -(TILE_LENGTH*GRID_SIZE/2)+(TILE_LENGTH*positionY);

    return make_pair(xcoordinate, ycoordinate);
}

void Draw::fillTile(pair<int, int> position, string colour)
{
    //gets coordinates of the position
    pair<float, float> coordinates = getCoordinates(position);
    float xcoordinate = coordinates.first;
    float ycoordinate = coordinates.second;

    //sets the colour based on specified colour
    if (colour == "WHITE")
    {
        glColor3f(1, 1, 1);

    }
    else if (colour == "BLACK")
    {
        glColor3f(0, 0, 0);
    }

    //fills the tile using polygon
    glBegin(GL_POLYGON);
        glVertex2f(xcoordinate, ycoordinate);
        glVertex2f(TILE_LENGTH+xcoordinate, ycoordinate);
        glVertex2f(TILE_LENGTH+xcoordinate, TILE_LENGTH+ycoordinate);
        glVertex2f(xcoordinate, TILE_LENGTH+ycoordinate);
    glEnd();
}
