# pge

Predictive Game Engine.  This is a physics engine which can coexist
with PyGame or run in batch mode with Python.  It is implemented in
Modula-2, C++, Python and maxima.  Internally it predicts the time
of next collision rather than test for a collision every frame.

# Building

```console
$ git clone https://github.com/gaiusm/pge
$ cd pge
$ mkdir build
$ cd build
$ ../configure
$ make
```

# Running

```console
$ ./localrun.sh ../examples/breakout/breakout.py
```

# Install

```console
$ make install
```