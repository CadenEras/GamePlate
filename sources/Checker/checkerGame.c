/**
 * @file checkerGame.c
 * @author Melissa GRIES
 * @brief Checker game functions deendedtion.
 */

#include "../../headers/Checker/interface.h"
#include "../../headers/Checker/bases.h"

Board boardGame;

/** Permet de savoir si un coup non terminé de la part du joueur est en cours. (Ne pas utiliser en dehors de moteur.c) */
int actualMove = 0;

/** Variable globale qui n'est calculée qu'une seule fois au début du turn. (Ne pas utiliser en dehors de moteur.c) */
Move *possibleMoves;

/** Variable globale qui permet de choisir la profondeur d'analyse de l'algorithme min-max (Ne pas utiliser en dehors de moteur.c, utilisez plutôt ::set_difficulty). */
int difficulty = 1;

/** sauvegarde de la case de départ dans le cas d'un coup en plusieurs mouvement */
int startTile;

/** on garde la case intermédiaire afin de vérifier que le joueur reclique bien sur le même jeton après un mouvement partiel */
int middleTile;

int playMove(int start, int end) {
	resetHighlight(&boardGame);
	if (actualMove) { /* si un mouvement n'a pas été transfomé en coup complet */
		if (start == middleTile) { /* on vérifie qu'on déplace toujours le même pawn */
			int i = 0;
			Move m;
			while ((m = possibleMoves[i]).oldTile != 0) { /* on recherche à nouveau les coups qui correspondent à la case de départ */
				if (m.oldTile == startTile) {
					if (m.newTile == end) {
						movePawnOnBoard(start, startTile, &boardGame); /* on remet le pawn à sa position initiale pour appeler applyMove() */
						applyMove(m, &boardGame);
						actualMove = 0;
						return 1;
					} else { /* sinon on recherche si le déplacement fait partie d'un coup valide */
						int j = 0;
						BoardTile tilePath;
						int noTaken = m.noTaken;
						while (j < noTaken) {
							tilePath = m.path[j];
							if (tilePath.officialRating == end) { /* si c'est le cas, on stocke la case de départ et on quitte en attendant la suite du coup */
								actualMove = 1;
								middleTile = end;
								movePawnOnBoard(start, end, &boardGame);
								return 2;
							}
							j++;
						}
					}
				}
				i++;
			}
		}
		/* si on n'a pas fait de return avant ce point, alors le coup est invalide, on remet le Board dans sa position initiale */
		actualMove = 0;
		startTile = 0;
		middleTile = 0;
		movePawnOnBoard(start, startTile, &boardGame);

		return 0;
	} else { /* si on commence un nouveau turn */
		int i = 0;
		Move m;
		int noMove = numberMoves(possibleMoves);
		while (i < noMove) { /* puis on le parcours à la recherche de la case cliquée */
			m = possibleMoves[i];
			if (m.oldTile == start) { /* si on la trouve on teste si c'est un coup complet */
				if (m.newTile == end) {
					applyMove(m, &boardGame); /* si c'est le cas on met le Board à jour */
					return 1;
				} else { /* sinon on cherche si le déplacement fait partie d'un coup valide */
					int j = 0;
					BoardTile tilePath;
					int noTaken = m.noTaken;
					while (j < noTaken) {
						tilePath = m.path[j];
						if (tilePath.officialRating == end) { /* si c'est le cas, on stocke la case de départ et on quitte en attendant la suite du coup */
							startTile = start;
							actualMove = 1;
							middleTile = end;
							movePawnOnBoard(start, end, &boardGame);
							return 2;
						}
						j++;
					}
				}
			}
			i++;
		}
		return 0; /* si on n'a pas touvé de case de départ ou de path correspondant, alors le coup n'est pas valide */
	}
}

int playMoveXY(int x1, int y1, int x2, int y2) {
	BoardTile c1 = getTilePosition(x1, y1, boardGame);
	BoardTile c2 = getTilePosition(x2, y2, boardGame);
	return playMove(c1.officialRating, c2.officialRating);
}


int startTurn() {
	if (!actualMove) {
		
		if(boardGame.turn.color == boardGame.player1.color)
			boardGame.turn = boardGame.player2;
		else
			boardGame.turn = boardGame.player1;
		return 1;
		
	}
	return 0;
}

