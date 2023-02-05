//
// Created by gries on 16/12/2022.
//

#include "../../headers/Checker/interface.h"

void printBoard(SDL_Surface *screen, GridType grid[][8]) {
	SDL_Texture *square[8] = {NULL};
	SDL_Texture *whiteElipse = NULL;
	SDL_Texture *redElipse = NULL;
	SDL_Rect position;
	int squareColor = 1;
	
	for (int i = 0; i < 8; ++i) {
		square[i] = SDL_CreateTexture((SDL_Renderer *) screen, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
	}
	
	position.x = 0;
	position.y = 0;
	
	for (int i = 0; i < SQUARE_NUMBER; ++i) {
		for (int j = 0; j < SQUARE_NUMBER; ++j) {
			position.x = j * 100;
			
			if (squareColor == RED) {
				SDL_SetRenderDrawColor((SDL_Renderer *) screen, 255, 0, 0, 255);
			} else {
				SDL_SetRenderDrawColor((SDL_Renderer *) screen, 255, 255, 255, 255);
			}
			SDL_RenderFillRect((SDL_Renderer *) screen, &position);
			squareColor = -squareColor;
		}
		squareColor = -squareColor;
		position.y += 100;
	}
	
	whiteElipse = IMG_LoadTexture((SDL_Renderer *) screen, "../../assets/Checker/whiteElipse.png");
	redElipse = IMG_LoadTexture((SDL_Renderer *) screen, "../../assets/Checker/redElipse.png");
	
	for (int i = 0; i < SQUARE_NUMBER; ++i) {
		for (int j = 0; j < SQUARE_NUMBER; ++j) {
			position.x = j * 100;
			position.y = i * 100;
			
			if (grid[i][j].state == FULL && grid[i][j].color == WHITE) {
				SDL_RenderCopy((SDL_Renderer *) screen, whiteElipse, NULL, &position);
			} else if (grid[i][j].state == RED && grid[i][j].color == RED) {
				SDL_RenderCopy((SDL_Renderer *) screen, redElipse, NULL, &position);
			}
		}
	}
	SDL_RenderPresent((SDL_Renderer *) screen);
}

void initBoard(GridType grid[][8]) {
	int blit = -1;
	
	for (int i = 0; i < SQUARE_NUMBER; ++i) {
		for (int j = 0; j < SQUARE_NUMBER; ++j) {
			grid[i][j].state = EMPTY;
			grid[i][j].color = WHITE;
		}
	}
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < SQUARE_NUMBER; ++j) {
			if (blit == 1) {
				grid[i][j].state = FULL;
				grid[i][j].color = WHITE;
			} else {
				blit = -blit;
			}
		}
		blit = -blit;
	}
	
	blit = 1;
	for (int i = 0; i < SQUARE_NUMBER; ++i) {
		for (int j = 0; j < SQUARE_NUMBER; ++j) {
			if (blit == 1) {
				grid[i][j].state = FULL;
				grid[i][j].color = RED;
			} else {
				blit = -blit;
			}
		}
		blit = -blit;
	}
}