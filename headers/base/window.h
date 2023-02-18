/**
 * @file window.h
 * @author Melissa GRIES
 * @brief Implementation of the window.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500

/**
 * @brief Stores the main window and the renderer.
 */
typedef struct Window {
    SDL_Window *window;
    SDL_Surface *screen;
    SDL_Renderer *renderer;
} Window;

/**
 * @brief Create the window.
 */
Window *createWindow();

/**
 * @brief Destroy the Window.
 * @param window The Window to destroy.
 */
void destroyWindow(Window *window);

/**
 * @brief Update the Window with a rendering context.
 * @param window The Window to update.
 */
void updateWindow(Window *window);

#endif /* WINDOW_H */