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
#include "math_3d.h"
#include "FPSTimer.h"
#include "shader.h"

using namespace std;
World *world = NULL;
static b2World *physWorld = NULL;
FPSTimer *fpsTimer = new FPSTimer(60);
GLuint program;
GLint attribute_coord2d;

void drawText(float x, float y, void *font, char *string) {
	char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != NULL; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void render()
{
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	fpsTimer->timeFrame();

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	physWorld->Step(timeStep, velocityIterations, positionIterations);
	glColor3f(1.f, 1.f, 1.f);
	drawText(0.2f, 0.5f, GLUT_BITMAP_HELVETICA_18, fpsTimer->getFps());
	//world->run();
	world->render();
	glutSwapBuffers();
}

void idleRender()
{
	world->run();
	glutPostRedisplay();
}

struct Mouse {
	int x, y;
} Mouse;

void mouseClick(int button, int state, int x, int y)
{
	Mouse.x = (x - (WIDTH / 2)) / 10;
	Mouse.y = -(y - (HEIGHT / 2)) / 10;
	if (state == 0)
	{
		if (button == 0)
		{
			for each (Boop *boop in world->boops)
			{
				if (boop->health < 200)
				{
					boop->health = 0;
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	srand(clock());

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("AnooGame");

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	physWorld = new b2World(b2Vec2(0, 0));
	world = new World(physWorld, false);

	glutMouseFunc(mouseClick);

	glOrtho(0, (WIDTH), 0, (HEIGHT), 1, -1);
	glutDisplayFunc(render);
	glutIdleFunc(idleRender);

	//GLuint program=LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	//glUseProgram(program);

	glutMainLoop();
	return 1;
}