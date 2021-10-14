#include <glut.h>
#include<iostream>
#include<cstdlib>
#include <cmath>
#include <cstdio>
#include <math.h>

#define PI 3.14159265f

char title[] = "Cycle";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;

GLfloat ballRadius = 0.15f;
GLfloat xPos = 0.0f;
GLfloat yPos = 0.6f;
GLfloat xPosMax, xPosMin, yPosMax, yPosMin;
GLdouble xLeft, xRight, yBottom, yTop;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.0f;
int refreshMillis = 30;
bool day = 0;
GLfloat sky_colour[3];

void initGL() {
	glClearColor(0.0, 0.75, 1.0, 1.0);
	// рассчет освещения

	glEnable(GL_LIGHTING);

	// двухсторонний расчет освещения

	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// автоматическое приведение нормалей к

	// единичной длине

	//glEnable(GL_NORMALIZE);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	GLfloat light_position1[] = { xPos, yPos, 2, 1 };
	GLfloat light1[] = { 1, 1, 1, 0 };

	//Небо
	glBegin(GL_QUADS);
	if (day) {
		sky_colour[0] = 0.0f;
		sky_colour[1] = 0.75f;
		sky_colour[2] = 1.0f;
	}
	else {
		sky_colour[0] = 0.0f;
		sky_colour[1] = 0.0f;
		sky_colour[2] = 0.3f;
	}
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sky_colour);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, ground_colour);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ground_colour);

	glColor3f(0.0f, 0.75f, 1.0f);
	glVertex2f(xLeft, yBottom * 0.1);
	glVertex2f(xRight, yBottom * 0.1);
	glVertex2f(xRight, yTop);
	glVertex2f(xLeft, yTop);
	glEnd();

	// setup
	glEnable(GL_LIGHT0);

	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);

	glLightfv(GL_LIGHT0, GL_SPECULAR, light1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	
	glTranslatef(xPos, yPos, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	GLfloat sun_colour[] = { 1.0f, 0.5f, 0.1f };
	if (day) {
		sun_colour[0] = 1.0f;
		sun_colour[1] = 0.5f;
		sun_colour[2] = 0.1f;
	}
	else {
		sun_colour[0] = 0.9f;
		sun_colour[1] = 0.9f;
		sun_colour[2] = 0.9f;
	}
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_colour);
	glColor3f(1.0f, 0.5f, 0.1f);
	glVertex2f(0.0f, 0.0f);
	int numSegments = 100;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++)
	{
		angle = i * 2.0f * PI / numSegments;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();

	glTranslatef(-xPos, -yPos, 0.0f);

	
	
	//Земля
	glBegin(GL_QUADS);
	GLfloat ground_colour[] = { 0.09f, 0.45f, 0.27f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_colour);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, ground_colour);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ground_colour);

	glColor3f(0.1f, 0.5f, 0.3f);
	glVertex2f(xLeft, yBottom * 0.1);
	glVertex2f(xRight, yBottom * 0.1);
	glVertex2f(xRight, yBottom);
	glVertex2f(xLeft, yBottom);
	glEnd();
	//Дом
	GLfloat house_colour[] = { 0.5f, 0.2f, 0.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, house_colour);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, house_colour);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, house_colour);
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.2f, 0.0f);
	glVertex2f(xRight * 0.2, yBottom * 0.1);
	glVertex2f(xRight * 0.7, yBottom * 0.1);
	glVertex2f(xRight * 0.7, yTop * 0.5);
	glVertex2f(xRight * 0.2, yTop * 0.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	GLfloat roof_colour[] = { 0.3f, 0.3f, 0.3f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, roof_colour);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex2f(xRight * 0.15, yTop * 0.5);
	glVertex2f(xRight * 0.45, yTop * 0.9);
	glVertex2f(xRight * 0.75, yTop * 0.5);
	glEnd();

	glBegin(GL_QUADS);
	GLfloat windows_colour[] = { 0.9f, 0.9f, 0.6f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, windows_colour);
	glColor3f(0.9f, 0.9f, 0.6f);
	glVertex2f(xRight * 0.3, yTop * 0.1);
	glVertex2f(xRight * 0.4, yTop * 0.1);
	glVertex2f(xRight * 0.4, yTop * 0.3);
	glVertex2f(xRight * 0.3, yTop * 0.3);
	glEnd(); 

	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.6f);
	glVertex2f(xRight * 0.5, yTop * 0.1);
	glVertex2f(xRight * 0.6, yTop * 0.1);
	glVertex2f(xRight * 0.6, yTop * 0.3);
	glVertex2f(xRight * 0.5, yTop * 0.3);
	glEnd();

	

	glutSwapBuffers();

	xPos += xSpeed;
	yPos = sqrt(((xPosMax -abs(xPos))/ xPosMax)*yPosMax);

	if (xPos > xPosMax) {
		xPos = xPosMin;
		yPos = sqrt(((xPosMax - abs(xPos)) / xPosMax) * yPosMax);
		day = !day;
	}
}


void reshape(GLsizei weight, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)weight / height;

	glViewport(0, 0, weight, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (weight <= height) {
		xLeft = -1.0;
		xRight = 1.0;
		yBottom = -1.0 / aspect;
		yTop = 1.0 / aspect;
	}
	else {
		xLeft = -1.0 * aspect;
		xRight = 1.0 * aspect;
		yBottom = -1.0;
		yTop = 1.0;
	}
	gluOrtho2D(xLeft, xRight, yBottom, yTop);
	xPosMin = xLeft;
	xPosMax = xRight;
	yPosMin = yBottom ;
	yPosMax = yTop - ballRadius;


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow(title);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, Timer, 0);
	initGL();
	glutMainLoop();
	return 0;
}