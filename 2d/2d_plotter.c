
#include <GL/gl.h>
#include <stdio.h>

#include "2d_plotter.h"


typedef struct {
  double x_min;
  double x_max;
  double x_scale;

  double y_min;
  double y_max;
  double y_scale;
} bounding_box;

typedef struct {
  double width;
  double height;
} viewport;


void plot(coordinate *coords, int size) {
  if (!coords) {
    perror("Plotter Error (plot): invalid coordinates provided, must be a valid pointer to a coordinate array.");
  }
  if (!size) {
    perror("Plotter Error (plot): invalid size provided, must be an positive integer.");
  }

  glBegin(GL_LINE_STRIP);
    for(int i = 0; i < size; i++) {
      glVertex2d(coords[i].x, coords[i].y);
    }
  glEnd();
}
