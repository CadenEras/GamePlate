//
// Created by gries on 16/12/2022.
//

#include "../../headers/Checker/checkerGame.h"
#include "../../headers/Checker/interface.h"

void initGame(SDL_Surface *screen, SDL_Window *window) {
	GridType grid[8][8];
	Position destPosition, fromPosition, click;
	int gameOver = 0, turn = RED, valid;
	
	initBoard(grid);
	
	while (!gameOver) {
		printBoard(screen, grid);
		int moveChoosed = 0;
		
		while (!moveChoosed) {
			click = getMousePosition(window);
			if ((click.x > 7) || (click.x < 0) || (click.y > 7) || (click.y < 0)) {
				exit(0);
			} else if (isPieceSelected(turn, grid, click)) {
				fromPosition = click;
				printBoard(screen, grid);
			} else if (isDestinationValid(turn, grid, fromPosition, click)) {
				destPosition = click;
				moveChoosed = 1;
			} else if (removePiece(turn, grid, fromPosition, click) == WHITE_LEFT) {
				destPosition = click;
				grid[fromPosition.x+1][fromPosition.y-1].color = UNDEFINED;
				grid[fromPosition.x+1][fromPosition.y-1].state = EMPTY;
				moveChoosed = 1;
			} else if (removePiece(turn, grid, fromPosition, click) == WHITE_RIGHT) {
				destPosition = click;
				grid[fromPosition.x+1][fromPosition.y+1].color = UNDEFINED;
				grid[fromPosition.x+1][fromPosition.y+1].state = EMPTY;
				moveChoosed = 1;
			} else if (removePiece(turn, grid, fromPosition, click) == RED_LEFT) {
				destPosition = click;
				grid[fromPosition.x-1][fromPosition.y-1].color = UNDEFINED;
				grid[fromPosition.x-1][fromPosition.y-1].state = EMPTY;
				moveChoosed = 1;
			} else if (removePiece(turn, grid, fromPosition, click) == RED_RIGHT) {
				destPosition = click;
				grid[fromPosition.x-1][fromPosition.y+1].color = UNDEFINED;
				grid[fromPosition.x-1][fromPosition.y+1].state = EMPTY;
				moveChoosed = 1;
			}
		}
		updateGrid(turn, grid, fromPosition, destPosition);
		turn = -turn;
		
		if (whoWin(grid) == RED) {
			printf("RED WIN");
			gameOver = 1;
		} else if (whoWin(grid) == WHITE) {
			printf("WHITE WIN");
			gameOver = 1;
		}
	}
	exit(0);
}

void updateGrid(int turn, GridType grid[][8], Position from, Position dest) {
	grid[dest.x][dest.y].color = turn;
	grid[dest.x][dest.y].state = FULL;
	
	grid[from.x][from.y].color = UNDEFINED;
	grid[from.x][from.y].state = EMPTY;
}

Position getMousePosition(SDL_Window *window) {
	Position mousePosition;
	SDL_Event event;
	int wait = 1;
	
	while (wait) {
		SDL_UpdateWindowSurface(window);
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				wait = 0;
				mousePosition.x = -1; //User is pointing close button
				mousePosition.y = -1;
				return mousePosition;
				
			case SDL_MOUSEBUTTONDOWN:
				mousePosition.x = event.button.y;
				mousePosition.y = event.button.x;
				
				if ((mousePosition.x / 100 < 8) && (mousePosition.y / 100 < 8)) {
					mousePosition.x = mousePosition.x / 100;
					mousePosition.y = mousePosition.y / 100;
					return mousePosition;
				}
				break;
		}
	}
}

int isPieceSelected(int turn, GridType grid[][8], Position mousePosition) {
	if (grid[mousePosition.x][mousePosition.y].state == FULL && (grid[mousePosition.x][mousePosition.y].color == turn)) {
		return 1;
	} else {
		return 0;
	}
}

int isDestinationValid(int turn, GridType grid[][8], Position from, Position dest) {
	if (grid[dest.x][dest.y].state == EMPTY) {
		if (turn == RED) {
			if ((dest.x == from.x - 1) && ((dest.y == from.y - 1) || (dest.y == from.y + 1))) {
				return 1;
			} else {
				return 0;
			}
		} else if (turn == WHITE) {
			if ((dest.x == from.x + 1) && ((dest.y == from.y - 1) || (dest.y == from.y + 1))) {
				return 1;
			} else {
				return 0;
			}
		}
	} else {
		return 0;
	}
}

int removePiece(int turn, GridType grid[][8], Position from, Position dest) {
	if (turn == RED) {
		if ((dest.x == from.x - 2) && (dest.y == from.y - 2)) {
			if ((grid[from.x-1][from.y-1].state == EMPTY) && (grid[from.x-1][from.y-1].color == WHITE)) {
				return RED_LEFT;
			} else {
				return 0;
			}
		} else if ((dest.x == from.x - 2) && (dest.y == from.y + 2)) {
			if ((grid[from.x-1][from.y+1].state == EMPTY) && (grid[from.x-1][from.y+1].color == WHITE)) {
				return RED_RIGHT;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	} else if (turn == WHITE) {
		if ((dest.x == from.x + 2) && (dest.y == from.y - 2)) {
			if ((grid[from.x+1][from.y-1].state == EMPTY) && (grid[from.x+1][from.y-1].color == RED)) {
				return WHITE_LEFT;
			} else {
				return 0;
			}
		} else if ((dest.x == from.x + 2) && (dest.y == from.y + 2)) {
			if ((grid[from.x+1][from.y+1].state == EMPTY) && (grid[from.x+1][from.y+1].color == RED)) {
				return WHITE_RIGHT;
			} else {
				return 0;
			}
		} else {
			return 0;
		}
	}
}

int whoWin(GridType grid[][8]) {
	int red = 0, white = 0;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid[i][j].color == RED) {
				red++;
			} else if (grid[i][j].color == WHITE) {
				white++;
			}
		}
	}
	
	if (red > white) {
		return RED;
	} else if (white > red) {
		return WHITE;
	} else {
		return 0;
	}
}
