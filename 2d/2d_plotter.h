
#ifndef _PLOTTER_H
#define _PLOTTER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


typedef struct {
  double x;
  double y;
} coordinate;


/**
 * Given Math World coordinates to plot, determines there viewport coordinates and draws a GL_LINE_STRIP
 * with them
 * 
 * @param coords [coordinate *] pointer to first coordinate in an array of coordinates
 * @param size [int] number of coordinates in array
 * 
 * @return void
*/ 
void plot(coordinate *coords, int size);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _PLOTTER_H
