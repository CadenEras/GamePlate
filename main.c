#define SDL_MAIN_HANDLED

#include "headers/Checker/interface.h"

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
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
	window = SDL_CreateWindow("GamePlate", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	
	if (renderer == NULL) {
		fprintf(stderr, "SDL could not create the renderer => SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_CreateRGBSurface(0, 800, 800, 32, 0, 0, 0, 255);
	SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 255, 255, 255, 255));
	initGame(screen, window);
	//Don't forget to free everything !!
	//cleanEverything(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	
	return 0;
}
