
#ifndef _2D_PLOTTER_H
#define _2D_PLOTTER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus



typedef struct {
  double x;
  double y;
} coordinate;


typedef enum {
  PLOTTER_NO_ERROR,
  PLOTTER_INIT_ERROR,
  PLOTTER_VIEWPORT_ERROR,
  PLOTTER_BOUNDING_BOX_ERROR,
  PLOTTER_PLOT_ERROR
} PLOTTER_ERROR;


/**
 * Get the current error value, similar to glGetError
 * 
 * @return current PLOTTER_ERROR enum value
*/ 
int plGetError();


/**
 * Set the viewport dimensions
 * 
 * @param width [double] width of the viewport
 * @param height [double] height of the viewport
 * 
 * @return void
*/ 
void plViewportSize(double width, double height);


/**
 * Set the viewport dimensions
 * 
 * @param x_min [double] left bound of visible x-axis
 * @param x_max [double] right bound of visible x-axis
 * @param x_scale [double] zoom factor of x-axis
 * @param y_min [double] bottom bound of visible y-axis
 * @param y_max [double] top bound of visible y-axis
 * @param y_scale [double] zoom factor of y-axis
 * 
 * @return void
*/ 
void plBoundingBox(double x_min, double x_max, double x_scale, double y_min, double y_max, double y_scale);


/**
 * Given Math World coordinates to plot, determines there viewport coordinates and draws a GL_LINE_STRIP
 * with them
 * 
 * @param coords [coordinate *] pointer to first coordinate in an array of coordinates
 * @param size [int] number of coordinates in array
 * 
 * @return void
*/ 
void plPlot(coordinate *coords, int size);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _2D_PLOTTER_H