int saveGame(char * filename) {
	int i;
	FILE* fichier;

	fichier = fopen(filename, "w");

	if (fichier) {

		if (boardGame.player1.color == white) {
			fprintf(fichier, "%d\t 1\n", boardGame.player1);
		} else {
			if (boardGame.player1.color == black) {
				fprintf(fichier, "%d\t 0\n", boardGame.player1);
			}
		}

		if (boardGame.player2.color == white) {
			fprintf(fichier, "%d\t 1\n", boardGame.player2);
		} else {
			if (boardGame.player2.color == black) {
				fprintf(fichier, "%d\t 0\n", boardGame.player2);
			}
		}
		if (boardGame.turn.color == boardGame.player1.color) {
			fprintf(fichier, "1\n");
		} else {
			fprintf(fichier, "2\n");
		}
		for (i = 1; i <= 50; i++) {
			if (boardGame.tiles[i].pawn.color == white) { //color = 1 si white
				fprintf(fichier, "%d\t %d\t %d\t %d\t %d\t 0\t %d\t %d\t 1\n",
						boardGame.tiles[i].officialRating,
						boardGame.tiles[i].isHighlighted, boardGame.tiles[i].x,
						boardGame.tiles[i].y, boardGame.tiles[i].isFree,
						boardGame.tiles[i].pawn.isHighlighted,
						boardGame.tiles[i].pawn.isKing,
						boardGame.tiles[i].pawn.isKing);
			} else {
				if (boardGame.tiles[i].pawn.color == black) { //color = 0 si black
					fprintf(fichier,
							"%d\t %d\t %d\t %d\t %d\t 0\t %d\t %d\t 0\n",
							boardGame.tiles[i].officialRating,
							boardGame.tiles[i].isHighlighted, boardGame.tiles[i].x,
							boardGame.tiles[i].y, boardGame.tiles[i].isFree,
							boardGame.tiles[i].pawn.isHighlighted,
							boardGame.tiles[i].pawn.isKing,
							boardGame.tiles[i].pawn.isKing);

				}
			}
		}
		//fprintf(fichier,"LoL %d", p.tiles[40].color);
		fclose(fichier);
		printf("Sauvegarde reussi \n");
		return 1;
	} else {
		printf("Erreur lors de l'ouverture de fichier \n");
		return 0;
	}
}

int loadGame(char * filename) {
	Player p1;
	Player p2;

	int p1Color, p2Color, turncolor, notationOff, surbrillance, x, y, isFree, tileColor,
			highlightPawn, isKing, pawnColor, i;
	FILE* fichier;
	fichier = fopen(filename, "r");

	if (fichier) {
		//Recuperation donnees joueur 1
		fscanf(fichier, "%d\n", &p1Color);
		if (p1Color == 1) {
			boardGame.player1.color = white;
		} else {
			boardGame.player1.color = black;
		}

		//Recuperation donnees joueur 2
		fscanf(fichier, "%d\n", &p2Color);
		if (p2Color == 1) {
			boardGame.player2.color = white;
		} else {
			boardGame.player2.color = black;
		}

		//Recuperation donnees turn
		fscanf(fichier, "%d\n", &turncolor);
		if (turncolor == 1) {
			boardGame.turn.color = boardGame.player1.color;
		} else {
			boardGame.turn.color = boardGame.player2.color;
		}

		//Recuperation donnees tiles
		for (i = 1; i <= 50; i++) {
			fscanf(fichier, "%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
					&notationOff, &surbrillance, &x, &y, &isFree,
					&tileColor, &highlightPawn, &isKing, &pawnColor);
			if (pawnColor == 1) {
				boardGame.tiles[i].officialRating = notationOff;
				boardGame.tiles[i].isHighlighted = surbrillance;
				boardGame.tiles[i].x = x;
				boardGame.tiles[i].y = y;
				boardGame.tiles[i].isFree = isFree;
				boardGame.tiles[i].color = black;
				boardGame.tiles[i].pawn.isHighlighted = highlightPawn;
				boardGame.tiles[i].pawn.isKing = isKing;
				boardGame.tiles[i].pawn.color = white;
			} else {
				boardGame.tiles[i].officialRating = notationOff;
				boardGame.tiles[i].isHighlighted = surbrillance;
				boardGame.tiles[i].x = x;
				boardGame.tiles[i].y = y;
				boardGame.tiles[i].isFree = isFree;
				boardGame.tiles[i].color = black;
				boardGame.tiles[i].pawn.isHighlighted = highlightPawn;
				boardGame.tiles[i].pawn.isKing = isKing;
				boardGame.tiles[i].pawn.color = black;
			}
		}
		printf("Chargement termine avec succes \n");
		return 1;
	} else {
		printf("Erreur lors de l'ouverture du fichier \n");
		return 0;
	}
}

void initGame() {
	Player player1;
	Player player2;

	boardGame = newBoard(player1, player2);
}

Board getBoard() {
	return boardGame;
}

int isFinished() {
	return isWon(boardGame);
}
