#include <glut.h>
#include<iostream>
#include<cstdlib>
#include <cmath>
#include <cstdio>
#include <math.h>
#include <iostream>
#define PI 3.14159265f


// Нумерация элементов массивов vertices (присвоение вершинам номера от 0 до 7) и colors. Составляем из вершин треугольники - грани (а1, а2, а3, а4, а5, а6, а7, а8)
GLubyte a1[] = { 0, 2, 1 }; //
GLubyte a2[] = { 1, 2, 3 }; //
GLubyte a3[] = { 0, 1, 4 }; //
GLubyte a4[] = { 1, 3, 4 }; //
GLubyte a5[] = { 0, 5, 2 }; //
GLubyte a6[] = { 2, 5, 3 }; //
GLubyte a7[] = { 0, 4, 5 }; //
GLubyte a8[] = { 5, 4, 3 }; //

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


void setupPointers(void)
{   
	static GLint vertices[] =
	{
		-R, 0, 0,  //0 левый
		0, 0, R, //1 дальный
		0, R, 0, //2 верхний
		R, 0, 0, //3 правый
		0, -R, 0, //4 нижний
		0, 0, -R //5 ближний
	}; 
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_INT, 0, vertices); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); 
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	

	glEnable(GL_NORMALIZE);
	
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

	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.08);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);

	GLfloat lightPosition[] = { xLightPos, yLightPos, zLightPos, 1 };
	GLfloat lightColour[] = { 1, 1, 1, 0 };
	


	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, lightColour);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);



	GLfloat color[] = { 0.7, 0.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);
	
	
	glTranslatef((1.0f) * xLightPos, yLightPos, (-1.0f) * zLightPos);
	glutWireSphere(R / 6, 20, 20);
	glTranslatef((-1.0f) * xLightPos, (-1.0f) * yLightPos, (1.0f) * zLightPos);
	//8 вызовов по числу граней (пронумерованы выше)
	
	
	glNormal3f(-1, 1, 1);

	glTranslatef((-1) * moveCoef, (1) * moveCoef, (1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a1);
	moveCoef = moveCoef * (-1);
	glTranslatef((-1) * moveCoef, (1) * moveCoef, (1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(1, 1, 1);
	
	glTranslatef((1) * moveCoef, (1) * moveCoef, (1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a2);
	moveCoef = moveCoef * (-1);
	glTranslatef((1) * moveCoef, (1) * moveCoef, (1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(-1, -1, 1);
	
	glTranslatef((-1) * moveCoef, (-1) * moveCoef, (1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a3);
	moveCoef = moveCoef * (-1);
	glTranslatef((-1) * moveCoef, (-1) * moveCoef, (1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(1, -1, 1);
	
	glTranslatef((1) * moveCoef, (-1) * moveCoef, (1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a4);
	moveCoef = moveCoef * (-1);
	glTranslatef((1) * moveCoef, (-1) * moveCoef, (1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(-1, 1, -1);
	
	glTranslatef((-1) * moveCoef, (1) * moveCoef, (-1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a5);
	moveCoef = moveCoef * (-1);
	glTranslatef((-1) * moveCoef, (1) * moveCoef, (-1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(1, 1, -1);
	
	glTranslatef((1) * moveCoef, (1) * moveCoef, (-1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a6);
	moveCoef = moveCoef * (-1);
	glTranslatef((1) * moveCoef, (1) * moveCoef, (-1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(-1, -1, -1);
	
	glTranslatef((-1) * moveCoef, (-1) * moveCoef, (-1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a7);
	moveCoef = moveCoef * (-1);
	glTranslatef((-1) * moveCoef, (-1) * moveCoef, (-1) * moveCoef);
	moveCoef = moveCoef * (-1);

	glNormal3f(1, -1, -1);
	
	glTranslatef((1) * moveCoef, (-1) * moveCoef, (-1) * moveCoef);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a8);
	moveCoef = moveCoef * (-1);
	glTranslatef((1) * moveCoef, (-1) * moveCoef, (-1) * moveCoef);
	moveCoef = moveCoef * (-1);


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