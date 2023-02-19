#include "../../headers/base/window.h"

Window *createWindow() {
    Window *window = malloc(sizeof(Window));
    window->window = SDL_CreateWindow("GamePlate V1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window->window == NULL) {
        printf("Window could not be created ->SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
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

void destroyWindow(Window *window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_FreeSurface(window->screen);
    SDL_DestroyWindow(window->window);
    free(window);
}

void updateWindow(Window *window) {
    SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
}

int mousePositionMainMenu(SDL_Event e){
	e.motion.x;
	e.motion.y;

	if(e.button.x > 320 && e.button.x < 485 && e.button.y > 170 && e.button.y < 190 ){
		return 1;
	} else {
		if(e.button.x > 355 && e.button.x < 450 && e.button.y > 213 && e.button.y < 232 ){
			return 2;
		} else {
			if(e.button.x > 325 && e.button.x < 480 && e.button.y > 257 && e.button.y < 278 ){
				return 3;
			} else {
				return 0;
			}
		}
	}
}

int mouseClickMainMenu(SDL_Event e){
	e.button.x;
	e.button.y;

	if(e.button.x > 320 && e.button.x < 485 && e.button.y > 170 && e.button.y < 190 ){
		return 1;
	} else {
		if(e.button.x > 355 && e.button.x < 450 && e.button.y > 213 && e.button.y < 232 ){
			return 2;
		} else {
			if(e.button.x > 325 && e.button.x < 480 && e.button.y > 257 && e.button.y < 278 ){
				return 3;
			} else {
				return 0;
			}
		}
	}
}

void displayMainMenu(int choice, Window *window) {
	SDL_Surface *startScreen;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_Surface *windowMenu = SDL_GetWindowSurface(window->window);
	printf("là 1");
	switch (choice) {
		case 1: //Jeu de dame
			startScreen = SDL_LoadBMP("./assets/main_menu_checkers_selected.bmp"); 
			if (startScreen == 0 || startScreen == NULL) {
				printf("ça a pas marché : %s", SDL_GetError());
				exit(-1);
			}
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			if(SDL_UpdateWindowSurface(window->window) != 0) {
				printf("Surface could not be updated -> SDL_Error: %s", SDL_GetError());
				exit(-1);
			}
			break;
		case 2: //Morpion
			startScreen = SDL_LoadBMP("./assets/main_menu_morpion_selected.bmp"); 
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
        case 3: //Puissance 4
			startScreen = SDL_LoadBMP("./assets/main_menu_puis4_selected.bmp"); 
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			SDL_UpdateWindowSurface(window->window);
			break;    
		case 4: //Quit
			startScreen = SDL_LoadBMP("./assets/main_menu_quit.bmp"); 
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
		default: // Neutre
			startScreen = SDL_LoadBMP("./assets/main_menu_neutral.bmp"); //neutral menu
			if (startScreen == 0 || startScreen == NULL) {
				printf("ça a pas marché : %s", SDL_GetError());
				exit(-1);
			}
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			if(SDL_UpdateWindowSurface(window->window) != 0) {
				printf("Surface could not be updated -> SDL_Error: %s", SDL_GetError());
				exit(-1);
			}
			break;
	}
}