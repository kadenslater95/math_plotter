
example: example.c lib2d_plotter.so 2d_plotter.h
	gcc -Wall -o example example.c -lGL -lGLU -lglut -lm -L. -l2d_plotter

lib2d_plotter.so: 2d_plotter.c 2d_plotter.h
	gcc -Wall -shared -o lib2d_plotter.so 2d_plotter.c
