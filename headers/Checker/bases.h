/**
 * @file bases.h
 * @author Melissa GRIES
 * @brief Declaration of the base elements.
 */

#ifndef C_PAS_COOL_GAMEPLATE_BASES_H
#define C_PAS_COOL_GAMEPLATE_BASES_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief Which color the pawn is (red, black).
 */
typedef enum Color {
	white,
	black
} Color;

/**
 * @brief Which move it is (capture, move).
 */
typedef enum MoveType {
	capture,
	move
} MoveType;

/**
 * @brief Pawn object (color, is king ?, is highlighted ?).
 */
typedef struct Pawn {
	Color color;
	int isKing;
	int isHighlighted
} Pawn;

/**
 * @brief Tile object (color, is free ?, pawn on it, x, y, rating, is highlighted ?).
 */
typedef struct BoardTile {
	Color color;
	int isFree; // 1 if the tile is free, else 0.
	Pawn pawn; // The pawn on it if isFree = 1.
	int x; //Only if color = black.
	int y; //Only if color = black.
	int officialRating;
	int isHighlighted;
} BoardTile;

/**
 * @brief Player object (color).
 */
typedef struct player {
	Color color;
} Player;

/**
 * @brief Player object (color).
 */
typedef struct Move {
	int oldTile;
	int newTile;
	MoveType type; //move or capture
	int noTaken;
	BoardTile taken[20]; //Tiles were pawns were taken.
	BoardTile path[20]; //Tiles on which the panw stops during a raid (the last tile will be white to mark the end of the list)
	char *comment; /*Comments are :
						! strong move/ Well played
						!! pour indiquer un Move très fort
						? pour indiquer un Move faible ou mal joué
						?? pour indiquer un Move très faible ou une gaffe
						!? pour indiquer un Move paraissant fort, mais qui en réalité se révèle faible
						! pour indiquer un Move paraissant faible, mais qui en réalité se révèle fort
						* pour indiquer un Move forcé, tout autre mouvement entraînant une perte immédiate
						+ pour indiquer le gain de la partie
						= pour indiquer un jeu égal
						+1 pour indiquer le gain d’un pion
						+n pour indiquer le gain de n pion
						+- pour indiquer un avantage aux blancs
						+ pour indiquer un avantage aux noirs
					*/
} Move;

/**
 * @brief Player object (color).
 */
typedef struct Board {
	BoardTile tiles[51];	// A board is made up of 50 tiles, numbered from 01 to 50. (tile 0 store a white tile).
	Move history[500];	// Can store up to 500 moves.
	Player player1;
	Player player2;
	Player turn; // Which player is to play the next turn.
} Board;

// The board we will use
Board board;

/**
 * @brief Fonction de création d'un nouveau Board.
 * @param j1 Le Player blanc.
 * @param j2 Le Player noir.
 * @return Board Un Board initialisé avec les pions en position initiale et associé aux Players.
 */
Board newBoard(Player p1, Player p2);

/**
 * @brief Déplace un pion.
 * @param old_position La position de départ.
 * @param new_position La position d'arrivée.
 * @return int Vrai si le déplacement est possible, faux si un pion occupe déjà la case ou si on sort du Board.
 */
int movePawnOnBoard(int oldPosition, int newPosition, Board *board);

/**
 * @brief Prend le pion de la case "position".
 * @param position Position de la case sur laquelle se trouve le pion.
 * @return int Vrai si la prise est effectuée, faux si la case est vide ou si on sort du Board.
 */
int capturePawnOnBoard(int position, Board *board);

/**
 * @brief Ajoute un Move dans l'historique du Board.
 * @param c Le Move à ajouter.
 * @param p Le Board auquel on ajoute le Move.
 * En raison du risque improbable qu'une partie dure plus de 500 Moves, l'historique au-delà est ignoré.
 */
void addMoveToBoardHistory(Move move,Board *board);

/**
 *	@brief Met à jour le Board en jouant le Move donné et passe la main au Player suivant.
 *	@param c Le Move à jouer.
 */
void applyMove(Move move, Board *board);

/**
 * 	@brief Teste si la partie est gagnée pour un des deux Players.
 * 	@return 0 si la partie n'est pas finie, couleur + 1 sinon.
 */
int isWon(Board board);

/**
 * @brief Renvoie la case à la position (x,y).
 * @param x Abscisse de la case (colonne) [1-10].
 * @param y Ordonnée de la case [1-10].
 */
BoardTile getTilePosition(int x, int y,Board board);

/**
 * @brief Affiche les informations sur la case (à des fins de test).
 * @param c La case à afficher.
 */
void displayTestInfo(BoardTile tile);

/**
 * 	@brief Affiche le Board sur stdout.
 */
void printBoardTest(Board board);

/**
 * @brief Met la case en surbrillance.
 * @param numero Numéro de la case à mettre en surbrillance (selon la notation officielle).
 */
void highlightTile(int numero,Board *board);

/**
 * @brief Met un pion en surbrillance.
 * @param numero Numéro de la case sur laquelle se trouve le pion à mettre en surbrillance (selon la notation officielle).
 */
void highlightPawn(int numero,Board *board);

/**
 * @brief Annule la mise en surbrillance de toutes les cases et tous les pions du Board.
 */
void resetHighlight(Board *board);

/**
 * @brief print les infos d'un Move
 * @param move le Move dont on veut les informations.
 */
void displayMove(const Move move);

/**
 * @brief predicat pour savoir si une position est prenable.
 * @param position la position du pion que l'on veut prendre.
 * @param board le Board sur lequel on veut tester la position à prendre.
 */
int isTakeable(int position, Board *board);

/**
 * @brief affiche la liste des Moves dans l.
 * @param move la liste des Moves que l'on veut afficher.
 */
void displayMoveAvailable(Move *move);

/**
 * @brief prédicat: est ce que la case c est incluse dans liste ?
 * @param c la case a tester.
 * @param liste l'ensemble d'inclusion.
 */
int moveIsIncluded(BoardTile c, BoardTile *list, int size);

/**
 * @brief retourne la case si elle existe, ou la case 0 sinon
 * @param x la position horizontale sur le Board
 * @param y la position verticale sur le Board
 * @param p le Board courant
 */
BoardTile getTileSilent(int x, int y, Board board);

/**
 * @brief retourne le nombre de Moves dans set
 * @param set le tableau des Moves.
 */
int numberMoves(Move *set);

#endif //C_PAS_COOL_GAMEPLATE_BASES_H
