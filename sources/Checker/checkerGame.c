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

int highlightPossibleMovesXY(int x, int y) {
	BoardTile c = getTilePosition(x, y, boardGame);
	return highlightPossibleMoves(c.officialRating);
}

int startTurn() {
	if (!actualMove) {
		possibleMoves = getMaxMoves(getMove(boardGame.turn, boardGame)); /* on met à jour le tableau des coups possibles */
		if (numberMoves(possibleMoves) == 0) { // si on ne peut pas jouer, on passe la main.
			if(boardGame.turn.color == boardGame.player1.color)
				boardGame.turn = boardGame.player2;
			else
				boardGame.turn = boardGame.player1;
			return 1;
		}
	}
	return 0;
}

/*void jouer_turn_ia() {
	resetHighlight(&boardGame);
	coup c = jouerIA(boardGame, difficulty);
	applyMove(c, &boardGame);
	highlightTile(c.oldTile,&boardGame);
	int i;
	for(i = 0; i < c.noTaken; i++) {
		highlightTile(c.path[i].officialRating,&boardGame);
	}
	highlightPawn(c.newTile, &boardGame);
}*/

void setDifficulty(int i) {
	difficulty = i;
}

void highlightPlayablePawns() {
	resetHighlight(&boardGame);
	if(!actualMove) {
		possibleMoves = getMaxMoves(getMove(boardGame.turn, boardGame));
	}
	int i = 0;
	int n = numberMoves(possibleMoves);
	for (i = 0; i < n; i++) { /* On parcours toutes les tiles de départ possibles et on les met en surbrillance */
		highlightPawn(possibleMoves[i].oldTile, &boardGame);
	}
}

