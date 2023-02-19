/**
 * @file checkerGame.h
 * @author Melissa GRIES
 * @brief Implementation of the Checker game.
 */

#ifndef C_PAS_COOL_GAMEPLATE_CHECKERGAME_H
#define C_PAS_COOL_GAMEPLATE_CHECKERGAME_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h> /* pour NULL */

//#include "interface.h"
#include "bases.h"
//#include "../base/window.h"

#define NOMOVES 2000
#define NOMEVEMENTS 2

/**
 * @brief Initialise une nouvelle partie.
 */
void initGame();

/**
 *	@brief Renvoie le Board de la partie pour le consulter.
 */
Board getBoard();

/**
 * 	@brief Sauvegarde l'état courant de la partie.
 * 	@param filename Le chemin vers le fichier de sauvegarde.
 * 	@return Vrai si la sauvegarde s'est bien effectuée, faux si un problème est survenu.
 */
int saveGame(char *filename);

/**
 * 	@brief Charge une partie depuis le disque.
 * 	@param filename Le chemin vers le fichier à charger.
 * 	@return Vrai si le chargement s'est bien déroulé, faux sinon.
 */
int loadGame(char *filename);

/**
 * 	@brief Joue le coup pour le Player courant.
 * 	@param start La case de départ du coup.
 * 	@param end La case d'arrivée du coup.
 * 	@return 0 si le coup est invalide, 1 si le coup est valide et terminé, 2 si le mouvement fait partie d'un coup valide, on attend que le Player termine son coup par un nouvel appel à cette fonction ::jouer_coup.
 */
int playMove(int start, int end);

/**
 * 	@brief Identique à ::jouer_coup(int depart, int arrivee) mais prends les coordonnées (x,y) de la case.
 */
int playMoveXY(int x1, int y1, int x2, int y2);

/**
 * 	@brief Débute un nouveau tour de jeu, fait jouer l'IA si c'est à elle de jouer, attend un coup humain sinon.
 * 	@return Faux si on attend q'un humain joue, vrai si l'IA à joué et qu'on doit relancer immédiatement un nouveau tour.
 */
int startTurn();

/**
 * 	@brief Identique à ::hint_deplacements_possibles(int c) mais prends les coordonnées (x,y) de la case.
 */
int highlightPossibleMovesXY(int x,int y);

/**
 * @return Renvoie Faux si la partie n'est pas terminée, la color gagnante + 1 sinon.
 */
int isFinished();

#endif //C_PAS_COOL_GAMEPLATE_CHECKERGAME_H
