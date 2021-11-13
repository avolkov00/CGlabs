#include <glut.h>
#include<iostream>
#include<cstdlib>
#include <cmath>
#include <cstdio>
#include <math.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

#define PI 3.14159265f

char title[] = "Octahedron";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;

int numSegments = 100;
int segment = 0;

GLfloat R = 1; // радиус

GLfloat maxSpacing = 0.12f;
int OCcounter = 0;
int OCflag = 0;
GLfloat moveCoef = 0;

GLfloat lightRadius = 1.5 * R;
GLfloat xLightPos = lightRadius;
GLfloat yLightPos = 0.0f;
GLfloat zLightPos = 0.0f;

int refreshMillis = 30;

unsigned int  texture[8];

int isTexOn = 0;
// Нумерация элементов массивов vertices (присвоение вершинам номера от 0 до 7) и colors. Составляем из вершин треугольники - грани
GLubyte vecArr[8][3] = 
{		{ 1, 0, 2 },
		{ 3, 1, 2 },
		{ 0, 1, 4 },
		{ 1, 3, 4 },
		{ 0, 5, 2 },
		{ 5, 3, 2 },
		{ 5, 0, 4 },
		{ 3, 5, 4 }
};

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

GLfloat texCoord[] = {
		0.0f, 0.0f,  // Нижний левый угол 
		1.0f, 0.0f,  // Нижний правый угол
		0.5f, 1.0f,   // Верхняя центральная сторона
		0.0f, 0.0f,  // Нижний левый угол 
		1.0f, 0.0f,  // Нижний правый угол
		0.5f, 1.0f   // Верхняя центральная сторона
};

GLint vertices[] =
{
	-R, 0, 0,  //0 левый
	0, 0, R, //1 дальный
	0, R, 0, //2 верхний
	R, 0, 0, //3 правый
	0, -R, 0, //4 нижний
	0, 0, -R //5 ближний
};

std::string picNames[8] = {
	"circle1.png",
	"circle2.png",
	"circle3.png",
	"circle4.png",
	"circle5.png",
	"circle6.png",
	"circle7.png",
	"circle8.png",
};

void setupPointers(void)
{ 

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_INT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoord);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


	glEnable(GL_NORMALIZE);

}

void Texture_Init()
{
	int w, h;
	int count;
	unsigned char* data;
	for (int i = 0; i < 8; i++) {
		data = stbi_load(picNames[i].c_str(), &w, &h, &count, 0);
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture[i]);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, count == 4 ? GL_RGBA : GL_RGB, w, h,
			0, count == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	
}



void display(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.0);
	GLfloat initialcolor[] = { 0.4, 0.4, 0.4, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, initialcolor);
	glEnable(GL_LIGHT0);

	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.8);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);

	GLfloat lightPosition[] = { xLightPos, yLightPos, zLightPos, 1 };
	GLfloat lightColour[] = { 1, 1, 1, 0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	GLfloat color[] = { 0.7, 0.0, 0.0 };

	if (isTexOn) {
		glEnable(GL_TEXTURE_2D);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightColour);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lightColour);
	}
	else {
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	}

	glTranslatef((1.0f) * xLightPos, yLightPos, (-1.0f) * zLightPos);
	glutWireSphere(R / 6, 20, 20);
	glTranslatef((-1.0f) * xLightPos, (-1.0f) * yLightPos, (1.0f) * zLightPos);

	for (int i = 0; i < 8; i++) {
		glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
		glTranslatef((normals[i][0]) * moveCoef, (normals[i][1]) * moveCoef, (normals[i][2]) * moveCoef);

		texCoord[vecArr[i][0] * 2] = 0.0f;
		texCoord[vecArr[i][0] * 2 + 1] = 0.0f;
		texCoord[vecArr[i][1] * 2] = 1.0f;
		texCoord[vecArr[i][1] * 2 + 1] = 0.0f;
		texCoord[vecArr[i][2] * 2] = 0.5f;
		texCoord[vecArr[i][2] * 2 + 1] = 1.0f;

		glBindTexture(GL_TEXTURE_2D, texture[i]);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, vecArr[i]);
		moveCoef = moveCoef * (-1);
		glTranslatef((normals[i][0]) * moveCoef, (normals[i][1]) * moveCoef, (normals[i][2]) * moveCoef);
		moveCoef = moveCoef * (-1);
	}

	segment = (segment + 1) % numSegments;
	std::cout << segment << " " << xLightPos << " " << zLightPos << "\n";

	xLightPos = lightRadius * cos(2.0f * PI * segment / numSegments);
	zLightPos = lightRadius * sin(2.0f * PI * segment / numSegments);
	//std::cout << xLightPos << " " << zLightPos << "\n";

	if (((OCflag == 1) && (OCcounter < 100)) || ((OCflag == -1) && (OCcounter > 0))) {
		moveCoef = 1.0f * OCcounter * maxSpacing / 100;
		OCcounter += OCflag;

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

	if (key == ' ')
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
	Texture_Init();

	glutMainLoop();
	return 0;
}