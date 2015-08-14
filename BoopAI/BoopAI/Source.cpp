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
	//cout << "Rand: " << (rand() / (double) (RAND_MAX + 1)) << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world->run();
	glutSwapBuffers();
}


int main(int argc, char *argv[])
{
	srand(clock());
	world = new World(40);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("AnooGame");

	glOrtho(0, (WIDTH), 0, (HEIGHT), 1, -1);
	//glOrtho(-40, 40, -30, 30, 1, -1);

	glPointSize(5.0f);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glutMainLoop();

	return 1;
}