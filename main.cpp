/*
* Name: Susan Yuen
* MacID: yuens2
* Student ID: 001416198
*/

#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "RulesOfLife.h"
#include "Draw.h"

#include <iostream>

using namespace std;

//Globals
const int WINDOW_SIZE = 600;    //size of window
const int GRID_SIZE = 100;      //size of grid (by number of cells)
const int TILE_PIXEL_LENGTH = WINDOW_SIZE/GRID_SIZE;    //pixel size of a cell
int speed = 5;                  //factor for speed of animation; ranges from 1-10 (default is 5)
bool paused = false;            //tells if the program is paused or not

Draw draw;
RulesOfLife rules(draw);

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    draw.drawGrid();    //draws grid

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y = WINDOW_SIZE - y;  //flip y to match OpenGL coordinate system

    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
    {
        //if left mouse clicked, turn cell on/off (alive or dead)
        rules.alternateLifeOrDeath(x, y, TILE_PIXEL_LENGTH);
        glFlush();
    }
}

void timer(int value)
{
    if (!paused)
    {
        rules.updateGrid();
    }
    glutTimerFunc(speed*100, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'q':
        exit(0);
        break;

    case 27:        //esc key
        exit(0);
        break;

    case 'c':
        rules.reset();
        break;

    case 'a':
        if (speed <= 10)
        {
            speed++;
        }
        break;

    case 's':
        if (speed > 0)
        {
            speed--;
        }
        break;

    case 32:        //space key
        paused = !paused;
        break;

    case 'r':
        rules.randomizeGrid();
        glFlush();
        break;

    }
}

void printInstructions()
{
    cout << "Welcome to Conway's Game of Life!" << endl;
    cout << "~ Created by Susan Yuen ~" << endl << endl;
    cout << "The controls for the game are as follows:" << endl;
    cout << "* Space = run/pause the simulation" << endl;
    cout << "* q or ESC = quit the program" << endl;
    cout << "* c = clear the grid" << endl;
    cout << "* s = speed up the simulation" << endl;
    cout << "* a = slow down the simulation" << endl;
    cout << "* r = randomize grid" << endl << endl;
}

int main(int argc, char** argv)
{
    //initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("Conway's Game of Life < Susan Yuen | yuens2 | 001416198 >");

    printInstructions();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(speed*100, timer, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return(0);
}
