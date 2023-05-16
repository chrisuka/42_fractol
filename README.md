# Fract'ol
A CPU-based [fractal](https://en.wikipedia.org/wiki/Fractal) renderer for [Hive](https://hive.fi/en/).
Written in C on top of MiniLibX, the school's own X11 library.
The goal of this project was to have a graphical program displaying different complex sets, such as Mandelbrot and Julia.

## Introduction
We represent the screen as a 2D complex plane, where the X-axis represents real values and Y-axis represents imaginary values.
For each point (pixel), we can apply a repeating complex function, which will move the point on the complex plane. The function is exponential so
successive iterations will have greater effect if the initial point is shifted further from the center. After enough iterations,
some points will escape ever further, reaching towards infinity, whereas some points will stay within a limited area forever.
These latter points represent the complex set, such as the Mandelbrot Set.

We render each pixel a different color based on how many iterations it took for it to escape. We have an arbitrary MAX_DEPTH to prevent the program
from freezing during calculation. We use this value for any point inside the set.
In practise this gives us mesmerizing self-similar shapes you can zoom into "infinitely" (though computer limitations get in the way).

![Mandelbrot Set](/resources/pics/mandelbrot.png)

## Features
* Mandelbrot, Julia, Tricorn, Burning Ship
* Pan
* Zoom
* Adjusting the constant value of the Julia Set with cursor
* Periodicity
* BSP scan optimization ([Mariani-Silver](https://www.mrob.com/pub/muency/marianisilveralgorithm.html))
* Debug view (visualizes rectangle scan-depths per pixel)

Multithreading and adaptive depth were also planned, but ultimately scrapped.

## Install
Note: currently only supports MacOS! Prerequisites are `clang` and `make`.

`cd` into the root of the repository and run `make`. For convenience there are also:
* `make W` for stricter rules
* `make O` for speed optimization (-O3)
* `make D` for a debug build

