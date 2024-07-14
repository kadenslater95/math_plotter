
#include <GL/gl.h>
#include <stdio.h>

#include "plotter.h"


typedef struct {
  double x_min;
  double x_max;
  double x_scale;

  double y_min;
  double y_max;
  double y_scale;
} _BOUNDING_BOX;


GLint _viewport[4];
_BOUNDING_BOX _boundingBox;
int _plotter_error = PLOTTER_NO_ERROR;


int plGetError() {
  return _plotter_error;
}


void plBoundingBox(double x_min, double x_max, double x_scale, double y_min, double y_max, double y_scale) {
  if ( x_scale <= 0.0 || y_scale <= 0.0 ) {
    _plotter_error = PLOTTER_BOUNDING_BOX_ERROR;
    perror("Plotter Error (plBoundingBox): Invalid arguments provided, x_scale and y_scale must be positive values.\n");
    return;
  }

  _boundingBox.x_min = x_min;
  _boundingBox.x_max = x_max;
  _boundingBox.x_scale = x_scale;

  _boundingBox.y_min = y_min;
  _boundingBox.y_max = y_max;
  _boundingBox.y_scale = y_scale;
}


void plPlot(coordinate *coords, int size) {
  if (!coords) {
    _plotter_error = PLOTTER_PLOT_ERROR;
    perror("Plotter Error (plPlot): Invalid coordinates provided, must be a valid pointer to a coordinate array.\n");
    return;
  }
  if (!size) {
    _plotter_error = PLOTTER_PLOT_ERROR;
    perror("Plotter Error (plPlot): Invalid size provided, must be an positive integer.\n");
    return; 
  }

  double x, y;

  glGetIntegerv(GL_VIEWPORT, _viewport);

  glBegin(GL_LINE_STRIP);
    for(int i = 0; i < size; i++) {
      // Transform to Viewport world x and y
      x = (coords[i].x - _boundingBox.x_min) / (_boundingBox.x_max - _boundingBox.x_min) * _viewport[2];
      y = (coords[i].y - _boundingBox.y_min) / (_boundingBox.y_max - _boundingBox.y_min) * _viewport[3];

      glVertex2d(x, y);
    }
  glEnd();
}
