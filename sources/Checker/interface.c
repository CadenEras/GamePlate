/**
 * @file interface.c
 * @author Melissa GRIES
 * @brief Interface functions definition.
 */

#include "../../headers/Checker/interface.h"
#include "../../headers/Checker/bases.h"

//SDL_Surface *screen;
SDL_Renderer *renderer;

/** Our black tile */
BlackTile blackTile;

/** Black tile highlighted*/
BlackTile blackTileHighlighted;

/** Our white tile */
WhiteTile whiteTile;

/** Our red pawn */
RedPawn redPawn;

/** Our black pawn */
BlackPawn blackPawn;

// The board we will use
Board board;

void displayMainCheckerMenu(int choice, Window *window) {
	SDL_Surface *startScreen;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_Surface *windowMenu = SDL_GetWindowSurface(window->window);
	switch (choice) {
		case 1:
			startScreen = IMG_Load("./../assets/Checker/checker_menu_new_selected.bmp"); //start menu
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
		case 2:
			startScreen = IMG_Load("./../assets/Checker/checker_menu_load_selected.bmp"); //load menu
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
		case 3:
			startScreen = SDL_LoadBMP("./../assets/Checker/checker_menu_quit_selected.bmp"); //quit menu
			SDL_BlitSurface(startScreen,NULL,windowMenu,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
		default:
			startScreen = SDL_LoadBMP("./../assets/Checker/checker_menu_neutral.bmp"); //neutral menu
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
 
void displayPauseCheckerScreen(int choice, Window *window) {
	SDL_Surface *pauseMenu;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	switch (choice) {
		case 1:
			pauseMenu = SDL_LoadBMP("./../assets/Checker/checker_pause_menu_save_selected.bmp");
			SDL_BlitSurface(pauseMenu,NULL,window->screen,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
		case 2:
			pauseMenu = SDL_LoadBMP("./../assets/Checker/checker_pause_menu_backtogame_selected.bmp");
			SDL_BlitSurface(pauseMenu,NULL,window->screen,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
		case 3:
			pauseMenu = SDL_LoadBMP("./../assets/Checker/checker_pause_menu_quit_selected.bmp");
			SDL_BlitSurface(pauseMenu,NULL,window->screen,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
		default:
			pauseMenu = SDL_LoadBMP("./../assets/Checker/checker_pause_menu_neutral.bmp");
			SDL_BlitSurface(pauseMenu,NULL,window->screen,&position);
			SDL_UpdateWindowSurface(window->window);
			break;
	}
}

void refreshBoard(Window *window) {
	int i;
	blackTile.surface = SDL_LoadBMP("./../assets/Checker/black_tile.bmp");
	whiteTile.surface = SDL_LoadBMP("./../assets/Checker/white_tile.bmp");
	blackTileHighlighted.surface = SDL_LoadBMP("./../assets/Checker/black_tile_select.bmp");

	for ( i = 1 ; i <= 50 ; i++) {
		if(board.tiles[i].isHighlighted == 0) {				// IF tile is not selected
			blackTile.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTile.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTile.surface, NULL, window->screen, &blackTile.position);
			SDL_UpdateWindowSurface(window->window);
			redPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			redPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;

			blackTile.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTile.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTile.surface, NULL, window->screen, &blackTile.position);
			SDL_UpdateWindowSurface(window->window);
			blackPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;
		} else {											// else tile is selected
			blackTileHighlighted.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTileHighlighted.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTileHighlighted.surface, NULL, window->screen, &blackTileHighlighted.position);
			SDL_UpdateWindowSurface(window->window);
			redPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			redPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;

			blackTileHighlighted.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTileHighlighted.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTileHighlighted.surface, NULL, window->screen, &blackTileHighlighted.position);
			SDL_UpdateWindowSurface(window->window);
			blackPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;
		}

		if (board.tiles[i].isFree == 0) { 						//IF tile is not free
			if (board.tiles[i].pawn.color == white) { 			// IF pawn is white
				if (board.tiles[i].pawn.isKing == 0) { 			// IF pawn is not a King
					if (board.tiles[i].pawn.isHighlighted == 0) { // IF pawn is not selected
						redPawn.surface = SDL_LoadBMP("./../assets/Checker/red.bmp");
						//SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, window->screen, &redPawn.position);
						SDL_UpdateWindowSurface(window->window);
					} else {									// else pawn is selected
						redPawn.surface = SDL_LoadBMP("./../assets/Checker/red_select.bmp");
						//SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, window->screen, &redPawn.position);
						SDL_UpdateWindowSurface(window->window);
					}
				} else { 										// else pawn is a King
					if (board.tiles[i].pawn.isHighlighted == 0) { // IF pawn is not selected
						redPawn.surface = SDL_LoadBMP("./../assets/Checker/red_king.bmp");
						//SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, window->screen, &redPawn.position);
						SDL_UpdateWindowSurface(window->window);
					} else {									// else pawn is selected
						redPawn.surface = SDL_LoadBMP("./../assets/Checker/red_select_king.bmp");
						//SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, window->screen, &redPawn.position);
						SDL_UpdateWindowSurface(window->window);
					}
				}
			}

			if (board.tiles[i].pawn.color == black) {			// IF pawn is black
				if (board.tiles[i].pawn.isKing == 0) { 			// IF pawn is not a King
					if (board.tiles[i].pawn.isHighlighted == 0) { // IF pawn is not selected
						blackPawn.surface = SDL_LoadBMP("./../assets/Checker/black.bmp");
						//SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, window->screen, &blackPawn.position);
						SDL_UpdateWindowSurface(window->window);
					} else {
						blackPawn.surface = SDL_LoadBMP("./../assets/Checker/black_select.bmp");
						//SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, window->screen, &blackPawn.position);
						SDL_UpdateWindowSurface(window->window);
					}
				} else {
					if (board.tiles[i].pawn.isHighlighted == 0){ 
						blackPawn.surface = SDL_LoadBMP("./../assets/Checker/black_king.bmp");
						//SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, window->screen, &blackPawn.position);
						SDL_UpdateWindowSurface(window->window);
					} else {
						blackPawn.surface = SDL_LoadBMP("./../assets/Checker/black_select_king.bmp");
						//SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, window->screen, &blackPawn.position);
						SDL_UpdateWindowSurface(window->window);
					}
				}
			}
		} //End, tile is not free
	}
}

void displayWhiteWin(Window *window) {
	SDL_Surface *screenWhiteWin;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	screenWhiteWin = SDL_LoadBMP("./../assets/Checker/checker_red_win.bmp");
	SDL_BlitSurface(screenWhiteWin,NULL,window->screen,&position);
	SDL_UpdateWindowSurface(window->window);
}

void displayBlackWin(Window *window) {
	SDL_Surface *screenBlackWin;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	screenBlackWin = SDL_LoadBMP("./../assets/Checker/checker_black_win.bmp");
	SDL_BlitSurface(screenBlackWin,NULL,window->screen,&position);
	SDL_UpdateWindowSurface(window->window);
}

int *mouseClick(SDL_Event e){
	int *array = calloc(sizeof(int), 4); // A changer
	int xt,yt;
	SDL_Rect posRect;

	posRect.x = e.button.x;
	posRect.y = e.button.y;
	xt = posRect.x / 80 + 1;
	yt = posRect.y / 80 + 1;

	array[0] = xt;
	array[1] = yt;
	array[2] = posRect.x; // A virer
	array[3] = posRect.y;
	return array;
}

int mousePosition(SDL_Event e){
	e.motion.x;
	e.motion.y;

	if(e.button.x > 300 && e.button.x < 500 && e.button.y > 214 && e.button.y < 230 ){
		return 1;
	} else {
		if(e.button.x > 280 && e.button.x < 530 && e.button.y > 256 && e.button.y < 280 ){
			return 2;
		} else {
			if(e.button.x > 350 && e.button.x < 450 && e.button.y > 338 && e.button.y < 360 ){
				return 3;
			} else {
				return 0;
			}
		}
	}
}

int mouseClickMenu(SDL_Event e){
	e.button.x;
	e.button.y;

	if(e.button.x > 300 && e.button.x < 500 && e.button.y > 214 && e.button.y < 230 ){
		return 1;
	} else {
		if(e.button.x > 280 && e.button.x < 530 && e.button.y > 256 && e.button.y < 280 ){
			return 2;
		} else {
			if(e.button.x > 350 && e.button.x < 450 && e.button.y > 338 && e.button.y < 360 ){
				return 3;
			} else {
				return 0;
			}
		}
	}
}

int mousePositionPause(SDL_Event e){
	e.motion.x;
	e.motion.y;

	if(e.motion.x > 310 && e.motion.x < 490 && e.motion.y > 220 && e.motion.y < 240 ){
		return 1;
	} else {
		if(e.motion.x > 295 && e.motion.x < 505 && e.motion.y > 265 && e.motion.y < 287 ){
			return 2;
		} else {
			if(e.motion.x > 344 && e.motion.x < 460 && e.motion.y > 313 && e.motion.y < 336 ){
				return 3;
			} else {
				return 0;
			}
		}
	}
}

int mouseClickPause(SDL_Event e){
	e.button.x;
	e.button.y;

	if(e.motion.x > 310 && e.motion.x < 490 && e.motion.y > 220 && e.motion.y < 240 ){
		return 1;
	} else {
		if(e.motion.x > 295 && e.motion.x < 505 && e.motion.y > 265 && e.motion.y < 287 ){
			return 2;
		} else {
			if(e.motion.x > 344 && e.motion.x < 460 && e.motion.y > 313 && e.motion.y < 336 ){
				return 3;
			} else {
				return 0;
			}
		}
	}
}

void initWhiteTiles(Window *window) {
	int i,j;
	whiteTile.surface = SDL_LoadBMP("./../assets/Checker/white_tile.bmp");
	if(whiteTile.surface == NULL || whiteTile.surface == 0) {
		printf("ça a pas marché %s", SDL_GetError);
		exit(-1);
	}
	whiteTile.position.x = 0;
	whiteTile.position.y = 0;

	for(i = 0; i<=4; i++) {
		for(j=0;j<=4;j++) {
			SDL_BlitSurface(whiteTile.surface, NULL, window->screen, &whiteTile.position);
			SDL_UpdateWindowSurface(window->window);
			whiteTile.position.x += 2 * TILESIZE;
		}
		whiteTile.position.y += TILESIZE;
		whiteTile.position.x = TILESIZE;

		for(j=0;j<=4;j++){
			SDL_BlitSurface(whiteTile.surface, NULL, window->screen, &whiteTile.position);
			SDL_UpdateWindowSurface(window->window);
			whiteTile.position.x += 2 * TILESIZE;
		}
		whiteTile.position.y += TILESIZE;
		whiteTile.position.x = 0;
	}
}

BoardTile highlightControl(int *tab){
	BoardTile tile;
	tile = getTilePosition(tab[0], tab[1], board);
	if(tile.pawn.color == board.turn.color){
		highlightPawn(tile.officialRating, &board);
	}

	return tile;
}