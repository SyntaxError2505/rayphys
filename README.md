# rayphys 0.3.0
A physics engine using raylib in C designed purely to ragebait my Zig-friend

# Requirements
```
An instalation of raylib
An OS/WM that raylib supports (make sure to read their documentation)
CMake 3.14+
a C compiler (gcc recomended)
```

# Building
```
mkdir build && cd build
cmake .. # Make sure to pick the right generator using the -G flag like -G"generator"
cmake --build .
```

# How to use
start up the generated executable. You will see a white screen (with some circles). Press M1 to spawn one and press M2 to spawn one per Frame. Reset with R

# Roadmap
```
Window
Circle Rendering
Gravity
Circle Collision
Cube Rendering (planned)
Cube Collision (planned)
Image Rendering (planned)
Sounds (planned)
---------Release 1.0----------
```