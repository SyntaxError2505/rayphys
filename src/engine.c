#include "engine/engine.h"

// #define WINDOW_WIDTH 800
// #define WINDOW_HEIGTH 500

#define CIRCLE_RADIUS 50
#define GRAVITY -981.0
#define MAX_INIT_CIRCLES 100
//#define MAX_CIRCLES 10000 NOT IMPLEMENTED
#define ELASTICITY 0.9
#define FLOOR_FRICTION 0.9

// Ball System
ball_system* create_ball_system(int capacity){
    ball_system* sys = malloc(sizeof(ball_system));
    sys->capacity = capacity;
    sys->count = 0;
    sys->x = malloc(sys->capacity*sizeof(float));
    sys->y = malloc(sys->capacity*sizeof(float));
    sys->vx = malloc(sys->capacity*sizeof(float));
    sys->vy = malloc(sys->capacity*sizeof(float));

    return sys;
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
    for(int i = 0; i < sys->count; i++){
        sys->vy[i] -= GRAVITY * GetFrameTime();
    }

    //move according to speeds
    for(int i = 0; i < sys->count; i++){
        sys->x[i] += sys->vx[i] * GetFrameTime();
        sys->y[i] += sys->vy[i] * GetFrameTime();
    }

    //check and resolve collision
    for (int i = 0; i < sys->count; i++) {
        //check floor collision
        if(sys->y[i] > GetScreenHeight() - CIRCLE_RADIUS){
            sys->y[i] = GetScreenHeight() - CIRCLE_RADIUS;
            sys->vy[i] = (sys->vy[i] * - 1) * ELASTICITY;
            sys->vx[i] *= FLOOR_FRICTION;
        }

        //check left collision
        if(sys->x[i] < CIRCLE_RADIUS){
            sys->x[i] = CIRCLE_RADIUS;
            sys->vx[i] = (sys->vx[i] * - 1) * ELASTICITY;
        }

        //check right collision
        if(sys->x[i] > GetScreenWidth() - CIRCLE_RADIUS){
            sys->x[i] = GetScreenWidth() - CIRCLE_RADIUS;
            sys->vx[i] = (sys->vx[i] * - 1) * ELASTICITY;
        }

        //check circle to circle collision
        for (int j = i + 1; j < sys->count; j++) {
            if(!(i == j)){
                float dx = sys->x[i] - sys->x[j];
                float dy = sys->y[i] - sys->y[j];
                float dist = sqrtf(dx*dx + dy*dy);

                if(dist < CIRCLE_RADIUS*2){

                    if(dist == 0.0f){dist = 0.001f;}

                    float nx = dx / dist;
                    float ny = dy / dist;

                    // --- 2. Push circles apart ---
                    float overlap = (CIRCLE_RADIUS * 2.0f) - dist;
                    float push = overlap * 0.5f;

                    sys->x[i] += nx * push;
                    sys->y[i] += ny * push;

                    sys->x[j] -= nx * push;
                    sys->y[j] -= ny * push;

                    // --- 3. Velocity response using ELASTICITY ---

                    // Project velocities onto collision normal
                    float vi = sys->vx[i] * nx + sys->vy[i] * ny;
                    float vj = sys->vx[j] * nx + sys->vy[j] * ny;

                    // Compute new normal components after collision
                    float vi_after = vj * ELASTICITY;   // swap, scaled by elasticity
                    float vj_after = vi * ELASTICITY;

                    // Change in normal velocity
                    float dvi = vi_after - vi;
                    float dvj = vj_after - vj;

                    // Apply to full velocity vectors
                    sys->vx[i] += dvi * nx;
                    sys->vy[i] += dvi * ny;

                    sys->vx[j] += dvj * nx;
                    sys->vy[j] += dvj * ny;
                }
            }
        }
    }
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
    SetTargetFPS(60);
}

void run(void){
    ball_system* balls = create_ball_system(MAX_INIT_CIRCLES);

    add_ball(balls, 100, 0, 0, 0);
    add_ball(balls, 150, 100, 0, 0);

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            render_ball_system(balls);
            update_ball_system(balls);

            DrawText(TextFormat("FPS: %i", GetFPS()), 40, 40, 40, GRAY);
            DrawText(TextFormat("Ballcount: %i", (int)balls->count), 40, 80, 40, GRAY);
        EndDrawing();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            add_ball(balls, GetMousePosition().x, GetMousePosition().y, 0, 0);
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            add_ball(balls, GetMousePosition().x, GetMousePosition().y, 0, 0);
        }
        if(IsKeyPressed(KEY_R)){
            balls->count = 0;
            balls->capacity = MAX_INIT_CIRCLES;
        }
    }

    destroy_ball_system(balls);
}

void quit(void){
    CloseWindow();
}