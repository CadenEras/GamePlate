/**
 * @file interface.c
 * @author Melissa GRIES
 * @brief Interface functions definition.
 */

#include "../../headers/Checker/interface.h"

void displayMainCheckerMenu(int choice) {
	SDL_Surface *startScreen;
	SDL_Texture *startMenuT;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	switch (choice) {
		case 1:
			startScreen = IMG_Load("../../assets/Checker/checker_menu_new_selected.bmp"); //start menu
			break;
		
		case 2:
			startScreen = IMG_Load("../../assets/Checker/checker_menu_load_selected.bmp"); //load menu
			break;

		case 3:
			startScreen = IMG_Load("../../assets/Checker/checker_menu_quit_selected.bmp"); //quit menu
			break;

		default:
			startScreen = IMG_Load("../../assets/Checker/checker_menu_neutral.bmp"); //neutral menu
			break;
	}

	startMenuT = SDL_CreateTextureFromSurface(renderer, startScreen);
	SDL_RenderCopy(renderer, startMenuT, NULL, NULL);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}
 
void displayPauseCheckerScreen(int choice) {
	SDL_Surface *pauseMenu;
	SDL_Texture *pauseMenuT;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	switch (choice) {
		case 1:
			pauseMenu = SDL_LoadBMP("../../assets/Checker/checker_pause_menu_save_selected.bmp");
			break;

		case 2:
			pauseMenu = SDL_LoadBMP("../../assets/Checker/checker_pause_menu_backtogame_selected.bmp");
			break;

		case 3:
			pauseMenu = SDL_LoadBMP("../../assets/Checker/checker_pause_menu_quit_selected.bmp");
			break;

		default:
			pauseMenu = SDL_LoadBMP("../../assets/Checker/checker_pause_menu_neutral.bmp");
			break;
	}

	pauseMenuT = SDL_CreateTextureFromSurface(renderer, pauseMenu);
	SDL_RenderCopy(renderer, pauseMenuT, NULL, NULL);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void refreshBoard() {
	int i;
	blackTile.surface = SDL_LoadBMP("Images/marbre_black.bmp");
	whiteTile.surface = SDL_LoadBMP("Images/marbre.bmp");
	blackTileHighlighted.surface = SDL_LoadBMP("Images/marbre_black_selectionne.bmp");

	for ( i = 1 ; i <= 50 ; i++) {
		if(board.tiles[i].isHighlighted == 0) {				// IF tile is not selected
			blackTile.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTile.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTile.surface, NULL, screen, &blackTile.position);
			redPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			redPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;

			blackTile.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTile.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTile.surface, NULL, screen, &blackTile.position);
			blackPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;
		} else {											// else tile is selected
			blackTileHighlighted.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTileHighlighted.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTileHighlighted.surface, NULL, screen, &blackTileHighlighted.position);
			redPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			redPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;

			blackTileHighlighted.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackTileHighlighted.position.y = (board.tiles[i].y - 1) * TILESIZE;
			SDL_BlitSurface(blackTileHighlighted.surface, NULL, screen, &blackTileHighlighted.position);
			blackPawn.position.x = (board.tiles[i].x - 1) * TILESIZE;
			blackPawn.position.y = (board.tiles[i].y - 1) * TILESIZE;
		}

		if (board.tiles[i].isFree == 0) { 						//IF tile is not free
			if (board.tiles[i].pawn.color == white) { 			// IF pawn is white
				if (board.tiles[i].pawn.isKing == 0) { 			// IF pawn is not a King
					if (board.tiles[i].pawn.isHighlighted == 0) { // IF pawn is not selected
						redPawn.surface = SDL_LoadBMP("Images/redPawn.bmp");
						SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, screen, &redPawn.position);
					} else {									// else pawn is selected
						redPawn.surface = SDL_LoadBMP("Images/redPawn_selectionne.bmp");
						SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, screen, &redPawn.position);
					}
				} else { 										// else pawn is a King
					if (board.tiles[i].pawn.isHighlighted == 0) { // IF pawn is not selected
						redPawn.surface = SDL_LoadBMP("Images/redPawn_dame.bmp");
						SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, screen, &redPawn.position);
					} else {									// else pawn is selected
						redPawn.surface = SDL_LoadBMP("Images/redPawn_dame_selectionne.bmp");
						SDL_SetColorKey(redPawn.surface, NULL, SDL_MapRGB(redPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(redPawn.surface, NULL, screen, &redPawn.position);
					}
				}
			}

			if (board.tiles[i].pawn.color == black) {			// IF pawn is black
				if (board.tiles[i].pawn.isKing == 0) { 			// IF pawn is not a King
					if (board.tiles[i].pawn.isHighlighted == 0) { // IF pawn is not selected
						blackPawn.surface = SDL_LoadBMP("Images/blackPawn.bmp");
						SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, screen, &blackPawn.position);
					} else {
						blackPawn.surface = SDL_LoadBMP("Images/blackPawn_selectionne.bmp");
						SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, screen, &blackPawn.position);
					}
				} else {
					if (board.tiles[i].pawn.isHighlighted == 0){ 
						blackPawn.surface = SDL_LoadBMP("Images/blackPawn_dame.bmp");
						SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, screen, &blackPawn.position);
					} else {
						blackPawn.surface = SDL_LoadBMP("Images/blackPawn_dame_selectionne.bmp");
						SDL_SetColorKey(blackPawn.surface, NULL, SDL_MapRGB(blackPawn.surface->format, 241, 241, 241));
						SDL_BlitSurface(blackPawn.surface, NULL, screen, &blackPawn.position);
					}
				}
			}
		} //End, tile is not free
	}
}

