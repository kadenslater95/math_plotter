# math_plotter
Making mathematical graph plotting tool (similar to Desmos 2D and Geogebra 3D) for OpenGL using C/C++.

The 2d and 3d folders are each their own project.

![Screenshot from 2024-07-15 20-46-08](https://github.com/user-attachments/assets/f5514d7d-3e9b-4c9f-a6cf-f6ee88d58f29)


# Requirements
Make sure to have [freeglut](https://freeglut.sourceforge.net/) installed and on your path (you can also get it from your package manager).

Currently this uses a make file so you will want mingw if you are on windows. \
For linux (where it was developed) make sure you have the gnu compiler toolchain. \
For Mac the default clang toolchain will probably work, but otherwise install gnu compiler toolchain.


# Building
Run `make` from the 2d project root.

> **Note** \
> You will need to set the `LD_LIBRARY_PATH` to be able to use the shared library within this folder
>```
> export LD_LIBRARY_PATH="`pwd`;$LD_LIBRARY_PATH"
> ```

## Usage
. . .
