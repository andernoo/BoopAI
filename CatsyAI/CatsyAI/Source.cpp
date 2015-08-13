#include <iostream>					// for cout etc.
#include <vector>					// for vector class
#include <string>					// for string class
#include <algorithm>				// for sort algorithm
#include <time.h>					// for random seed
#include <math.h>					// for abs()
#include "World.h"
#include <GL\freeglut.h>

using namespace std;
World *world = NULL;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world->run();
}


int main(int argc, char *argv[])
{
	world = new World(20);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("AnooGame");

	glOrtho(-40, 40, -30, 30, 1, -1);

	glutDisplayFunc(render);
	glutIdleFunc(render);

	glEnable(GL_BLEND);

	glClearColor(0.8, 0.8, 0.8, 0.0f);
	glLineWidth(1);

	glutMainLoop();

	return 1;
}