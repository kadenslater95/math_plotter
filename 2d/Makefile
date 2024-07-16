
main: main.c libplotter.so plotter.h
	gcc -Wall -o main main.c -lGL -lGLU -lglut -lm -L. -lplotter

libplotter.so: plotter.c plotter.h
	gcc -Wall -fPIC -shared -o libplotter.so plotter.c -lGL -lglut
