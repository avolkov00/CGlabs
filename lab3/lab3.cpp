#include <glut.h>
#include<iostream>
#include<cstdlib>
#include <cmath>
#include <cstdio>
#include <math.h>

#define PI 3.14159265f
int R = 1; // радиус

// Нумерация элементов массивов vertices (присвоение вершинам номера от 0 до 7) и colors. Составляем из вершин треугольники - грани (а1, а2, а3, а4, а5, а6, а7, а8)
GLubyte a1[] = { 0, 1, 2 };
GLubyte a2[] = { 1, 3, 2 };
GLubyte a3[] = { 0, 4, 1 };
GLubyte a4[] = { 1, 4, 3 };
GLubyte a5[] = { 0, 5, 2 };
GLubyte a6[] = { 2, 5, 3 };
GLubyte a7[] = { 0, 5, 4 };
GLubyte a8[] = { 5, 4, 3 };

char title[] = "Oct";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;


void setupPointers(void)
{   //координаты вершин октаэдра; по 3 координаты для каждой вершины
    static GLint vertices[] = { -R, 0, 0,
        0, 0, R,
        0, R, 0,
        R, 0, 0,
        0, -R, 0,
        0, 0, -R };

    static GLfloat colors[] = { 1.0, 0.2, 0.2,
        0.1, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.75, 0.75, 0.75,
        0.35, 0.35, 0.35,
        0.0, 0.0, 1.0 };
    //включение массивов вершины и цвета
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    //указываем размер этих массивов (сколько элементов будет прочитано за один проход)
    glVertexPointer(3, GL_INT, 0, vertices); //3 - потому что 3 координаты для каждой вершины
    glColorPointer(3, GL_FLOAT, 0, colors);
}

void display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(-1.0, -1.0, -3.0);
    //8 вызовов по числу граней (пронумерованы выше)
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a1);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a2);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a4);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a5);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a6);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a7);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, a8);
    glutSwapBuffers();


}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, (GLdouble)w / h, 0.1, -100.0);//насколько широко открыто око камеры (120 градусов)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE); 
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY);
    glutCreateWindow(title);

    setupPointers();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}