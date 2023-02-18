/**
 * @file checkerGame.h
 * @author Melissa GRIES
 * @brief Implementation of the Checker game.
 */

#ifndef C_PAS_COOL_GAMEPLATE_CHECKERGAME_H
#define C_PAS_COOL_GAMEPLATE_CHECKERGAME_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h> /* pour NULL */

#include "interface.h"
#include "bases.h"
#include "../base/window.h"

#define NOMOVES 2000
#define NOMEVEMENTS 2

/** Le Board de jeu qui sera utilisé tout au long de la partie. (Ne pas utiliser en dehors de moteur.c, utilisez ::get_Board()) */
Board boardGame;

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
 * 	@brief Joue sur la profondeur d'évaluation du min-max.
 * 	@param i La profondeur d'évaluation.
 */
void setDifficulty(int i);

/**
 * 	@brief Débute un nouveau tour de jeu, fait jouer l'IA si c'est à elle de jouer, attend un coup humain sinon.
 * 	@return Faux si on attend q'un humain joue, vrai si l'IA à joué et qu'on doit relancer immédiatement un nouveau tour.
 */
int startTurn();

/**
 * @brief Met en surbrillance les pions qui permettent un déplacement valide pour ce tour.
 */
void highlightPlayablePawns();

/**
 * 	@brief Met en surbrillance les déplacements possibles partant d'une case donnée.
 * 	@param c Notation officielle de la case de départ.
 * 	@return Vrai si le pion séléctionné fait partie d'un coup authorisé.
 */
int highlightPossibleMoves(int c);

/**
 * 	@brief Identique à ::hint_deplacements_possibles(int c) mais prends les coordonnées (x,y) de la case.
 */
int highlightPossibleMovesXY(int x,int y);

/**
 * @return Renvoie Faux si la partie n'est pas terminée, la color gagnante + 1 sinon.
 */
int isFinished();

/**
 * @brief retourne le tableau des coups possible pour un coup donné.
 * @param c La case qui contient le pion de la recherche.
 * @param p la Board courant.
 */
Move *possibleMove(const BoardTile t, const Board b);

/**
 * @brief retourne le tableau des coups possible pour le Player donné.
 * @param j le Player dont on chercher tout les coups
 * @param p la Board courant.
 */
Move *getMove(const Player p, const Board b);

/**
 * @brief retourne les coups qui ont le max de prises possible.
 * @param m le tableau de tout les coups possibles
 */
Move *getMaxMoves(const Move *m);

/**
 * @brief retourne les deplacements possibles du pion de la case donné
 * @param c la case ou est situé le pion dont on va chercher les déplacements possibles.
 */
Move *getMovement(const BoardTile t, const Board b);

/**
 * @param mvt La diagonale du mouvement du coup précedent.
 * @return La liste des coups possibles commençant par le coup c.
 */
Move *completeKingMove(const Move m, int mvt, Board b);

/**
 * @param c Notation officielle de la case de départ.
 * @param diag Diagonale dans laquelle on recherche.
 * @return 0 si pas de cpions à prendre, la case sur laquelle se trouve le pion à prendre sinon.
 */
int possibleTilePosition(int c, int diag, Board b) ;

/**
 * @param liste1 la premiere liste des coups
 * @param liste2 la seconde liste des coups
 * @return 0 si liste 1 == liste2, sinon 1
 */
int compMove(Move *array1, Move *array2);

/**
 * @param x la position en abscisse
 * @param y la position en ordonnée
 * @param p le Board courant
 * @return la case qui est en position x y dans p
 */
BoardTile getTileSilent(int x, int y, Board p);

#endif //C_PAS_COOL_GAMEPLATE_CHECKERGAME_H
