
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <parallel/algorithm>

#include "Screen.h"

using namespace dev;

bool processEvent(SDL_Event &e)
{
    // user requests quit
    if (e.type == SDL_QUIT)
    {
        return false;
    }
    else if (e.type == SDL_KEYDOWN)
    {
        // printf("Pressed key: %d\n", e.key.keysym.sym);
    }
    return true;
}

int main(int argc, char *args[])
{   
    // __gnu_parallel::for_each()
    
    Screen screen(700, 700, "Ants");

    if (!screen.init())
        return 1;

    screen.setEventProcessor(processEvent);

    // Main game loop
    Uint32 prevTime = SDL_GetTicks();
    bool quit = false;
    while (!quit)
    {
        // Timing
        Uint32 curTime = SDL_GetTicks();
        Uint32 elapsed = curTime - prevTime;
        prevTime = curTime;

        // Clear screen
        screen.clear();

        // add render commands here

        // Draw screen
        screen.update();

        quit = !screen.processEvents();
    }
    
    screen.close();

    return 0;
}