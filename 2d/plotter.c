
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

#include "plotter.h"


#define _USE_MATH_DEFINES


typedef struct {
  double x_min;
  double x_max;
  double x_scale;

  double y_min;
  double y_max;
  double y_scale;
} _BOUNDING_BOX;


void _mouseFunc(int, int, int, int);
void _motionFunc(int, int);


GLint _viewport[4];

_BOUNDING_BOX _boundingBox;

int _plotter_error = PLOTTER_NO_ERROR;
int _plotter_warning = PLOTTER_NO_WARNING;

double _boundClosenessLimit = 0.000001;

int _mousedown_x, _mousedown_y;

float _red = 0.7f;
float _green = 0.0f;
float _blue = 0.0f;


int plGetError() {
  return _plotter_error;
}


int _validateInit() {
  if ( !(_boundingBox.x_scale > 0.0 || _boundingBox.y_scale > 0.0) ) {
    return 0;
  }

  return 1;
}


void plInit() {
  // If it has already been called, then just return early
  if ( _validateInit() ) {
    return;
  }

  plBoundingBox(
    -2.0*M_PI,  // x_min
    2.0*M_PI,   // x_max
    50.0,       // x_scale
    -2.0*M_PI,  // y_min
    2.0*M_PI,   // y_max
    50.0        // y_scale
  );

  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

  glEnable(GL_MULTISAMPLE);
  glSampleCoverage(1.0f, GL_FALSE);

  // glLineWidth(3.0f);
  glLineWidth(2.0f);

  glutMouseFunc(_mouseFunc);
  glutMotionFunc(_motionFunc);

  glColor3f(_red, _green, _blue);
}


double plGetBoundClosenessLimit() {
  return _boundClosenessLimit;
}


void plSetBoundClosenessLimit(double limit) {
  if ( limit <= 0.0 || limit >= 1.0 ) {
    _plotter_error = PLOTTER_BOUND_CLOSENESS_LIMIT_ERROR;
    perror("Plotter Error (plSetBoundClosenessLimit): Invalid argument provided, limit must be positive a value less than 1.0.\n");
    return;
  }

  _boundClosenessLimit = limit;
}


void plSetColor3f(float red, float green, float blue) {
  if ( red < 0.0f ) {
    _red = 0.0f;
  } else if ( red > 1.0f ) {
    _red = 1.0f;
  } else {
    _red = red;
  }

  if ( green < 0.0f ) {
    _green = 0.0f;
  } else if ( green > 1.0f ) {
    _green = 1.0f;
  } else {
    _green = green;
  }

  if ( blue < 0.0f ) {
    _blue = 0.0f;
  } else if ( blue > 1.0f ) {
    _blue = 1.0f;
  } else {
    _blue = blue;
  }
}


void plBoundingBox(double x_min, double x_max, double x_scale, double y_min, double y_max, double y_scale) {
  if ( x_scale <= 0.0 || y_scale <= 0.0 ) {
    _plotter_error = PLOTTER_BOUNDING_BOX_ERROR;
    perror("Plotter Error (plBoundingBox): Invalid arguments provided, x_scale and y_scale must be positive values.\n");
    return;
  }

  if ( x_min > x_max || y_min > y_max ) {
    _plotter_error = PLOTTER_BOUNDING_BOX_ERROR;
    perror("Plotter Error (plBoundingBox): Invalid arguments provided, (x_min > x_max) and/or (y_min > y_max).\n");
    return;
  }

  if( x_max - x_min < _boundClosenessLimit || y_max - y_min < _boundClosenessLimit ) {
    _plotter_warning = PLOTTER_BOUNDING_BOX_WARNING;
    perror("Plotter Warning (plBoundingBox): (x_min and x_max) and/or (y_min and y_max) have reached the allowed limit of closeness of (currnet value of plGetBoundClosenessLimit).\n");
    return;
  }

  _boundingBox.x_min = x_min;
  _boundingBox.x_max = x_max;
  _boundingBox.x_scale = x_scale;

  _boundingBox.y_min = y_min;
  _boundingBox.y_max = y_max;
  _boundingBox.y_scale = y_scale;
}


