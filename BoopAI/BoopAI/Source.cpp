#include <iostream>					// for cout etc.
#include <vector>					// for vector class
#include <string>					// for string class
#include <algorithm>				// for sort algorithm
#include <time.h>					// for random seed
#include <math.h>					// for abs()
#include "World.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <Box2D/Box2D.h>

using namespace std;
World *world = NULL;
static b2World *physWorld = NULL;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	physWorld->Step(timeStep, velocityIterations, positionIterations);
	world->run();
	glutSwapBuffers();
}


int main(int argc, char *argv[])
{
	srand(clock());

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("AnooGame");

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	physWorld = new b2World(b2Vec2(0, 0));
	world = new World(physWorld);

	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_PROGRAM_POINT_SIZE);

	glOrtho(0, (WIDTH), 0, (HEIGHT), 1, -1);
	//glOrtho(-40, 40, -30, 30, 1, -1);

	glPointSize(5.0f);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glutMainLoop();

	return 1;
}