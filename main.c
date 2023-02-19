#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/Tic-Tac-Toe/Game.h"
#include "headers/Tic-Tac-Toe/Logic.h"
#include "headers/Tic-Tac-Toe/Rendering.h"
#include "headers/base/window.h"


int main(int argc, char *argv[]) {

	SDL_Surface *screen = NULL;
	
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	//Making sure SDL is initialized
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize correctly => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		fprintf(stderr, "SDL_IMG could not initialize correctly => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//Create the render window
	Window *window = createWindow();
	
	if (window->renderer == NULL) {
		fprintf(stderr, "SDL could not create the renderer => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_CreateRGBSurface(0, 800, 800, 32, 0, 0, 0, 255);

	SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 255, 255, 255, 255));
	SDL_UpdateWindowSurface(window->window);
	main_ttt(window);
	//Don't forget to free everything !!
	//cleanEverything(window);
	destroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	
	return 0;
}