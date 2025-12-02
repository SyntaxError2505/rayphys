#include "raylib.h"
#include "engine/engine.h"

int main(void)
{
    //quick initializations
    init();

    //game loop inside run
    run();

    //delete the window and let raylib do some work
    quit();

    return 0;
}