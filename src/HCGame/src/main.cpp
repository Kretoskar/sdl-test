#include <SDL3/SDL.h>
#include "SDL3_image/SDL_image.h"
#include "HCCore/Core/Types.h"

#include <iostream>

struct SDLState
{
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void Cleanup(SDLState& state);

int main()
{
    SDLState state;
    
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL could not initialize", nullptr);
        return -1;
    }
    
    i32 width = 800;
    i32 height = 600;
    state.window = SDL_CreateWindow("HCGame", width, height, 0);
    
    if (!state.window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", state.window);
        Cleanup(state);
        return -1;
    }
    
    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    if (!state.renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating renderer", state.window);
        Cleanup(state);
        return -1;
    }
    
    bool running = true;
    while (running)
    {
        SDL_Event event {0};
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                {
                    running = false;
                    break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(state.renderer, 123, 21, 67, 255);
        SDL_RenderClear(state.renderer);
        
        SDL_RenderPresent(state.renderer);
    }
    
    Cleanup(state);

    return 0;
}

void Cleanup(SDLState& state)
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}