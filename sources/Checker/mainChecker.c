/**
 * @file mainChecker.c
 * @author Melissa GRIES
 * @brief Main file of Checker game.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../headers/Checker/interface.h"
#include "../../headers/Checker/mainChecker.h"
#include "../../headers/Checker/bases.h"

int mainChecker(Window *window) {
	int quitGame, activeWindow, mainMenu, gameWindow, pauseMenu,
			pos, click, posPause, noClick, diffX, diffY,
			playMove, player2, clickSelectPlayer;
	SDL_Event event;

	char *saveFile = "save.txt";
	int *arrC = calloc(sizeof(int), 2);
	int *arrC2 = calloc(sizeof(int), 2);
	int array[2];
	int array2[2];
	Player j1;
	Player j2;
	BoardTile t, oldPosition, newPosition, hoovedTile, startTile, middleTile;
	BoardTile *oldCase = malloc(sizeof(BoardTile));
	BoardTile *newCase = malloc(sizeof(BoardTile));
	int *endTurn = malloc(sizeof(int));
	int *playerTurn = malloc(sizeof(int));

	*endTurn = 0;
	*playerTurn = 0;
	clickSelectPlayer = 0;
	noClick = 0;
	player2 = 0;
	quitGame = 1;
	mainMenu = 1;
	gameWindow = 1;
	pauseMenu = 1;
	activeWindow = 0;
	int ongoingTurn = 0;

	/*SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetIcon(SDL_LoadBMP("Images/icon.bmp"), NULL);
	screen = SDL_SetVideoMode(LARGEUR, LONGUEUR, 32,
			SDL_SWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 0));*/

	printf("0) J'entre dans la boucle \n");
	while (quitGame) {
		switch (activeWindow) {
            case 0: //Fenetre Menu principal
                displayMainCheckerMenu(pos, window);
                while (mainMenu) {
                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                            case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {
                                    case SDLK_a:
                                        displayMainCheckerMenu(0, window);
                                        break;
                                    case SDLK_b:
                                        mainMenu = 0;
                                        activeWindow = 1;
                                        break;
                                    case SDLK_ESCAPE:
                                        mainMenu = 0;
                                        activeWindow = 9;
                                        break;
                                    default:
                                        quitGame = 1;
                                        break;
                                }//Fin switch touche choisi
                            case SDL_MOUSEMOTION:
                                pos = mousePosition(event);
                                displayMainCheckerMenu(pos, window);
                                break;
                                //Fin du cas : la souris bouge
                            case SDL_MOUSEBUTTONUP:
                                switch (event.button.button) {
                                    case SDL_BUTTON_LEFT:
                                        click = mouseClickMenu(event);
                                        switch (click) {
                                            case 1:
                                                // Clique sur commencer partie
                                                initGame();
                                                mainMenu = 0;
                                                activeWindow = 3;
                                                break;
                                            case 2:
                                                // Clique sur charger partie
                                                initGame();
                                                loadGame(saveFile);
                                                mainMenu = 0;
                                                activeWindow = 1;
                                                break;
                                            case 3:
                                                // Clique sur quitter
                                                mainMenu = 0;
                                                activeWindow = 9;
                                                break;
                                            default:
                                                break;
                                        }//Fin switch click
                                        break;
                                    default:
                                        break;
                                }//Fin choix bouton de souris UP
                            default:    
                                break;
                        }//Fin switch event.type
                    }//Fin while PollEvent
                }
                break;
            case 1: //Fenetre Jeu
                initWhiteTiles(window);
                refreshBoard(window);
                SDL_UpdateWindowSurface(window->window);
                while (gameWindow) {
                    while (SDL_PollEvent(&event) && !isFinished()) {
                        switch (event.type) {
                            case SDL_MOUSEBUTTONUP:
                                switch (event.button.button) {
                                    case SDL_BUTTON_LEFT:
                                        // ASTUCE : Appuyer sur la touche H affiche les pions jouables
                                        // Mais ce n est pas necessaire si on sait quoi jouer on peut le jouer directement.
                                        if (!player2) { // Tour Joueur 1
                                            noClick = noClick % 2; // Quel click ?
                                            if (noClick == 0) { //Premier click
                                                /*if (!ongoingTurn) {
                                                    tour_ia = commencer_tour();
                                                    ongoingTurn = 1;
                                                }
                                                if (!tour_ia) {*/
                                                    arrC = mouseClick(event); // Recupère les coordonnees du premier click
                                                    refreshBoard(window);
                                                    SDL_UpdateWindowSurface(window->window);
                                                    startTile = getTilePosition(arrC[0], arrC[1], boardGame);
                                                    int click_ok = highlightPossibleMovesXY(arrC[0], arrC[1]); // Une fois le pion selectionne, cela affiche les deplacements possibles
                                                    printf("Premier click reussi \n");
                                                    if (click_ok) {
                                                        noClick += 1; // On autorise l'acces au deuxieme click
                                                        highlightControl(arrC);
                                                    }
                                                /*} else { // si c'est l'ia qui a joué
                                                    player2 = 1;
                                                    ongoingTurn = 0;
                                                    tour_ia = 0;
                                                }*/
                                                refreshBoard(window);
                                                SDL_UpdateWindowSurface(window->window);
                                            } else {
                                                if (noClick == 1) { //Deuxieme click
                                                    arrC = mouseClick(event); // Recupère les coordonnees du deuxieme click
                                                    middleTile = getTilePosition(arrC[0], arrC[1], boardGame);
                                                    playMove = playMoveXY(startTile.x, startTile.y, middleTile.x, middleTile.y); //On joue le coup
                                                    refreshBoard(window);
                                                    SDL_UpdateWindowSurface(window->window);
                                                    switch (playMove) {
                                                        case 0:
                                                            player2 = 0;
                                                            printf("###########################\nOn garde la main (joueur 1)\n###########################\n");
                                                            break;
                                                        case 1:
                                                            player2 = 1;
                                                            printf("###########################\nOn passe au joueur 2 \n###########################\n");
                                                            ongoingTurn = 0;
                                                            break;
                                                        case 2:
                                                            player2 = 0;
                                                            printf("###########################\nOn garde la main (joueur 1)\n###########################\n");
                                                            break;
                                                    }
                                                    if (!isFinished()) {
                                                        printf("Deuxieme click reussi \n");
                                                        noClick += 1;
                                                    } else {
                                                        gameWindow = 0;
                                                        activeWindow = 4;
                                                    }
                                                }
                                            }
                                        } else {
                                            if (player2) { // Tour Joueur 2
                                                noClick = noClick % 2;
                                                if (noClick == 0) { //Premier click
                                                    /*if (!ongoingTurn) {
                                                        tour_ia = commencer_tour();
                                                        ongoingTurn = 1;
                                                    }
                                                    if (!tour_ia) {*/
                                                        arrC = mouseClick(event); // Recupère les coordonnees du premier click
                                                        refreshBoard(window);
                                                        SDL_UpdateWindowSurface(window->window);
                                                        startTile = getTilePosition(arrC[0], arrC[1], boardGame);
                                                        int click_ok = highlightPossibleMovesXY(arrC[0], arrC[1]);
                                                        printf("Premier click reussi \n");
                                                        if (click_ok) {
                                                            noClick += 1;
                                                            highlightControl(arrC);
                                                        }
                                                    /*} else {
                                                        player2 = 0;
                                                        ongoingTurn = 0;
                                                        tour_ia = 0;
                                                    }*/
                                                    refreshBoard(window);
                                                    SDL_UpdateWindowSurface(window->window);
                                                } else {
                                                    if (noClick == 1) { //Deuxieme click
                                                        arrC = mouseClick(event);
                                                        middleTile = getTilePosition(arrC[0], arrC[1], boardGame);
                                                        playMove = playMoveXY(
                                                                startTile.x,
                                                                startTile.y,
                                                                middleTile.x,
                                                                middleTile.y);
                                                        refreshBoard(window);
                                                        SDL_UpdateWindowSurface(window->window);
                                                        switch (playMove) {
                                                            case 0:
                                                                player2 = 1;
                                                                printf("###########################\nOn garde la main (joueur 2)\n###########################\n");
                                                                break;
                                                            case 1:
                                                                player2 = 0;
                                                                printf("###########################\nOn passe au joueur 1 \n###########################\n");
                                                                ongoingTurn = 0;
                                                                break;
                                                            case 2:
                                                                player2 = 1;
                                                                printf("###########################\nOn garde la main (joueur 2)\n###########################\n");
                                                                break;
                                                        }

                                                        if (!isFinished()) {
                                                            printf("Deuxieme click reussi \n");
                                                            noClick += 1;
                                                        } else {
                                                            gameWindow = 0;
                                                            activeWindow = 4;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        break;
                                }
                                break;
                            case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {
                                    case SDLK_ESCAPE:
                                        pauseMenu = 1;
                                        activeWindow = 2;
                                        gameWindow = 0;
                                        break;
                                    case SDLK_e:
                                        activeWindow = 9;
                                        gameWindow = 0;
                                        break;
                                    case SDLK_h:
                                        highlightPlayablePawns();
                                        refreshBoard(window);
                                        SDL_UpdateWindowSurface(window->window);
                                        break;
                                    default:
                                        quitGame = 1;
                                        break;
                                }//Fin choix de la touche
                                break;
                        }//Fin switch.type
                    }//Fin PollEvent
                }
                break;
            case 2: //Fentre Menu Pause
                displayPauseCheckerScreen(posPause, window);
                while (pauseMenu) {
                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                            case SDL_KEYDOWN:
                                switch (event.key.keysym.sym) {
                                    case SDLK_ESCAPE:
                                        pauseMenu = 0;
                                        activeWindow = 9;
                                        break;
                                    default:
                                        break;
                                }//Fin switch Keydown
                            case SDL_MOUSEMOTION:
                                posPause = mousePositionPause(event);
                                displayPauseCheckerScreen(posPause, window);
                            case SDL_MOUSEBUTTONUP:
                                switch (event.button.button) {
                                    case SDL_BUTTON_LEFT:
                                        click = mouseClickPause(event);
                                        printf("click souris = %d \n", click);
                                        switch (click) {
                                            case 1:
                                                saveGame(saveFile);
                                                pauseMenu = 0;
                                                activeWindow = 9;
                                                break;
                                            case 2:
                                                gameWindow = 1;
                                                pauseMenu = 0;
                                                activeWindow = 1;
                                                break;
                                            case 3:
                                                pauseMenu = 0;
                                                activeWindow = 9;
                                                break;
                                            default:
                                                break;
                                        }//Fin switch click
                                        break;
                                }// Fin switch choix click
                            default:
                                break;
                        }//Fin switch event.type
                    }
                }
                break;
            case 3: // Fin de partie
                if (isFinished() == 1) {
                    displayWhiteWin(window);
                } else {
                    displayBlackWin(window);
                }
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym) {
                                case SDLK_ESCAPE:
                                    activeWindow = 9;
                                    break;
                                default:
                                    break;
                            }//Fin switch Keydown
                            break;
                    }
                }
                break;
            default:
                printf("10) Je sors de la \n");
                quitGame = 0;
                break;
		}
	}

	printf("11) Fin du test \n");
	free(arrC);
	free(arrC2);

	return 0;
}
