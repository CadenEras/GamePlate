/**
 * @file interface.h
 * @author Melissa GRIES
 * @brief Implementation of the interface.
 */

#ifndef C_PAS_COOL_GAMEPLATE_INTERFACE_H
#define C_PAS_COOL_GAMEPLATE_INTERFACE_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "checkerGame.h"
#include "bases.h"

#define TILESIZE 80

SDL_Surface *screen;
SDL_Renderer *renderer;

/**
 * @brief Define a black tile. is free ? its number with a surface and a position.
 */
typedef struct BlackTile {
	int isFree;
	int nSquare;
	SDL_Rect position;
	SDL_Surface *surface;
} BlackTile;

/** Our black tile */
BlackTile blackTile;

/** Black tile highlighted*/
BlackTile blackTileHighlighted;

/**
 * @brief Define a white tile. is free ? its number with a surface and a position.
 */
typedef struct WhiteTile {
	int isFree;
	int nSquare;
	SDL_Rect position;
	SDL_Surface *surface;
} WhiteTile;

/** Our white tile */
WhiteTile whiteTile;

/**
 * @brief Define a red pawn. is King ? with a surface and a position.
 */
typedef struct RedPawn {
	int isKing;
	SDL_Surface *surface;
	SDL_Rect position;
} RedPawn;

/** Our red pawn */
RedPawn redPawn;

/**
 * @brief Define a black pawn. is King ? with a surface and a position.
 */
typedef struct BlackPawn {
	int isKing;
	SDL_Surface *surface;
	SDL_Rect position;
} BlackPawn;

/** Our black pawn */
BlackPawn blackPawn;

int arrayOfChoice[4];

/**
 * @brief Refresh board after an action.
 */
void refreshBoard();

/**
 * @brief Display Main Checker menu.
 * @param choice Choice from the Main Checker menu.
 */
void displayMainCheckerMenu(int choice);

/**
 * @brief Display Checker pause menu.
 * @param choice Choice from the Checker pause menu.
 */
void displayPauseCheckerScreen(int choice);

/**
 * @brief Affiche l'ecran de fin de partie, les noirs gagnent
 */
void displayBlackWin();

/**
 * @brief Affiche l'ecran de fin de partie, les blancs gagnent
 */
void displayWhiteWin();

/**
 * @brief Retourne la position de la mouse après un click
 * @return int* Un tableau contenant la position x et y du click
 */
int *mouseClick(SDL_Event e);

/**
 * @brief Initialise les cases blanches
 */
void initWhiteTiles();

/**
 * @brief Calcule la position de la mouse a chaque mouvement
 * @return int Un entier representant une position dans le menu.
 */
int mousePosition(SDL_Event e);

/**
 * @brief Calcule la position de la mouse a chaque mouvement
 * @return int Un entier representant une position dans le menu pause.
 */
int mousePositionPause(SDL_Event e);

/**
 * @brief Calcule la position de la mouse a chaque click dans le menu principal.
 * @return int Un entier representant un choice dans le menu principal.
 */
int mouseClickMenu(SDL_Event e);

/**
 * @brief Calcule la position de la mouse a chaque mouvement
 * @return int Un entier representant un choice dans le menu pause.
 */
int mouseClickPause(SDL_Event e);

/**
 * @brief Met en surbrillance un pion
 * @param tab Tableau contenant les coordonnees du click
 * @param p Board courant
 */
void capturePawnControl(BoardTile oldPosition, BoardTile newPosition);

/**
 * @brief Met en surbrillance un pion
 * @param tab Tableau contenant les coordonnees du click
 * @param p Board courant
 * @return BoardTile La case contenant le pion en surbrillance
 */
BoardTile highlightControl(int *tab);

/**
 * @brief Gere le premier click qui s'occupe uniquement de la selection du pion a jouer
 * @param tab Tableau contenant les coordonnees du click
 * @param oldCase la case de depart
 * @return BoardTile La case contenant le pion selectionne
 */
BoardTile firstClickOnBoardControl(SDL_Event event, int *tab, Board *p, BoardTile *oldCase);

/**
 * @brief Gere le deuxieme click qui s'occupe uniquement de la selection de la case a jouer
 * @param tab Tableau contenant les coordonnees du click
 * @param oldCase La case de depart
 * @param newCase La case d'arrive
 * @param finTour Gere le tour
 * @return BoardTile La case contenant le pion selectionne
 */
BoardTile secondClickOnBoardControl(SDL_Event event, int *tab, Board *p, BoardTile *newCase, BoardTile *oldCase);

#endif //C_PAS_COOL_GAMEPLATE_INTERFACE_H
