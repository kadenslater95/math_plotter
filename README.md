# math_plotter
Making mathematical graph plotting libraries for OpenGL using C/C++.

The 2d and 3d folders are each their own project.

# Building
Run `make` from the 2d project root.

> **Note** \
> You will need to set the `LD_LIBRARY_PATH` to be able to use the shared library within this folder
>```
> export LD_LIBRARY_PATH="`pwd`;$LD_LIBRARY_PATH"
> ```

## Usage
The 2d library assumes you are using the fixed function pipeline and have called glOrtho2d with the values going from 0 to Viewport Width in the X, and 0 to Viewport Height in the Y, similar to the following:
```
gluOrtho2D(0.0, viewportWidth, 0.0, viewportHeight);
```
. . .
