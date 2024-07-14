
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
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

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("OpenGL Template");

    glutDisplayFunc(displayFunc);

    init();

    printf("\n__STDC_VERSION__: %ld\n", __STDC_VERSION__);
    printf("M_PI: %lf\n\n", M_PI);

    glutMainLoop();

    return 0;
}


void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);

    // TODO: Distinguish the Graph Coordinates from the Plot Coordinates
    // Currently I am just using Plot Coordinates for everything.
    // I need to instead be able to give arbitrary Bounding Box values, and
    // determine Plot Coordinates for f in an interval based on that Bounding Box.
    // The Bounding Box will have an x-scale, y-scale, x-min, x-max, y-min, y-max, ... 

    // Zoomed Out Plot
    // int size = 100;
    // double step = 50.0/size;
    // coordinate coords[size];
    // for(int i = 0; i < size; i++) {
    //     coords[i].x = 150.0 + i*step;
    //     coords[i].y = 150.0 + 25.0*f(0.25*coords[i].x);
    // }

    // plot(coords, size);

    // // Zoomed Out Reference Line
    // glBegin(GL_LINES);
    //     glVertex2d(150.0, 150.0);
    //     glVertex2d(200.0, 150.0);
    // glEnd();


    // Zoomed in Plot
    // Plot from pi/2-4pi/9 to pi/2+4pi/9
    // First get coords in math world
    // Then transform those coords into plot world
    // int size2 = 100;
    // double step2 = (8.0*M_PI/9.0) / size2; // diff of right and left bounds of interval divided by size
    // coordinate coords2[size2];
    // for(int i = 0; i < size2; i++) {
    //     // Determine Math world x and y
    //     coords2[i].x = (M_PI/2.0 - 4.0*M_PI/9.0) + i*step2;
    //     coords2[i].y = f(coords2[i].x);

    //     // Now transform to Viewport world x and y
    //     coords2[i].x = 320.0 + 25.0*coords2[i].x;
    //     coords2[i].y = 240.0 + 150.0*coords2[i].y;
    // }

    // plot(coords2, size2);


    int size3 = 100;
    double step3 = (8.0*M_PI/9.0) / size3; // diff of right and left bounds of interval divided by size
    coordinate coords3[size3];
    for(int i = 0; i < size3; i++) {
        coords3[i].x = (M_PI/2.0 - 4.0*M_PI/9.0) + i*step3;
        coords3[i].y = f(coords3[i].x);
    }

    double x_min = M_PI/2.0 - 4.0*M_PI/9.0;
    double x_max = M_PI/2.0 + 4.0*M_PI/9.0;
    double x_scale = 50.0;
    double y_min = -2.0;
    double y_max = 2.0;
    double y_scale = 50.0;
    plBoundingBox(x_min, x_max, x_scale, y_min, y_max, y_scale);
    plPlot(coords3, size3);


    glFlush();
}


double f(double x) {
    return sin(x);
}

