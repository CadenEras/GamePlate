// Created by Melissa Gries

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct Window {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Window;

Window *createWindow();
void destroyWindow(Window *window);

#endif