void displayWhiteWin() {
	SDL_Surface *screenWhiteWin;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	screenWhiteWin = SDL_LoadBMP("Images/blancs_gagnent.bmp");
	SDL_BlitSurface(screenWhiteWin,NULL,screen,&position);
	SDL_Flip(screen);
}

void displayBlackWin() {
	SDL_Surface *screenBlackWin;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	screenBlackWin = SDL_LoadBMP("Images/noirs_gagnent.bmp");
	SDL_BlitSurface(screenBlackWin,NULL,screen,&position);
	SDL_Flip(screen);
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

	if (e.motion.x > 142 && e.motion.x < 670 && e.motion.y > 347 && e.motion.y < 380 ) {
		return 1;
	} else {
		if (e.motion.x > 173 && e.motion.x < 640 && e.motion.y > 449 && e.motion.y < 480 ) {
			return 2;
		} else {
			if (e.motion.x > 310 && e.motion.x < 500 && e.motion.y > 548 && e.motion.y < 580 ) {
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

	if(e.button.x > 142 && e.button.x < 670 && e.button.y > 347 && e.button.y < 380 ){
		return 1;
	}
	else{
		if(e.button.x > 173 && e.button.x < 640 && e.button.y > 449 && e.button.y < 480 ){
			return 2;
		}
		else{
			if(e.button.x > 310 && e.button.x < 500 && e.button.y > 548 && e.button.y < 580 ){
				return 3;
			}
			else{
				return 0;
			}
		}
	}
}

int mousePositionPause(SDL_Event e){
	e.motion.x;
	e.motion.y;

	if(e.motion.x > 251 && e.motion.x < 540 && e.motion.y > 321 && e.motion.y < 356 ){
		return 1;
	}
	else{
		if(e.motion.x > 180 && e.motion.x < 624 && e.motion.y > 397 && e.motion.y < 429 ){
			return 2;
		}
		else{
			if(e.motion.x > 305 && e.motion.x < 494 && e.motion.y > 479 && e.motion.y < 510 ){
				return 3;
			}
			else{
				return 0;
			}
		}
	}
}

int mouseClickPause(SDL_Event e){
	e.button.x;
	e.button.y;

	if(e.button.x > 251 && e.button.x < 540 && e.button.y > 321 && e.button.y < 356 ){
		return 1;
	}
	else{
		if(e.button.x > 180 && e.button.x < 624 && e.button.y > 397 && e.button.y < 429 ){
			return 2;
		}
		else{
			if(e.button.x > 305 && e.button.x < 494 && e.button.y > 479 && e.button.y < 510 ){
				return 3;
			}
			else{
				return 0;
			}
		}
	}
}

void initWhiteTiles() {
	int i,j;
	whiteTile.surface = SDL_LoadBMP("Images/marbre.bmp");
	whiteTile.position.x = 0;
	whiteTile.position.y = 0;

	for(i = 0; i<=4; i++) {
		for(j=0;j<=4;j++) {
			SDL_BlitSurface(whiteTile.surface, NULL, screen, &whiteTile.position);
			whiteTile.position.x += 2 * TILESIZE;
		}
		whiteTile.position.y += TILESIZE;
		whiteTile.position.x = TILESIZE;

		for(j=0;j<=4;j++){
			SDL_BlitSurface(whiteTile.surface, NULL, screen, &whiteTile.position);
			whiteTile.position.x += 2 * TILESIZE;

		}
		whiteTile.position.y += TILESIZE;
		whiteTile.position.x = 0;
	}
}

void capturePawnControl(BoardTile oldPosition, BoardTile newPosition){
	int diffX, diffY;
	BoardTile hoveredTile;
	diffX = oldPosition.x - newPosition.x;
	diffY = oldPosition.y - newPosition.y;

	switch(diffX){
		case 2: //On va a gauche
			switch(diffY){
				case 2: //On va en haut a gauche
					hoveredTile = getTilePosition( newPosition.x + 1, newPosition.y + 1, board);
					printf("Case survole :");
					displayTestInfo(hoveredTile);
					capturePawnOnBoard(hoveredTile.officialRating, &board);
					break;
				case -2: //On va en bas a gauche
					hoveredTile = getTilePosition( newPosition.x + 1, newPosition.y - 1, board);
					printf("Case survole :");
					displayTestInfo(hoveredTile);
					capturePawnOnBoard(hoveredTile.officialRating, &board);
					break;
				default: //default
					printf("mouvement interdit \n");
					break;
			}
			break;
		case -2: //On va a droite
			switch(diffY){
				case 2: //On va en haut a droite
					hoveredTile = getTilePosition( newPosition.x - 1, newPosition.y + 1, board);
					printf("Case survole :");
					displayTestInfo(hoveredTile);
					capturePawnOnBoard(hoveredTile.officialRating, &board);
					break;
				case -2: //On va en bas a droite
					hoveredTile = getTilePosition( newPosition.x - 1, newPosition.y - 1, board);
					printf("Case survole :");
					displayTestInfo(hoveredTile);
					capturePawnOnBoard(hoveredTile.officialRating, &board);
					break;
				default:
					printf("mouvement interdit \n");
					break;
			}
			break;
		default:
			printf("mouvement interdit \n");
			break;
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

BoardTile firstClickOnBoardControl(SDL_Event event, int *tab, Board *b, BoardTile *oldCase){
	BoardTile selected;
	Player actualPlayer;
	actualPlayer = b->turn;
	selected = getTilePosition(tab[0], tab[1],*b);

	if(selected.isFree == 0) { //Si elle n'est pas libre
		if(selected.pawn.color == actualPlayer.color) { //Si colorpawn correspond au Player en cours
			*oldCase = selected;
			//selected = highlightControl(tab, p);
			printf("premier click reussi : tab[0] = %d tab[1] = %d \n", tab[0], tab[1]);
		}//FinSi colorpawn correspond au Player en cours
	}//FinSi elle n'est pas libre

	return selected;
}

BoardTile secondClickOnBoardControl(SDL_Event event, int *tab, Board *b, BoardTile *newCase, BoardTile *oldCase){
	BoardTile selected;
	//BoardTile moveTile;

	selected = getTilePosition(tab[0], tab[1], *b);

	if(selected.isFree){ //Si la case est libre
		//Si la case selectionne correspond a une des cases du tableau des coups possibles
		*newCase = selected;
		Board_deplacer_pawn(oldCase->officialRating,newCase->officialRating, b);
		printf("deuxieme click reussi \n");
	} //FinSi la case est libre

	return selected;
}

//??
void initialisation_tableau_choix(){
	arrayOfChoice[0] = 0;
	arrayOfChoice[1] = 0;
	arrayOfChoice[2] = 0;
	arrayOfChoice[3] = 0;
}