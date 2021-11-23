#include <glut.h>
#include<iostream>
#include<cstdlib>
#include <cmath>
#include <cstdio>
#include <math.h>
#include <iostream>	
#include <string>

#define PI 3.14159265f

char title[] = "Octahedron";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;

int numSegments = 7;

GLfloat R = 1; // радиус

int refreshMillis = 30;

 GLint  edges[8];


GLfloat normals[8][3] =
{
	{-1, 1, 1},
	{1, 1, 1},
	{-1, -1, 1},
	{1, -1, 1},
	{-1, 1, -1},
	{1, 1, -1},
	{-1, -1, -1},
	{1, -1, -1}
};


void edge(GLfloat xN, GLfloat yN, GLfloat zN) {
	for (int i = 0; i < numSegments; i++) {
		if (i % 2 == 0) glBegin(GL_QUADS);
		else glBegin(GL_LINE_LOOP);
		glVertex3f(0, yN * ((R / numSegments) * i), zN * (R - (R / numSegments) * i));
		glVertex3f(xN * (R - (R / numSegments) * i), yN * ((R / numSegments) * i), 0);
		glVertex3f(xN * (R - (R / numSegments) * (i + 1)), yN * ((R / numSegments) * (i + 1)), 0);
		glVertex3f(0, yN * ((R / numSegments) * (i+1)), zN * (R - (R / numSegments) * (i + 1)));
		
		glEnd();	
	}
}

void setupPointers(void)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	for (int i = 0; i < 8; i++) {
		edges[i] = glGenLists(1);
		glNewList(edges[i], GL_COMPILE);
		edge(normals[i][0], normals[i][1], normals[i][2]);
		glEndList();
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}

}

void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.0);
	glColor3f(0.7, 0.0, 0.0);
	for (int i = 0; i < 8; i++) {
		glCallList(edges[i]);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -2.0);
	}

	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (GLdouble)w / h, 0.1, 10.0);//насколько широко открыто око камеры (120 градусов)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

void keyboard_function(unsigned char key, int x, int y)
{
	/*if (key == ' ')
	{
		if (OCcounter == 0) {
			OCflag = 1;
			OCcounter += OCflag;
		}
		else if (OCcounter == 100) {
			OCflag = -1;
			OCcounter += OCflag;
		}
	}
	else if (key == 't') {
		if (isTexOn) isTexOn = 0;
		else {
			isTexOn = 1;
		}
	}
	else if (key == 'a') {
		if (alpha == 1) alpha = transparency;
		else {
			alpha = 1;
		}
	}*/
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(title);

	setupPointers();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, Timer, 0);
	glutKeyboardFunc(keyboard_function);
	glutMainLoop();
	return 0;
}