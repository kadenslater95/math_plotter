
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
  PLOTTER_BOUND_CLOSENESS_LIMIT_ERROR,
  PLOTTER_BOUNDING_BOX_ERROR,
  PLOTTER_PLOT_ERROR
} PLOTTER_ERROR;

typedef enum {
  PLOTTER_NO_WARNING,
  PLOTTER_BOUNDING_BOX_WARNING
} PLOTTER_WARNING;


/**
 * Get the current error value, similar to glGetError
 * 
 * @return current PLOTTER_ERROR enum value
*/ 
int plGetError();


/**
 * Initialize the plotter, must be called once at the beginning of the code before using the library
 * 
 * @return void
*/
void plInit();


/**
 * Get the current bound closeness limit (default is 0.000001).
 * When the x_max - x_min (or y_max - y_min) are smaller than this limit they are considered to be equal
 * 
 * @return limit [double] the double that determines when the bounds are considered equal
*/
double plGetBoundClosenessLimit();


/**
 * Set the current bound closeness limit.
 * When the x_max - x_min (or y_max - y_min) are smaller than this limit they are considered to be equal
 * 
 * @param limit [double] the double that determines when the bounds are considered equal
 * 
 * @return void
*/
void plSetBoundClosenessLimit(double limit);


/**
 * Initialize the plotter, must be called once at the beginning of the code before using the library
 * 
 * @return void
*/
void plInit();


/**
 * Set the viewport dimensions
 * 
 * @param x_min [double] left bound of visible x-axis
 * @param x_max [double] right bound of visible x-axis
 * @param x_scale [double] used to determine gridlines of x-axis
 * @param y_min [double] bottom bound of visible y-axis
 * @param y_max [double] top bound of visible y-axis
 * @param y_scale [double] used to determine gridlines of y-axis
 * 
 * @return void
*/ 
void plBoundingBox(double x_min, double x_max, double x_scale, double y_min, double y_max, double y_scale);


/**
 * Given a pointer to a function f that outputs y given x, this will plot that function within
 * the current Bounding Box state of the plotter
 * 
 * @param f [function *] pointer to function that outputs y given x
 * 
 * @return void
*/ 
void plYofX( double (*f)(double) );


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
