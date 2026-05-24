#include <SDL3/SDL.h>
#include "SDL3_image/SDL_image.h"
#include "HCCore/Core/Types.h"
#include "HCEngine/Test.h"

#include <iostream>

#include "HCCore/Core/HString.h"

struct SDLState
{
    SDL_Window* window;
    SDL_Renderer* renderer;
};

void Cleanup(SDLState& state);
HC::HString GetPathInAssets(HC::HString assetsPath);

int main()
{
    HCE::A a;
    a.B();
    
    SDLState state;
    
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL could not initialize", nullptr);
        return -1;
    }
    
    i32 width = 800;
    i32 height = 600;
    state.window = SDL_CreateWindow("HCGame", width, height, SDL_WINDOW_RESIZABLE);
    
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
    
    i32 logicalWidth = 640;
    i32 logicalHeight = 320;
    SDL_SetRenderLogicalPresentation(state.renderer, logicalWidth, logicalHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    
    SDL_Texture* playerTexture = IMG_LoadTexture(state.renderer, GetPathInAssets("player.png").Get());
    SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);
    
    
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
                
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    width = event.window.data1;
                    height = event.window.data2;
                    break;
                }
            }
        }
        
        SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
        SDL_RenderClear(state.renderer);
        
        SDL_FRect src { 0,0,48,48};
        SDL_FRect dest {0,0,48,48};
        
        SDL_RenderTexture(state.renderer, playerTexture, &src, &dest);
        
        SDL_RenderPresent(state.renderer);
    }
    
    SDL_DestroyTexture(playerTexture);
    Cleanup(state);

    return 0;
}

void Cleanup(SDLState& state)
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

HC::HString GetPathInAssets(HC::HString assetsPath)
{
    char buff[256]{};
    sprintf_s(buff, "%s%s", "Z:/Dev/Personal/sdl-test/assets/", assetsPath.Get());
    return buff;
}
