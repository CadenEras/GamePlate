#define SDL_MAIN_HANDLED

#include "headers/Checker/Constructor.h"

int main(int argc, char *argv[]) {
	//Event variable we'll be using
	Constructor *flagged;
	Constructor *previous;
	SDL_Event e;
	//The boolean for the event loop
	bool quit = false;
	
	//Making sure SDL is initialized
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not initialize correctly => SDL_Error: %s\n", SDL_GetError());
	}
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		fprintf(stderr, "SDL_IMG could not initialize correctly => SDL_Error: %s\n", SDL_GetError());
	}
	//Create the render window
	Renderer *window = makeWindow("Gameplate", SCREEN_WIDTH, SCREEN_HEIGHT);
	
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}
	
	//Don't forget to free everything !!
	cleanEverything(window);
	SDL_Quit();
	IMG_Quit();
	
	return 0;
}