int highlightPossibleMoves(int t) {
	resetHighlight(&boardGame);
	int res = 0;
	int i = 0;
	int n = numberMoves(possibleMoves);
	int currentTile = t;
	if (actualMove) {
		t = startTile;
	}

	int currentFoundTile = 0;
	for (i = 0; i < n; i++) { /* On parcours tous les coups */
		Move m = possibleMoves[i];
		if (m.oldTile == t) { /* si la case de départ d'un coup correspond à celle qu'on cherche */
			BoardTile *tiles = m.path;
			int noTile = m.noTaken;
			int j = 0;
			while (j < noTile) { /* on met en surbrillance toutes les tiles par lesquelles passe le coup */
				int highlightedTile = tiles[j].officialRating;
				if (currentFoundTile)
					highlightTile(highlightedTile, &boardGame);
				if (highlightedTile == currentTile)
					currentFoundTile = 1;
				j++;
			}
			highlightTile(m.newTile, &boardGame);
			res = 1;
		}
	}
	return res;
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

/*
 * POSITION 1: x-1,y-1
 * POSITION 2: x+1,y-1
 * POSITION 3: x-1,y+1
 * POSITION 4: x+1,y+1
 */

/* retourne les coups possibles pour un pawn */
Move *possibleMove(const BoardTile t, const Board b) {
	Move *move = calloc(NOMOVES, sizeof(Move));
	Board nextBoard = b;
	int cntMove = 0;
	BoardTile actualTile = t;
	Color adversary = (t.pawn.color == white) ? black : white;

	/* conditions de départ */
	Move actualMove;
	actualMove.oldTile = actualTile.officialRating;
	actualMove.noTaken = 0;
	actualMove.type = capture;
	actualMove.path[actualMove.noTaken++] = actualTile;

	/* pour signaler qu'on est dans une rafle */
	int newSeries = 0;
	int ended = 0;
	int lastPosition = 0;

	/* quand on est sur la case de départ on marque l'element qu'on va visiter
	 * ainsi on ne reparcours pas une deuxieme fois quand on revient durant le backtrack
	 */
	BoardTile avoidStartTile[5];
	int cntAvoidStartTile = 0;

	/*
	 * quand on est sur une case pendant une prise, on marque les pawns alentours qu'on a visité
	 * au cas ou il y a plusieurs choix possibles
	 */
	BoardTile avoidPath[5];
	int cntAvoidPath = 0;

	/* ---------------------------------------------------------------------------
	 * stratégie:
	 *
	 * 		       |       |
	 *         1   |       |   2				On teste d'abord les tiles
	 * 		_______|_______|_______				dans l'ordre indiqué toujours
	 * 		       | case  |					par rapport à la case courante
	 *             |courant|
	 * 		_______|_______|_______
	 *		       |       |
	 * 		   3   |       |   4
	 *             |       |
	 *
	 *
	 *
	 * ---------------------------------------------------------------------------
	 */

	/* toTest est la case qu'on veut prendre s'il y a un pawn du joueur adverse dessus */
	BoardTile toTest = getTileSilent(actualTile.x-1,actualTile.y-1,nextBoard);

	while(!ended) {

		/* POSITION 1 */
		if((toTest.isFree == 0)
				&& (toTest.pawn.color == adversary)
				&& (isTakeable(toTest.officialRating,&nextBoard) == 1)
				&& ((getTileSilent(toTest.x-1, toTest.y-1, nextBoard).isFree)
						|| moveIsIncluded(getTileSilent(toTest.x-1, toTest.y-1, nextBoard),actualMove.path,actualMove.noTaken))
				&& (!moveIsIncluded(toTest, actualMove.taken, actualMove.noTaken))
				&& (getTileSilent(toTest.x-1, toTest.y-1, nextBoard).officialRating != 0)
				&& (toTest.officialRating != lastPosition)
				&& (!moveIsIncluded(toTest, avoidPath, cntAvoidPath))) {
			if((actualTile.officialRating == actualMove.oldTile)
					&& (actualMove.noTaken <= 1)
					&& (moveIsIncluded(toTest, avoidStartTile, cntAvoidStartTile))) {
				break;
			} else {
				newSeries = 1;
				lastPosition = 0;
				/* si je suis sur la case de départ, j'ajoute aTester a la liste des tiles a eviter */
				if ((actualTile.officialRating == actualMove.oldTile)
						&& (actualMove.noTaken <= 1)) {
					avoidStartTile[cntAvoidStartTile++] = toTest;
				}
				/* nouvelle_position est la case ou on atteri apres avoir mangé aTester */
				actualTile = getTileSilent(toTest.x-1, toTest.y-1, nextBoard);
				actualMove.newTile = actualTile.officialRating;
				actualMove.taken[actualMove.noTaken - 1] = toTest;
				actualMove.path[actualMove.noTaken++] = actualTile;

				/* on va reessayer le test sur la POSITION 1 de aTester */
				toTest = getTileSilent(actualTile.x-1,actualTile.y-1, nextBoard);
			}
		} else {
			toTest = getTileSilent(actualTile.x+1,actualTile.y-1,nextBoard);
			/* POSITION 2 */
			if((toTest.isFree == 0)
					&& (toTest.pawn.color == adversary)
					&& (isTakeable(toTest.officialRating,&nextBoard) == 1)
					&& ((getTileSilent(toTest.x+1, toTest.y-1, nextBoard).isFree)
							|| moveIsIncluded(getTileSilent(toTest.x+1, toTest.y-1, nextBoard), actualMove.path, actualMove.noTaken))
					&& (!moveIsIncluded(toTest, actualMove.taken, actualMove.noTaken))
					&& (getTileSilent(toTest.x+1, toTest.y-1, nextBoard).officialRating != 0)
					&& (toTest.officialRating != lastPosition)
					&& (!moveIsIncluded(toTest, avoidPath, cntAvoidPath))) {
				if((actualTile.officialRating == actualMove.oldTile)
						&& (actualMove.noTaken <= 1)
						&& (moveIsIncluded(toTest, avoidStartTile, cntAvoidStartTile))) {
					break;
				} else {
					newSeries = 1;
					lastPosition = 0;
					/* si je suis sur la case de départ, j'ajoute aTester a la liste des tiles a eviter */
					if ((actualTile.officialRating == actualMove.oldTile)
						&& (actualMove.noTaken <= 1)){
						avoidStartTile[cntAvoidStartTile++] = toTest;
					}
					actualTile = getTileSilent(toTest.x+1, toTest.y-1, nextBoard);
					actualMove.newTile = actualTile.officialRating;
					actualMove.taken[actualMove.noTaken - 1] = toTest;
					actualMove.path[actualMove.noTaken++] = actualTile;

					toTest = getTileSilent(actualTile.x-1,actualTile.y-1, nextBoard);
				}
			} else {
				toTest = getTileSilent(actualTile.x-1,actualTile.y+1,nextBoard);
				/* POSITION 3 */
				if((toTest.isFree == 0)
						&& (toTest.pawn.color == adversary)
						&& (isTakeable(toTest.officialRating,&nextBoard) == 1)
						&& ((getTileSilent(toTest.x-1, toTest.y+1, nextBoard).isFree)
								|| moveIsIncluded(getTileSilent(toTest.x-1, toTest.y+1, nextBoard),actualMove.path,actualMove.noTaken))
						&& (!moveIsIncluded(toTest, actualMove.taken, actualMove.noTaken))
						&& (getTileSilent(toTest.x-1, toTest.y+1, nextBoard).officialRating != 0)
						&& (toTest.officialRating != lastPosition)
						&& (!moveIsIncluded(toTest, avoidPath, cntAvoidPath))) {
					if((actualTile.officialRating == actualMove.oldTile)
							&& (actualMove.noTaken <= 1)
							&& (moveIsIncluded(toTest, avoidStartTile, cntAvoidStartTile))) {
						break;
					} else {
						newSeries = 1;
						lastPosition = 0;
						/* si je suis sur la case de départ, j'ajoute aTester a la liste des tiles a eviter */
						if ((actualTile.officialRating == actualMove.oldTile)
							&& (actualMove.noTaken <= 1)){
							avoidStartTile[cntAvoidStartTile++] = toTest;
						}
						actualTile = getTileSilent(toTest.x-1, toTest.y+1, nextBoard);
						actualMove.newTile = actualTile.officialRating;
						actualMove.taken[actualMove.noTaken - 1] = toTest;
						actualMove.path[actualMove.noTaken++] = actualTile;

						toTest = getTileSilent(actualTile.x-1,actualTile.y-1, nextBoard);
					}
				} else {
					toTest = getTileSilent(actualTile.x+1,actualTile.y+1,nextBoard);
					/* POSITION 4 */
					if((toTest.isFree == 0)
							&& (toTest.pawn.color == adversary)
							&& (isTakeable(toTest.officialRating,&nextBoard) == 1)
							&& ((getTileSilent(toTest.x+1, toTest.y+1, nextBoard).isFree)
									|| moveIsIncluded(getTileSilent(toTest.x+1, toTest.y+1, nextBoard),actualMove.path,actualMove.noTaken))
							&& (!moveIsIncluded(toTest, actualMove.taken, actualMove.noTaken))
							&& (getTileSilent(toTest.x+1, toTest.y+1, nextBoard).officialRating != 0)
							&& (toTest.officialRating != lastPosition)
							&& (!moveIsIncluded(toTest, avoidPath, cntAvoidPath))) {
						if((actualTile.officialRating == actualMove.oldTile)
								&& (actualMove.noTaken <= 1)
								&& (moveIsIncluded(toTest, avoidStartTile, cntAvoidStartTile))) {
							break;
						} else {
							newSeries = 1;
							lastPosition = 0;
							/* si je suis sur la case de départ, j'ajoute aTester a la liste des tiles a eviter */
							if ((actualTile.officialRating == actualMove.oldTile)
								&& (actualMove.noTaken <= 1)){
								avoidStartTile[cntAvoidStartTile++] = toTest;
							}
							actualTile = getTileSilent(toTest.x+1, toTest.y+1, nextBoard);
							actualMove.newTile = actualTile.officialRating;
							actualMove.taken[actualMove.noTaken - 1] = toTest;
							actualMove.path[actualMove.noTaken++] = actualTile;

							toTest = getTileSilent(actualTile.x-1,actualTile.y-1, nextBoard);
						}
					} else {	/* j'enregistre le coup et je backtrack  si possible, sinon je retourne le tableau de coups */

						lastPosition = actualMove.taken[actualMove.noTaken - 2].officialRating;
						/* si on a rien au bout d'une rafle et si on est pas dans la case 0, on l'ajoute a cp */
						if(newSeries && actualMove.oldTile != 0 && actualMove.newTile != 0) {
							move[cntMove++] = actualMove;
							newSeries = 0;
						}
						if(actualMove.noTaken <= 1) { /* si y'a plus de taken en fait */
							ended = 1;
						}
						/* et on backtracke */

						avoidPath[cntAvoidPath++] = actualMove.taken[actualMove.noTaken - 2];
						actualMove.noTaken--;
						actualTile = actualMove.path[actualMove.noTaken - 1];
						toTest = getTileSilent(actualTile.x-1,actualTile.y-1, nextBoard);
					}
				}
			}
		}
	}
	/* on ajoute aussi les deplacements possibles */
	Move *movements = getMovement(t, b);
	while((movements->oldTile != 0) && (movements->newTile != 0)) {
		move[cntMove++] = *movements;
		movements++;
	}
	/* pour marquer la fin de tableau */
	Move dummy;
	dummy.oldTile = 0;
	dummy.newTile = 0;
	move[cntMove++] = dummy;
	return move;
}

int possibleTilePosition(int c, int diag, Board b) {
	int x = b.tiles[c].x;
	int y = b.tiles[c].y;
	switch (diag) {
		case 1:
			while (x > 0 && y > 0) {
				x--;
				y--;
				BoardTile toTake = getTileSilent(x, y, b);
				if (!toTake.isFree) { /* si on trouve une case non libre */
					if (toTake.pawn.color != b.tiles[c].pawn.color) { /* soit elle à un pawn adversaire */
						return getTileSilent(x, y, b).officialRating;
					} else { /* soit un pawn de la même color */
						return 0;
					}
				}
			}
			return 0;
			break;
		case 2:
			while (x <= 10 && y > 0) {
				x++;
				y--;
				BoardTile toTake = getTileSilent(x, y, b);
				if (!toTake.isFree) { /* si on trouve une case non libre */
					if (toTake.pawn.color != b.tiles[c].pawn.color) { /* soit elle à un pawn adversaire */
						return getTileSilent(x, y, b).officialRating;
					} else { /* soit un pawn de la même color */
						return 0;
					}
				}
			}
			return 0;
			break;
		case 3:
			while (x > 0 && y <= 10) {
				x--;
				y++;
				BoardTile toTake = getTileSilent(x, y, b);
				if (!toTake.isFree) { /* si on trouve une case non libre */
					if (toTake.pawn.color != b.tiles[c].pawn.color) { /* soit elle à un pawn adversaire */
						return getTileSilent(x, y, b).officialRating;
					} else { /* soit un pawn de la même color */
						return 0;
					}
				}
			}
			return 0;
			break;
		case 4:
			while (x <= 10 && y <= 10) {
				x++;
				y++;
				BoardTile toTake = getTileSilent(x, y, b);
				if (!toTake.isFree) { /* si on trouve une case non libre */
					if (toTake.pawn.color != b.tiles[c].pawn.color) { /* soit elle à un pawn adversaire */
						return getTileSilent(x, y, b).officialRating;
					} else { /* soit un pawn de la même color */
						return 0;
					}
				}
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}


Move *completeKingMove(const Move m, int mvt, Board b) {
	Move *res = calloc(100, sizeof(Move));
	int cptRes = 0;
	Board nextBoard;
	if (mvt == 1 || mvt == 4) { // si on est dur la diagonale 1-4
		int diag2 = possibleTilePosition(m.newTile, 2, b); // on cherche sur les diagonales perpendiculaires
		int diag3 = possibleTilePosition(m.newTile, 3, b);
		if (diag2) { // si on peut prendre un pawn sur la diagonale 2
			BoardTile takenTile = b.tiles[diag2];
			int x = takenTile.x + 1;
			int y = takenTile.y - 1;
			while (x <= 10 && y > 0 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move = m;
				move.taken[move.noTaken] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.noTaken++;
				move.path[move.noTaken] = newTile;
				move.newTile = newTile.officialRating;
				res[cptRes++] = move;

				if (possibleTilePosition(newTile.officialRating, 1, b) /* si il n'y a pas d'aures taken sur la diagonale, on ajoute le coup */
						|| possibleTilePosition(newTile.officialRating, 4, b)) {
					nextBoard = b;
					capturePawnOnBoard(takenTile.officialRating, &nextBoard);
					movePawnOnBoard(m.newTile, newTile.officialRating, &nextBoard);
					Move *completedMove = completeKingMove(move, 2, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						res[cptRes++] = completedMove[i];
					}
				}
				x++;
				y--;
			}
		}
		if (diag3) { // si on peut prendre un pawn sur la diagonale 3
			BoardTile takenTile = b.tiles[diag3];
			int x = takenTile.x - 1;
			int y = takenTile.y + 1;
			while (x > 0 && y <= 10 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move = m;
				move.taken[move.noTaken] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.noTaken++;
				move.path[move.noTaken] = newTile;
				move.newTile = newTile.officialRating;
				res[cptRes++] = move;
				if (!(possibleTilePosition(newTile.officialRating, 1, b) /* si il n'y a pas d'aures taken sur la diagonale, on ajoute le coup */
						|| possibleTilePosition(newTile.officialRating, 4, b))) {
					nextBoard = b;
					capturePawnOnBoard(takenTile.officialRating, &nextBoard);
					movePawnOnBoard(m.newTile, newTile.officialRating, &nextBoard);
					Move *completedMove = completeKingMove(move, 3, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						res[cptRes++] = completedMove[i];
					}
				}
				x--;
				y++;
			}
		}
	} else { // sinon on est sur la diagonale 2-3
		int diag1 = possibleTilePosition(m.newTile, 1, b); // on cherche sur les diagonales perpendiculaires
		int diag4 = possibleTilePosition(m.newTile, 4, b);
		if (diag1) { // si on peut prendre un pawn sur la diagonale 1
			BoardTile takenTile = b.tiles[diag1];
			int x = takenTile.x - 1;
			int y = takenTile.y - 1;
			while (x > 0 && y > 0 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move = m;
				move.taken[move.noTaken] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.noTaken++;
				move.path[move.noTaken] = newTile;
				move.newTile = newTile.officialRating;
				res[cptRes++] = move;
				if (!(possibleTilePosition(newTile.officialRating, 2, b) /* si il n'y a pas d'aures taken sur la diagonale, on ajoute le coup */
						|| possibleTilePosition(newTile.officialRating, 3, b))) {
					nextBoard = b;
					capturePawnOnBoard(takenTile.officialRating, &nextBoard);
					movePawnOnBoard(m.newTile, newTile.officialRating, &nextBoard);
					Move *completedMove = completeKingMove(move, 1, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						res[cptRes++] = completedMove[i];
					}
				}
				x--;
				y--;
			}
		}
		if (diag4) { // si on peut prendre un pawn sur la diagonale 3
			BoardTile takenTile = b.tiles[diag4];
			int x = takenTile.x + 1;
			int y = takenTile.y + 1;
			while (x <= 10 && y <= 10 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move = m;
				move.taken[move.noTaken] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.noTaken++;
				move.path[move.noTaken] = newTile;
				move.newTile = newTile.officialRating;
				res[cptRes++] = move;
				if (!(possibleTilePosition(newTile.officialRating, 2, b) /* si il n'y a pas d'aures taken sur la diagonale, on ajoute le coup */
						|| possibleTilePosition(newTile.officialRating, 3, b))) {
					nextBoard = b;
					capturePawnOnBoard(takenTile.officialRating, &nextBoard);
					movePawnOnBoard(m.newTile, newTile.officialRating, &nextBoard);
					Move *completedMove = completeKingMove(move, 4, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						res[cptRes++] = completedMove[i];
					}
				}
				x++;
				y++;
			}
		}
	}

	Move dummy;
	dummy.oldTile = 0;
	dummy.newTile = 0;
	res[cptRes++] = dummy;

	return res;
}

/**
 * \brief Recherche les coups possibles pour une dame.
 */
Move *possibleKingMove(const BoardTile t, const Board b) {
	Move *moves = calloc(NOMOVES, sizeof(Move));
	Board nextBoard = b;
	int cntMove = 0;
	BoardTile actualTile = t;
	Color adversaire = (t.pawn.color == white) ? black : white;
	MoveType captures = capture;

	/* conditions de départ */
	Move actualMove;
	actualMove.oldTile = actualTile.officialRating;
	actualMove.noTaken = 0;
	actualMove.type = capture;
	actualMove.path[actualMove.noTaken++] = actualTile;

	/* pour signaler qu'on est dans une rafle */
	int newSeries = 0;
	int lastDoneSearch = 0; /* lorsqu'on revient sur la case de départ, on fait une derniere recherche */
	int ended = 0;
	int lastPosition = 0;

	/* quand on est sur la case de départ on marque l'element qu'on va visiter
	 * ainsi on ne reparcours pas une deuxieme fois quand on revient durant le backtrack
	 */
	BoardTile toAvoid[5];
	int cntAvoid = 0;

	/* ---------------------------------------------------------------------------
	 * stratégie:
	 *
	 * 		       |       |
	 *         1   |       |   2				On teste d'abord les diagonales
	 * 		_______|_______|_______				dans l'ordre indiqué toujours
	 * 		       | case  |					par rapport à la case courante
	 *             |courant|
	 * 		_______|_______|_______
	 *		       |       |
	 * 		   3   |       |   4
	 *             |       |
	 *
	 *
	 *
	 * ---------------------------------------------------------------------------
	 */

	while (!ended) {
		/* ---------------------- Diagonale 1 ----------------------------- */
		int tookTile = possibleTilePosition(t.officialRating, 1, b);
		BoardTile behindTile = getTileSilent(
				b.tiles[tookTile].x - 1, b.tiles[tookTile].y - 1, b);
		if (!tookTile || !behindTile.isFree
				|| behindTile.officialRating == 0) { /* si la diagonale est vide, ou qu'on ne peut pas prendre le pawn */
			int x = t.x - 1;
			int y = t.y - 1;
			while (x > 0 && y > 0 && getTileSilent(x, y, b).isFree) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pawn. */
				BoardTile newTile = getTileSilent(x, y, b);
				if (newTile.officialRating != 0) {
					Move move;
					move.type = '-';
					move.oldTile = t.officialRating;
					move.noTaken = 0;
					move.newTile = newTile.officialRating;
					moves[cntMove++] = move; /* on ajoute tous les coups à la liste */
				}
				x--;
				y--;
			}
		} else { /* sinon, il y a un pawn à prendre sur la diagonale */
			BoardTile takenTile = b.tiles[tookTile];
			int x = takenTile.x - 1;
			int y = takenTile.y - 1;
			while (x > 0 && y > 0 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move;
				move.type = capture;
				move.oldTile = t.officialRating;
				move.noTaken = 1;
				move.taken[0] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.path[0] = t;
				move.path[1] = newTile;
				move.newTile = newTile.officialRating;

				nextBoard = b;
				capturePawnOnBoard(takenTile.officialRating, &nextBoard);
				movePawnOnBoard(t.officialRating,
						newTile.officialRating, &nextBoard);

				moves[cntMove++] = move;

				if (possibleTilePosition(newTile.officialRating, 2,nextBoard) 
						|| possibleTilePosition(newTile.officialRating, 3, nextBoard)) { /* si il y a une prise possible sur la diagonale, on l'ajoute à la liste */
					Move *completedMove = completeKingMove(move, 1, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						moves[cntMove++] = completedMove[i];
					}
					free(completedMove);
				}
				x--;
				y--;
			}
		}

		/* ---------------------- Diagonale 2 ----------------------------- */

		tookTile = possibleTilePosition(t.officialRating, 2, b);
		behindTile = getTileSilent(b.tiles[tookTile].x + 1, b.tiles[tookTile].y - 1, b);
		if (!tookTile || !behindTile.isFree
				|| behindTile.officialRating == 0) { /* si la diagonale est vide */
			int x = t.x + 1;
			int y = t.y - 1;
			while (x <= 10 && y > 0 && getTileSilent(x, y, b).isFree) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pawn. */
				BoardTile newTile = getTileSilent(x, y, b);
				if (newTile.officialRating != 0) {
					Move move;
					move.type = '-';
					move.oldTile = t.officialRating;
					move.noTaken = 0;
					move.newTile = newTile.officialRating;
					moves[cntMove++] = move; /* on ajoute tous les coups à la liste */
				}
				x++;
				y--;
			}
		} else { /* sinon, il y a un pawn à prendre sur la diagonale */
			BoardTile takenTile = b.tiles[tookTile];
			int x = takenTile.x + 1;
			int y = takenTile.y - 1;
			while (x <= 10 && y > 0 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move;
				move.type = capture;
				move.oldTile = t.officialRating;
				move.noTaken = 1;
				move.taken[0] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.path[0] = t;
				move.path[1] = newTile;
				move.newTile = newTile.officialRating;

				nextBoard = b;
				capturePawnOnBoard(takenTile.officialRating, &nextBoard);
				movePawnOnBoard(t.officialRating, newTile.officialRating, &nextBoard);
				moves[cntMove++] = move;

				if (possibleTilePosition(newTile.officialRating, 1, nextBoard) 
						|| possibleTilePosition(newTile.officialRating, 4, nextBoard)) {
					Move *completedMove = completeKingMove(move, 2, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						moves[cntMove++] = completedMove[i];
					}
					free(completedMove);
				}
				x++;
				y--;
			}
		}

		/* ---------------------- Diagonale 3 ----------------------------- */

		tookTile = possibleTilePosition(t.officialRating, 3, b);
		behindTile = getTileSilent(b.tiles[tookTile].x - 1, b.tiles[tookTile].y + 1, b);
		if (!tookTile || !behindTile.isFree
				|| behindTile.officialRating == 0) { /* si la diagonale est vide */
			int x = t.x - 1;
			int y = t.y + 1;
			while (x > 0 && y <= 10 && getTileSilent(x, y, b).isFree) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pawn. */
				BoardTile newTile = getTileSilent(x, y, b);
				if (newTile.officialRating != 0) {
					Move move;
					move.type = '-';
					move.oldTile = t.officialRating;
					move.noTaken = 0;
					move.newTile = newTile.officialRating;
					moves[cntMove++] = move; /* on ajoute tous les coups à la liste */
				}
				x--;
				y++;
			}
		} else { /* sinon, il y a un pawn à prendre sur la diagonale */
			BoardTile takenTile = b.tiles[tookTile];
			int x = takenTile.x - 1;
			int y = takenTile.y + 1;
			while (x > 0 && y <= 10 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move cp;
				cp.type = capture;
				cp.oldTile = t.officialRating;
				cp.noTaken = 1;
				cp.taken[0] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				cp.path[0] = t;
				cp.path[1] = newTile;
				cp.newTile = newTile.officialRating;
				nextBoard = b;
				capturePawnOnBoard(takenTile.officialRating, &nextBoard);
				movePawnOnBoard(t.officialRating, newTile.officialRating, &nextBoard);
				moves[cntMove++] = cp;

				if (possibleTilePosition(newTile.officialRating, 1, nextBoard) 
						|| possibleTilePosition(newTile.officialRating, 4, nextBoard)) {
					Move *completedMove = completeKingMove(cp, 3, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						moves[cntMove++] = completedMove[i];
					}
					free(completedMove);
				}
				x--;
				y++;
			}
		}

		/* ---------------------- Diagonale 4 ----------------------------- */

		tookTile = possibleTilePosition(t.officialRating, 4, b);
		behindTile = getTileSilent(b.tiles[tookTile].x + 1,
				b.tiles[tookTile].y + 1, b);
		if (!tookTile || !behindTile.isFree
				|| behindTile.officialRating == 0) { /* si la diagonale est vide */
			int x = t.x + 1;
			int y = t.y + 1;
			while (x <= 10 && y <= 10 && getTileSilent(x, y, b).isFree) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pawn. */
				BoardTile newTile = getTileSilent(x, y, b);
				if (newTile.officialRating != 0) {
					Move move;
					move.type = '-';
					move.oldTile = t.officialRating;
					move.noTaken = 0;
					move.newTile = newTile.officialRating;
					moves[cntMove++] = move; /* on ajoute tous les coups à la liste */
				}
				x++;
				y++;
			}
		} else { /* sinon, il y a un pawn à prendre sur la diagonale */
			BoardTile takenTile = b.tiles[tookTile];
			int x = takenTile.x + 1;
			int y = takenTile.y + 1;
			while (x <= 10 && y <= 10 && getTileSilent(x, y, b).isFree) { /* dans ce cas, on parcours les tiles de la diagonale derrière la prise */
				Move move;
				move.type = capture;
				move.oldTile = t.officialRating;
				move.noTaken = 1;
				move.taken[0] = takenTile;
				BoardTile newTile = getTileSilent(x, y, b);
				move.path[0] = t;
				move.path[1] = newTile;
				move.newTile = newTile.officialRating;

				nextBoard = b;
				capturePawnOnBoard(takenTile.officialRating, &nextBoard);
				movePawnOnBoard(t.officialRating, newTile.officialRating, &nextBoard);
				moves[cntMove++] = move;

				if (possibleTilePosition(newTile.officialRating, 2, nextBoard) 
						|| possibleTilePosition(newTile.officialRating, 3, nextBoard)) { /* si il y a d'aures taken sur la diagonale */
					Move *completedMove = completeKingMove(move, 4, nextBoard);
					int noMoves = numberMoves(completedMove);
					int i;
					for (i = 0; i < noMoves; i++) {
						moves[cntMove++] = completedMove[i];
					}
					free(completedMove);
				}
				x++;
				y++;
			}
		}
		ended = 1;
	}

	//free(deplacements);

	/* pour marquer la fin de tableau */
	Move dummy;
	dummy.oldTile = 0;
	dummy.newTile = 0;
	moves[cntMove++] = dummy;
	return moves;
}

