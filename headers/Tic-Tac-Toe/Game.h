#ifndef GAME_H_
#define GAME_H_

#include "./../base/window.h"
int main_ttt(Window *window);

// macro pour creer la grille de jeu
#define N 3
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500
#define CELL_WIDTH (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)


// champs de la grille de jeu
#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2


// état du jeu
#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4


// structure qui contient les informations du jeu
typedef struct {
    int board[N * N];
    int player;
    int state;
} game_t;

#endif  // GAME_H_ 