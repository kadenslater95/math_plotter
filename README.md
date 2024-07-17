# math_plotter
Making mathematical graph plotting tool (similar to Desmos 2D and Geogebra 3D) for OpenGL using C/C++.

The 2d and 3d folders are each their own project.

[Screencast from 07-17-2024 08:36:16 AM.webm](https://github.com/user-attachments/assets/06dfe185-a34b-47c7-b5bf-4e79c50b53e4)



# Requirements
Make sure to have [freeglut](https://freeglut.sourceforge.net/) installed and on your path (you can also get it from your package manager).

Currently this uses a make file so you will want mingw if you are on windows. \
For linux (where it was developed) make sure you have the gnu compiler toolchain. \
For Mac the default clang toolchain will probably work, but otherwise install gnu compiler toolchain.


# Building
Run `make` from the 2d project root.

> **Note** \
> You will need to set the `LD_LIBRARY_PATH` to be able to use the shared library within this folder, so from the 2d folder execute this command:
>```
> export LD_LIBRARY_PATH="`pwd`;$LD_LIBRARY_PATH"
> ```

## Usage
. . .