/* retourne les coups possibles de tout les pawns */
Move *getMove(const Player j, const Board b) {
	//coup cp[500];
	Move *move = calloc(500, sizeof(Move));
	BoardTile t;
	int cntMove = 0;
	int i;
	int k = 0;
	/* j'itere sur toutes les tiles du Board */
	for (i = 1; i < 51; i++) {
		t = b.tiles[i];
		/* si dans cette case y'a un pawn du joueur j
		 * on recupere tout les coups possibles de ce pawn
		 */
		if ((!t.isFree) && (t.pawn.color == j.color)) {
			Move *aAjouter;
			if (t.pawn.isKing) {
				aAjouter = possibleKingMove(t, b);
			} else {
				aAjouter = possibleMove(t, b);
			}
			/* recopie les coups possibles de ce pawn dans cp */
			while ((aAjouter[k].oldTile != 0) && (aAjouter[k].newTile != 0)) {
				move[cntMove++] = aAjouter[k++];
			}
			k = 0;
		}
	}
	/* pour marquer la fin de tableau */
	Move dummy;
	dummy.oldTile = 0;
	dummy.newTile = 0;
	move[cntMove++] = dummy;

	Move *result = calloc(cntMove, sizeof(Move));
	memcpy(&result, &move, sizeof result);

	return result;
}