void plHome() {
  plBoundingBox(
    -2.0*M_PI,  // x_min
    2.0*M_PI,   // x_max
    50.0,       // x_scale
    -2.0*M_PI,  // y_min
    2.0*M_PI,   // y_max
    50.0        // y_scale
  );
}


void plPlot(coordinate *coords, int size) {
  if ( !_validateInit() ) {
    _plotter_error = PLOTTER_INIT_ERROR;
    perror("Plotter Error (plPlot): You didn't call plInit to setup the plotter.\n");
    return;
  }

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

  glColor3f(_red, _green, _blue);

  glBegin(GL_LINE_STRIP);
    for(int i = 0; i < size; i++) {
      // Transform to Viewport world x and y
      x = (coords[i].x - _boundingBox.x_min) / (_boundingBox.x_max - _boundingBox.x_min) * _viewport[2];
      y = (coords[i].y - _boundingBox.y_min) / (_boundingBox.y_max - _boundingBox.y_min) * _viewport[3];

      glVertex2d(x, y);
    }
  glEnd();
}


void plYofX( double (*f)(double) ) {
  int size = 4096;
  double step = (_boundingBox.x_max - _boundingBox.x_min) / size; // diff of right and left bounds of interval divided by size

  coordinate coords[size];

  for(int i = 0; i < size; i++) {
      coords[i].x = _boundingBox.x_min + i*step;
      coords[i].y = f(coords[i].x);
  }

  plPlot(coords, size);
}


void plRofTheta( double (*r)(double), double theta_min, double theta_max, int size ) {
  double step = (theta_max - theta_min) / size; // diff of right and left bounds of interval divided by size
  double theta = theta_min;

  coordinate coords[size];

  for(int i = 0; i < size; i++) {
      theta = theta_min + i*step;

      coords[i].x = r(theta) * cos(theta);
      coords[i].y = r(theta) * sin(theta);
  }

  plPlot(coords, size);
}


void _mouseFunc(int button, int state, int x, int y) {
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    _mousedown_x = x;
    _mousedown_y = y;
  } else if ( button == 3 || button == 4 ) {
    double scaleFactor = 0.05;

    if (button == 3) {
      scaleFactor = 1.0 - scaleFactor;
    }else {
      scaleFactor = 1.0 + scaleFactor;
    }

    double x_min = _boundingBox.x_min;
    double x_max = _boundingBox.x_max;
    _boundingBox.x_min = x_min + (1.0 - scaleFactor) * ( x/( (double) _viewport[2] ) ) * ( x_max - x_min );
    _boundingBox.x_max = x_max -  (1.0 - scaleFactor) * (_viewport[2] - x) / ( (double) _viewport[2] ) * ( x_max - x_min );

    double y_min = _boundingBox.y_min;
    double y_max = _boundingBox.y_max;
    _boundingBox.y_min = y_min + (1.0 - scaleFactor) * ( (_viewport[3] - y)/( (double) _viewport[3] ) ) * ( y_max - y_min );
    _boundingBox.y_max = y_max -  (1.0 - scaleFactor) * ( y / ( (double) _viewport[3] ) ) * ( y_max - y_min );


    glutPostRedisplay();
  }
}


void _motionFunc(int x, int y) {
  // Determine what x and y are in terms of normalized coordinates from 0.0 to 1.0 based on viewport width
  // and height proportions, then put those proportions in terms of the bounding box width and height
  double dX = (_boundingBox.x_max - _boundingBox.x_min) * (_mousedown_x - x)/( (double) _viewport[2] );
  double dY = -(_boundingBox.y_max - _boundingBox.y_min) * (_mousedown_y - y)/( (double) _viewport[3] );

  _boundingBox.x_min += dX;
  _boundingBox.x_max += dX;

  _boundingBox.y_min += dY;
  _boundingBox.y_max += dY;

  glutPostRedisplay();

  // Update _mousedown_x and _mousedown_y so that when that stop moving and then start moving again
  // it will base the dX and dY on the current position and not the old initial mouse down position
  _mousedown_x = x;
  _mousedown_y = y;
}
