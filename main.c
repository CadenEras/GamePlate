#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/Tic-Tac-Toe/Game.h"
#include "headers/Tic-Tac-Toe/Logic.h"
#include "headers/Tic-Tac-Toe/Rendering.h"
#include "headers/base/window.h"

int main(int argc, char *argv[])
{
	SDL_Surface *screen = NULL;
	SDL_Event event;
	int actionMenu = 1;
	int choice = 0;
	int pos = 0;
	int click = 0;
	int mainMenu = 1;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	// Making sure SDL is initialized
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize correctly => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		fprintf(stderr, "SDL_IMG could not initialize correctly => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	// Create the render window
	Window *window = createWindow();

	if (window->renderer == NULL)
	{
		fprintf(stderr, "SDL could not create the renderer => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_CreateRGBSurface(0, 800, 800, 32, 0, 0, 0, 255);

	SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 255, 255, 255, 255));
	SDL_UpdateWindowSurface(window->window);

		displayMainMenu(pos, window);
		while (mainMenu == 1) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
							case SDLK_ESCAPE:
								mainMenu = 0;
								break;
							default:
								break;
						} // Fin switch touche choisi
					case SDL_MOUSEMOTION:
						pos = mousePositionMainMenu(event);
						displayMainMenu(pos, window);
						break;
						// Fin du cas : la souris bouge
					case SDL_MOUSEBUTTONUP:
						switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							click = mouseClickMainMenu(event);
							switch (click) {
								case 1:
									// jeu de dame
									mainMenu = 0;
									break;
								case 2:
									// morpion
									main_ttt(window);
									mainMenu = 0;
									break;
								case 3:
									// Puissance 4
									mainMenu = 0;
									break;
								case 4:
									// Clique sur quitter
									mainMenu = 0;
									actionMenu = 0;
									break;
								default:
									break;
							} // Fin switch click
							break;
						default:
							break;
						} // Fin choix bouton de souris UP
					default:
						break;
				} // Fin switch event.type
			}
		}

	// Don't forget to free everything !!
	destroyWindow(window);
	SDL_Quit();
	IMG_Quit();

	return 0;
}