#ifndef RAYPHYS_ENGINE
#define RAYPHYS_ENGINE

#include "raylib/raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef struct{
    float* x;
    float* y;
    float* vx;
    float* vy;
    size_t count;
    size_t capacity;
} ball_system;

void init(void);
void run(void);
void quit(void);

ball_system* create_ball_system(int capacity);
void render_ball_system(ball_system* sys);
void add_ball(ball_system* sys, int x, int y, float vx, float vy);
void destroy_ball_system(ball_system* sys);

#endif