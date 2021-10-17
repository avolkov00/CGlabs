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

	glEnableClientState(GL_VERTEX_ARRAY);
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	//Небо

	if (day) {
		sky_colour[0] = 0.0f;
		sky_colour[1] = 0.75f;
		sky_colour[2] = 1.0f;
	}
	else {
		sky_colour[0] = 0.0f;
		sky_colour[1] = 0.0f;
		sky_colour[2] = 0.2f;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sky_colour);

	GLfloat VertexSkyAndGround[6][2];

	VertexSkyAndGround[0][0] = xLeft;
	VertexSkyAndGround[0][1] = yTop;
	VertexSkyAndGround[1][0] = xRight;
	VertexSkyAndGround[1][1] = yTop;
	VertexSkyAndGround[2][0] = xRight;
	VertexSkyAndGround[2][1] = yBottom * 0.1;
	VertexSkyAndGround[3][0] = xLeft;
	VertexSkyAndGround[3][1] = yBottom * 0.1;
	VertexSkyAndGround[4][0] = xLeft;
	VertexSkyAndGround[4][1] = yBottom ;
	VertexSkyAndGround[5][0] = xRight;
	VertexSkyAndGround[5][1] = yBottom ;

	glVertexPointer(2, GL_FLOAT, 0, VertexSkyAndGround);

	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);

	// setup Lights
	glEnable(GL_LIGHT0);

	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.05);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);


	GLfloat light_position1[] = { xPos, yPos, 2, 1 };
	GLfloat light1[] = { 1, 1, 1, 0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	
	//солнца
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
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sun_colour);
	
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
	GLfloat ground_colour[] = { 0.09f, 0.35f, 0.17f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ground_colour);

	glDrawArrays(GL_QUADS, 2, 4);

	glDisableClientState(GL_VERTEX_ARRAY);


	//Дом
	GLfloat house_colour[] = { 0.5f, 0.2f, 0.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, house_colour);
	
	GLfloat VertexHouseWalls[4][2];

	VertexHouseWalls[0][0] = xRight * 0.2;
	VertexHouseWalls[0][1] = yBottom * 0.1;
	VertexHouseWalls[1][0] = xRight * 0.7;
	VertexHouseWalls[1][1] = yBottom * 0.1;
	VertexHouseWalls[2][0] = xRight * 0.7;
	VertexHouseWalls[2][1] = yTop * 0.5;
	VertexHouseWalls[3][0] = xRight * 0.2;
	VertexHouseWalls[3][1] = yTop * 0.5;

	glVertexPointer(2, GL_FLOAT, 0, VertexHouseWalls);

	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);

	//крыша
	GLfloat roof_colour[] = { 0.3f, 0.3f, 0.3f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, roof_colour);

	GLfloat VertexHouseRoof[3][2];

	VertexHouseRoof[0][0] = xRight * 0.15;
	VertexHouseRoof[0][1] = yTop * 0.5;
	VertexHouseRoof[1][0] = xRight * 0.45;
	VertexHouseRoof[1][1] = yTop * 0.9;
	VertexHouseRoof[2][0] = xRight * 0.75;
	VertexHouseRoof[2][1] = yTop * 0.5;

	glVertexPointer(2, GL_FLOAT, 0, VertexHouseRoof);

	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableClientState(GL_VERTEX_ARRAY);

	//окна
	GLfloat windows_colour[] = { 0.9f, 0.9f, 0.6f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, windows_colour);

	GLfloat VertexHouseWindows[8][2];

	VertexHouseWindows[0][0] = xRight * 0.3;
	VertexHouseWindows[0][1] = yTop * 0.1;
	VertexHouseWindows[1][0] = xRight * 0.4;
	VertexHouseWindows[1][1] = yTop * 0.1;
	VertexHouseWindows[2][0] = xRight * 0.4;
	VertexHouseWindows[2][1] = yTop * 0.3;
	VertexHouseWindows[3][0] = xRight * 0.3;
	VertexHouseWindows[3][1] = yTop * 0.3;
	VertexHouseWindows[4][0] = xRight * 0.5;
	VertexHouseWindows[4][1] = yTop * 0.1;
	VertexHouseWindows[5][0] = xRight * 0.6;
	VertexHouseWindows[5][1] = yTop * 0.1;
	VertexHouseWindows[6][0] = xRight * 0.6;
	VertexHouseWindows[6][1] = yTop * 0.3;
	VertexHouseWindows[7][0] = xRight * 0.5;
	VertexHouseWindows[7][1] = yTop * 0.3;

	glVertexPointer(2, GL_FLOAT, 0, VertexHouseWindows);

	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS, 0, 4);
	glDrawArrays(GL_QUADS, 4, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	

	glutSwapBuffers();

	xPos += xSpeed;
	yPos = yPosMax -(yPosMax*xPos*xPos)/ (xPosMax*xPosMax);

	if (xPos > xPosMax) {
		xPos = xPosMin;
		yPos = yPosMax - (yPosMax * xPos * xPos) / (xPosMax * xPosMax);
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