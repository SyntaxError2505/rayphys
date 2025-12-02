#include "engine/engine.h"

// #define WINDOW_WIDTH 800
// #define WINDOW_HEIGTH 500

#define CIRCLE_RADIUS 50
#define GRAVITY 981f
#define MAX_INIT_CIRCLES 100
#define MAX_CIRCLES 10000

// Ball System
ball_system* create_ball_system(int capacity){
    ball_system* sys = malloc(sizeof(ball_system));
    sys->capacity = capacity;
    sys->count = 0;
    sys->x = malloc(sys->count*sizeof(int));
    sys->y = malloc(sys->count*sizeof(int));
    sys->vx = malloc(sys->count*sizeof(float));
    sys->vy = malloc(sys->count*sizeof(float));
}

void add_ball(ball_system* sys, int x, int y, float vx, float vy){
    if(sys->count >= sys->capacity){
        sys->capacity *= 2;
        sys->x = realloc(sys->x, sys->capacity * sizeof(float));
        sys->y = realloc(sys->y, sys->capacity * sizeof(float));
        sys->vx = realloc(sys->vx, sys->capacity * sizeof(float));
        sys->vy = realloc(sys->vy, sys->capacity * sizeof(float));
    }

    //current I is always empty, I - 1 is the last created Ball
    int i = sys->count;
    sys->x[i] = x;
    sys->y[i] = y;
    sys->vx[i] = vx;
    sys->vy[i] = vy;
    sys->count++;
}

void render_ball_system(ball_system* sys){
    for(int i = 0; i < sys->count; i++){
        int current = i;
        
        DrawCircle(sys->x[current], sys->y[current], CIRCLE_RADIUS, RED);
    }
}

void update_ball_system(ball_system* sys){
    
}

void destroy_ball_system(ball_system* sys){
    free(sys->x);
    free(sys->y);
    free(sys->vx);
    free(sys->vy);
    free(sys);
}

//Functions for main.c
void init(void){
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Rayphys");
}

void run(void){
    ball_system* balls = create_ball_system(MAX_INIT_CIRCLES);

    add_ball(balls, 0, 0, 0, 0);
    add_ball(balls, 100, 100, 0, 0);

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            render_ball_system(balls);
        EndDrawing();
    }

    destroy_ball_system(balls);
}

void quit(void){
    CloseWindow();
}