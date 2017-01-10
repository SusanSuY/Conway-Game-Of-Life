/*
* Name: Susan Yuen
* MacID: yuens2
* Student ID: 001416198
*/

#include "RulesOfLife.h"

#include <iostream>

using namespace std;

RulesOfLife::RulesOfLife(Draw d)
{
    draw = d;   //takes the draw object from main.cpp
}

void RulesOfLife::updateGrid()
{
    deathRules();   //calls rule function
    draw.setNextGeneration();
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
        {
            //updates the grid
            if (draw.isCellAlive(i, j))
            {
                draw.fillTile(make_pair(i, j), "WHITE");
            }
            else
            {
                draw.fillTile(make_pair(i, j), "BLACK");
            }
        }
    }
    glFlush();
}

void RulesOfLife::randomizeGrid()
{
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
        {
            if (rand()%2 == 0)  //if random number is divisible by 2
            {
                //sets cell to dead
                draw.fillTile(make_pair(i, j), "BLACK");
                draw.setIsCellAlive(i, j, false);
            }
            else
            {
                //sets cell to alive
                draw.fillTile(make_pair(i, j), "WHITE");
                draw.setIsCellAlive(i, j, true);
            }
        }
    }
}

void RulesOfLife::alternateLifeOrDeath(int mouseX, int mouseY, int tileLength)
{
    //detects user click, finds the cell, and turns it on/off
    int positionX = mouseX/tileLength;
    int positionY = mouseY/tileLength;

    if ((positionX >= GRID_SIZE) || (positionX < 0) || (positionY >= GRID_SIZE) || (positionY < 0))
    {
        //if user clicks outside of grid, do nothing
        return;
    }

    if (draw.isCellAlive(positionX, positionY))
    {
        //if cell is alive, make it dead
        draw.fillTile(make_pair(positionX, positionY), "BLACK");
        draw.setIsCellAlive(positionX, positionY, false);
    }
    else
    {
        //if cell is dead, make it alive
        draw.fillTile(make_pair(positionX, positionY), "WHITE");
        draw.setIsCellAlive(positionX, positionY, true);
    }
}

void RulesOfLife::deathRules()
{
    //for each cell...
    for (int i=0; i<GRID_SIZE; i++)
    {
        for (int j=0; j<GRID_SIZE; j++)
        {
            int numLiveNeighbours = numberOfLiveNeighbours(make_pair(i, j));

            if (draw.isCellAlive(i, j))
            {
                if ((numLiveNeighbours == 2) || (numLiveNeighbours == 3))
                {
                    //if cell is alive and has 2 or 3 live neighbours, keep it alive
                    draw.setIsNextCellAlive(i, j, true);
                }
                else
                {
                    //if cell is alive but live neighbours < 2 or > 3, kill it
                    draw.setIsNextCellAlive(i, j, false);
                }
            }
            else
            {
                if (numLiveNeighbours == 3)
                {
                    //if cell is dead but number of live neighbours is 3, bring it to life
                    draw.setIsNextCellAlive(i, j, true);
                }
                else
                {
                    //if cell is dead and number of live neighbours != 3, keep it dead
                    draw.setIsNextCellAlive(i, j, false);
                }
            }
        }
    }
}

void RulesOfLife::reset()
{
    //clears the grid
    draw.setupCells();
    updateGrid();
}

int RulesOfLife::numberOfLiveNeighbours(pair<int, int> position)
{
    int numLiveNeighbours = 0;
    int x = position.first;
    int y = position.second;

    int dx[8]= {-1,-1,-1,0,0,1,1,1};
    int dy[8]= {-1,0,1,-1,1,-1,0,1};

    for (int i=0; i<8; i++)
    {
        int neighbourX = x+dx[i];
        int neighbourY = y+dy[i];
        bool validCell = (neighbourX >= 0) && (neighbourX < GRID_SIZE) && (neighbourY >= 0) && (neighbourY < GRID_SIZE);

        if (validCell)
        {
            if (draw.isCellAlive(neighbourX, neighbourY))
            {
                numLiveNeighbours++;
            }
        }
    }
    return numLiveNeighbours;
}