/* retourne les coups max du tableau en entrée */
Move *getMaxMoves(const Move *move) {
	int i = 0;
	//coup coups_max[noMoves];
	Move *maxMoves = calloc(NOMOVES, sizeof(Move));
	int cntMaxMoves = 0;
	int noMaxTaken = 0;

	/* je parcours une premiere fois cp pour trouver le nb de taken max rencontré */
	while ((move[i].oldTile != 0) && (move[i].newTile != 0)) {
		if (move[i].noTaken > noMaxTaken) {
			noMaxTaken = move[i].noTaken;
		}
		i++;
	}

	/* je reparcours cp, cette fois je ne prend que les coups qui ont un
	 * nb de taken égal au nb_taken_max
	 */
	i = 0;
	while ((move[i].oldTile != 0) && (move[i].newTile != 0)) {
		if (move[i].noTaken == noMaxTaken) {
			maxMoves[cntMaxMoves++] = move[i];
		}
		i++;
	}

	/* je marque la fin de tableau */
	Move dummy;
	dummy.oldTile = 0;
	dummy.newTile = 0;
	maxMoves[cntMaxMoves++] = dummy;

	Move *result = calloc(cntMaxMoves, sizeof(Move));
	memcpy(&result, &maxMoves, sizeof(result));

	return result;
}

