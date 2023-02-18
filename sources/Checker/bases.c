/**
 * @file bases.h
 * @author Melissa GRIES
 * @brief Definition of the base elements.
 */

#include "../../headers/Checker/interface.h"
#include "../../headers/Checker/bases.h"

Board newBoard(Player p1, Player p2) {
	Board b;
	int i = 1;
	int x = 2;
	int y = 1;

	p1.color = white;
	p2.color = black;
	b.player1 = p1;
	b.player2 = p2;
	b.turn = p1;
	
	while (i <= 50) { /* on remplit le Board ( bug ici j ai change le 20 en 50)*/
		BoardTile t;
		Pawn pawn;

		pawn.isKing = 0;
		t.officialRating = i;
		t.color = black;
		t.isHighlighted = 0;
		t.x = x;
		t.y = y;

		if (i <= 20) { /* si on est du côté des blacks, on place les pawns */
			t.isFree = 0;
			pawn.color = black;
			pawn.isHighlighted = 0;
			t.pawn = pawn;
		} else if (i > 30) { /* si on est du côté des whites */
			t.isFree = 0;
			pawn.color = white;
			pawn.isHighlighted = 0;
			t.pawn = pawn;
		} else { /* si on est au centre on a des case libres */
			t.isFree = 1;
		}

		b.tiles[i] = t;
		i++;
		x = x + 2;

		if (i % 10 == 6) { /* on détecte les changements de ligne pour décaler x et incrémenter y */
			/*printf("%i mod 10 = %i\n",i,i%10);*/
			x = 1;
			y++;
		} else if (i % 10 == 1) {
			/*printf("%i mod 10 = %i\n",i,i%10);*/
			x = 2;
			y++;
		}
	}

	BoardTile whiteTile;
	whiteTile.color = white;
	whiteTile.isFree = 1;
	whiteTile.officialRating = 0;
	whiteTile.isHighlighted = 0;
	whiteTile.x = 0;
	whiteTile.y = 0;
	b.tiles[0] = whiteTile;

	return b;
}

int movePawnOnBoard(int old_position, int new_position, Board *b) {
	if (old_position < 1 || old_position > 50 || new_position < 1
			|| new_position > 50 || b->tiles[old_position].isFree
			|| !b->tiles[new_position].isFree) {
		return 0;
	} else {
		Pawn pawn = b->tiles[old_position].pawn;
		b->tiles[old_position].isFree = 1;
		b->tiles[new_position].isFree = 0;
		b->tiles[new_position].pawn = pawn;
		return 1;
	}
}

int capturePawnOnBoard(int position, Board *b) {
	if (position < 1 || position > 50 || b->tiles[position].isFree) {
		return 0;
	} else {
		b->tiles[position].isFree = 1;
		return 1;
	}
}

/*void Board_ajouter_coup(Move m, Board *b) {
	int i = b->i;
	if (i < 500) {
		m->historique[i] = m;
		m->i = i + 1;
	}
}*/

BoardTile getTilePosition(int x, int y, Board b) {
	if (x < 1 || x > 10 || y < 1 || y > 10) {
		fprintf(stderr, "Case hors Board (%i,%i)\n", x, y);
		return b.tiles[0];
	}

	if ((x % 2) == (y % 2)) { /* si x et y sont tout les deux pairs (ou impairs), alors c'est une case whitehe */
		return b.tiles[0];
	} else {
		int i;
		for (i = 1; i <= 50; i++) { /* temporairement on fait une recherche dans le tableau, en attendant un algorithme qui offre de meilleures performances */
			BoardTile t = b.tiles[i];
			if (t.x == x && t.y == y) {
				return t;
			}
		}
		return b.tiles[0];
	}
}

void displayTestInfo(BoardTile t) {
		printf("Case [%i] : (%i,%i) color : %i, isFree : %i surbrillance : %i\n",
				t.officialRating, t.x, t.y, t.color, t.isFree, t.isHighlighted);
}

void highlightTile(int number, Board *b) {
	b->tiles[number].isHighlighted = 1;
}

void highlightPawn(int number, Board *b) {
	b->tiles[number].pawn.isHighlighted = 1;
}

void resetHighlight(Board *b) {
	int i;
	for(i = 0; i < 51; i++) {
		b->tiles[i].isHighlighted = 0;
		b->tiles[i].pawn.isHighlighted = 0;
	}
}

