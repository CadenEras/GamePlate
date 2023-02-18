#include "../../headers/base/window.h"

Window *createWindow() {
    Window *window = malloc(sizeof(Window));
    window->window = SDL_CreateWindow("SDL_TP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window->window == NULL)
    {
        printf("Window could not be created ->SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL)
    {
        printf("Renderer could not be created -> SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window->window);
        SDL_Quit();
        exit(-1);
    }

    SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);

    return window;

}

void destroy_window(Window *window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window);
}