/* retourne les déplacements possible du pawn sur la case c */
Move *getMovement(const BoardTile t, const Board b) {
	Move *moves = calloc(3, sizeof(Move));
	Move *d = moves;
	Board next = b;
	if (t.pawn.color == white) {
		BoardTile tile = getTileSilent(t.x - 1, t.y - 1, next);
		if ((tile.officialRating != 0) && tile.isFree) {
			Move newMove;
			newMove.oldTile = t.officialRating;
			newMove.newTile = tile.officialRating;
			newMove.type = '-';
			*(d++) = newMove;
		}
		BoardTile c2 = getTileSilent(t.x + 1, t.y - 1, next);
		if ((c2.officialRating != 0) && c2.isFree) {
			Move newMove;
			newMove.oldTile = t.officialRating;
			newMove.newTile = c2.officialRating;
			newMove.type = '-';
			*(d++) = newMove;
		}
	} else {
		BoardTile c1 = getTileSilent(t.x - 1, t.y + 1, next);
		if ((c1.officialRating != 0) && c1.isFree) {
			Move newMove;
			newMove.oldTile = t.officialRating;
			newMove.newTile = c1.officialRating;
			newMove.type = '-';
			*(d++) = newMove;
		}
		BoardTile c2 = getTileSilent(t.x + 1, t.y + 1, next);
		if ((c2.officialRating != 0) && c2.isFree) {
			Move newMove;
			newMove.oldTile = t.officialRating;
			newMove.newTile = c2.officialRating;
			newMove.type = '-';
			printf("\n");
			*(d++) = newMove;
		}
	}

	/* je marque la fin du tableau */
	Move dummy;
	dummy.oldTile = 0;
	dummy.newTile = 0;
	*(d++) = dummy;

	return moves;
}

/* retourne 0 si array1 = array2, sinon 1 */
int compMove(Move* array1, Move *array2) {
	Move *p1 = array1;
	Move *p2 = array2;

	while(p1->oldTile != 0) {
		if((p1->oldTile != p2->oldTile)
				|| (p1->newTile != p2->newTile)
				|| (p1->noTaken != p2->noTaken)
				|| (p1->type != p2->type))
			return 1;
		p1++;
		p2++;
	}
	return 0;
}

BoardTile getTileSilent(int x, int y, Board p) {
	if (x < 1 || x > 10 || y < 1 || y > 10) {
		return p.tiles[0];
	}
	if ((x % 2) == (y % 2)) { /* si x et y sont tout les deux pairs (ou impairs), alors c'est une case whitehe */
		return p.tiles[0];
	} else {
		int i;
		for (i = 1; i <= 50; i++) { /* temporairement on fait une recherche dans le tableau, en attendant un algorithme qui offre de meilleures performances */
			BoardTile c = p.tiles[i];
			if (c.x == x && c.y == y) {
				return c;
			}
		}
		return p.tiles[0];
	}
}