void applyMove(Move c, Board *b) {
	BoardTile *tiles = b->tiles;

	if(tiles[c.oldTile].isFree || !tiles[c.newTile].isFree) {
		fprintf(stderr, "Impossible de jouer le coup (%d,%d) : case de départ vide ou case d'arrivée déjà occupée.",c.oldTile,c.newTile);
	} else {
		movePawnOnBoard(c.oldTile, c.newTile, b);	/* on déplace le pawn */

		if(c.type == capture) {	/* puis, si le coup est une prise, on prend le(s) pawn(s) */
			int i;
			for(i = 0; i < c.noTaken; i++) {
				capturePawnOnBoard(c.taken[i].officialRating, b);
			}
		}

		if(b->tiles[c.newTile].pawn.color == white && c.newTile <= 5) { /* puis on teste si le mouvement crée une dame */
			b->tiles[c.newTile].pawn.isKing = 1;
		} else if( b->tiles[c.newTile].pawn.color == black && c.newTile >= 46 ) {
			b->tiles[c.newTile].pawn.isKing = 1;
		}

		if(b->turn.color == b->player1.color) { /* enfin on passe la main au Player suivant */
			b->turn = b->player2;
		} else {
			b->turn = b->player1;
		}
		// @todo printf de debug a supprimer
		printf("\n------------------------\n");
		printf("\nCoup appliqué :\n");
		//printBoardTest(c);
		printf("\n------------------------\n");
	}
}

int isWon(Board b) {
	int i;
	int found = 0; /* on le passe à vrai quand on a trouvé le premier pawn, puis on vérifie que tout les autres pawns sont de la même color */
	Color color;
	for(i = 1; i <= 50; i++ ) {
		if(! b.tiles[i].isFree) {
			if(found) {
				if( color != b.tiles[i].pawn.color) {
					return 0;
				}
			} else {
				found = 1;
				color = b.tiles[i].pawn.color;
			}
		}
	}
	/* si on a parcouru le tout le damier et qu'on n'a pas trouvé deux pawns de colors différentes, alors la partie est terminée */
	return color + 1; /* 1 si c'est les whites, 2 si c'est les blacks. */
}


// @todo Delete this
void printBoardTest(Board b) {
	int i, j;
	printf("\n---------------------\n");
	for(i = 1; i <= 10; i++) {
		printf("|");
		for(j = 1; j <=10 ; j++) {
			BoardTile t = getTilePosition(j, i, b);
			if(t.color != white) {
				if(!t.isFree) {
					if(t.pawn.color == white) {
						if(t.pawn.isHighlighted)
							printf("o");
						else printf("O");
					} else {
						if(t.pawn.isHighlighted)
							printf("x");
						else printf("X");
					}
					if (t.pawn.isKing)
						printf("*");
				} else {
					if (t.isHighlighted)
						printf("-");
					else printf(" ");
				}
			} else {
				printf(" ");
			}
			printf("|");
		}
		printf("\n---------------------\n");
	}
	return;
}

// @TODO delete this too
/* pretty print d'un coup */
void displayMove(const Move c) {
	if ((c.oldTile == 0) && (c.newTile == 0)) {
		/* on tombe normalement jamais dessus mais utile au debug */
		printf("coup bidon");
	} /*else {
		printf("de [%d] vers [%d]\n", c.oldTile, c.newTile);
		printf("parcours du coup:\n");
		int i;
		for (i = 0; i < c.noTaken; i++) {
			print(c.path[i]);
		}
		printf("la position des pawns pris:\n");
		i = 0;
		for (i = 0; i < c.noTaken - 1; i++) {
			print_case(c.taken[i]);
		}
		printf("noTaken: %d\n", c.noTaken - 1);
		printf("type coup: %d\n", c.type);
	}*/
}

// @TODO delete this
/* predicat: est ce que le pawn sur position est prenable ? */
int isTakeable(int position, Board *p) {
	printf("prenabilité de [%d]: %d\n", position, p->tiles[position].isFree);
	if (position < 1 || position > 50 || p->tiles[position].isFree) {
		return 0;
	} else {
		return 1;
	}
}

// @TODO to delete
/* affiche ce qu'il y a dans la liste de coups */
void displayMoveAvailable(Move *l) {
	printf("----------------------------\n");
	printf("etat de cp:\n");
	Move *ptr = l;
	int a = 1;
	while (ptr->oldTile != 0 && ptr->newTile != 0) {
		printf("[%d]----~\n", a);
		//printypeoup(*ptr);
		ptr++;
		a++;
	}
	printf("----------------------------\n");
}

// @TODO to delete
/* predicat: est ce que cette BoardTile est dans le tableau ? */
int moveIsIncluded(BoardTile c, BoardTile *liste, int taille) {
	int resultat = 0;
	int i;
	for (i = 0; i < taille - 1; ++i) {
		if (liste[i].officialRating == c.officialRating) {
			printf("[%d] est dans la liste !\n", c.officialRating);
			resultat = 1;
			break;
		}
	}
	return resultat;
}


// @TODO debug returnne le nombre de coups dans un tableau and to delete
int numberMoves(Move *set) {
	int cpt = 0;
	while ((set->oldTile != 0) && (set->newTile != 0)) {
		cpt++;
		set++;
	}
	return cpt;
}