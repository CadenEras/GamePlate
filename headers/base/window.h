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

/**
 * @brief Display Main Checker menu.
 * @param choice Choice from the Main Checker menu.
 */
void displayMainCheckerMenu(int choice, Window *window);

/**
 * @brief Calcule la position de la mouse a chaque mouvement
 * @return int Un entier representant une position dans le menu pause.
 */
int mousePositionMainMenu(SDL_Event e);

/**
 * @brief Calcule la position de la mouse a chaque click dans le menu principal.
 * @return int Un entier representant un choice dans le menu principal.
 */
int mouseClickMainMenu(SDL_Event e);

/**
 * @brief Display Main Checker menu.
 * @param choice Choice from the Main Checker menu.
 */
void displayMainMenu(int choice, Window *window);


/**
 * @brief Calcule la position de la mouse a chaque mouvement
 * @return int Un entier representant une position dans le menu pause.
 */
int mousePositionEndTTT(SDL_Event e);

/**
 * @brief Calcule la position de la mouse a chaque click dans le menu principal.
 * @return int Un entier representant un choice dans le menu principal.
 */
int mouseClickEndTTT(SDL_Event e);


#endif /* WINDOW_H */