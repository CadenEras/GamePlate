/**
 * \file window.h
 * \author Melissa GRIES
 * \brief Implementation of the window.
 */

#ifndef WINDOW_H
#define WINDOW_H

#pragma once

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500

/**
 * \fn typedef struct Window
 * \brief Stores the main window and the renderer.
 */
typedef struct Window {
    SDL_Window *window;
    SDL_Surface *screen;
    SDL_Renderer *renderer;
} Window;

/**
 * \fn Window *createWindow()
 * \brief Create the window.
 */
Window *createWindow();

/**
 * \fn void destroyWindow(Window *window)
 * \brief Destroy the Window.
 * \param window The Window to destroy.
 */
void destroyWindow(Window *window);

#endif /* WINDOW_H */