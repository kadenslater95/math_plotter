
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

#include "plotter.h"


// Need this to be able to access constants like M_PI from math.h
#define _USE_MATH_DEFINES

void displayFunc();

double f(double);
double r(double);


void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("OpenGL Template");

    glutDisplayFunc(displayFunc);

    init();
    plInit();

    glutMainLoop();

    return 0;
}


void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);

    plSetColor3f(0.0f, 0.5f, 0.0f);
    plYofX(f);

    plSetColor3f(0.0f, 0.0f, 0.7f);
    plRofTheta(r, 0.0, 10.0*M_PI, 4096);


    glutSwapBuffers();
}


double f(double x) {
    return x*sin(7.0/x) + 4.0;
}


double r(double theta) {
    return cos(1.6*theta) + 1.6;
}
