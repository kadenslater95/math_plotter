
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

    plYofX(f);


    glutSwapBuffers();
}


double f(double x) {
    return x*sin(1.0/x);
}

