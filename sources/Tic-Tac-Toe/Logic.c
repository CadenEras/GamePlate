#include "../../headers/Tic-Tac-Toe/Game.h"
#include "../../headers/Tic-Tac-Toe/Logic.h"
#include "../../headers/base/window.h"

void switch_player(game_t *game)
{
    if (game->player == PLAYER_X) {
        game->player = PLAYER_O;
    } else if (game->player == PLAYER_O) {
        game->player = PLAYER_X;
    }
}

int check_player_won(game_t *game, int player)
{
    int row_count = 0;
    int column_count = 0;
    int diag1_count = 0;
    int diag2_count = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (game->board[i * N + j] == player) {
                row_count++;
            }

            if (game->board[j * N + i] == player) {
                column_count++;
            }
        }

        if (row_count >= N || column_count >= N) {
            return 1;
        }

        row_count = 0;
        column_count = 0;

        if (game->board[i * N + i] == player) {
            diag1_count++;
        }

        if (game->board[i * N + N - i - 1] == player) {
            diag2_count++;
        }
    }

    return diag1_count >= N || diag2_count >= N;
}

int count_cells(const int *board, int cell)
{
    int count = 0;

    for (int i = 0; i < N * N; ++i) {
        if (board[i] == cell) {
            count++;
        }
    }

    return count;
}

void game_over_condition(game_t *game)
{
    if (check_player_won(game, PLAYER_X)) {
        game->state = PLAYER_X_WON_STATE;
    } else if (check_player_won(game, PLAYER_O)) {
        game->state = PLAYER_O_WON_STATE;
    } else if (count_cells(game->board, EMPTY) == 0) {
        game->state = TIE_STATE;
    }
}

void player_turn(game_t *game, int row, int column)
{
    if (game->board[row * N + column] == EMPTY) {
        game->board[row * N + column] = game->player;
        switch_player(game);
        game_over_condition(game);
    }
}

void reset_game(game_t *game)
{
    game->player = PLAYER_X;
    game->state = RUNNING_STATE;
    for (int i = 0; i < N * N; ++i) {
        game->board[i] = EMPTY;
    }
}

void click_on_cell(game_t *game, int row, int column)
{
    if (game->state == RUNNING_STATE) {
        player_turn(game, row, column);
    } else {
        reset_game(game);
    }
}





int mousePositionEndTTT(SDL_Event e){
	e.motion.x;
	e.motion.y;

	// Rejouer
	if(e.button.x > 348 && e.button.x < 450 && e.button.y > 290 && e.button.y < 316 ){
		return 1;
	} else {
		//Quitter
		if(e.button.x > 350 && e.button.x < 450 && e.button.y > 330 && e.button.y < 354 ){
			return 2;
		} else {
				return 0;
			}
		}
}

int mouseClickEndTTT(SDL_Event e) {
		e.button.x;
		e.button.y;

		// Rejouer
		if (e.button.x > 348 && e.button.x < 450 && e.button.y > 290 && e.button.y < 316){
			return 1;
		}
		else{
			// Quitter
			if (e.button.x > 350 && e.button.x < 450 && e.button.y > 330 && e.button.y < 354){
				return 2;
			} else{
				return 0;}
		}
}


void displayEndP1TTT(int pos, Window *window) {
	SDL_Surface *startScreen;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_Surface *windowMenu = SDL_GetWindowSurface(window->window);
	switch (pos){ 
				case 1: // Rejouer
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_p1_win_replay_select.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					SDL_UpdateWindowSurface(window->window);
				break;

				case 2: // Quitter
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_p1_win_quit_select.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					SDL_UpdateWindowSurface(window->window);
					break;

				default: // Neutre
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_p1_win_neutral.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					if (SDL_UpdateWindowSurface(window->window) != 0)
					{
						printf("Surface could not be updated -> SDL_Error: %s", SDL_GetError());
						exit(-1);
					}
					break;
			}
}

void displayEndP2TTT(int pos, Window *window) {
	SDL_Surface *startScreen;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_Surface *windowMenu = SDL_GetWindowSurface(window->window);
	switch (pos){ 
				case 1: // Rejouer
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_p2_win_replay_select.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					SDL_UpdateWindowSurface(window->window);
				break;

				case 2: // Quitter
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_p2_win_quit_select.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					SDL_UpdateWindowSurface(window->window);
					break;

				default: // Neutre
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_p2_win_neutral.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					if (SDL_UpdateWindowSurface(window->window) != 0)
					{
						printf("Surface could not be updated -> SDL_Error: %s", SDL_GetError());
						exit(-1);
					}
					break;
			}
	
}

void displayEndTieTTT(int pos, Window *window) {
	SDL_Surface *startScreen;
	SDL_Rect position;
	position.x = 0;
	position.y = 0;

	SDL_Surface *windowMenu = SDL_GetWindowSurface(window->window);
	switch (pos){ 
				case 1: // Rejouer
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_tie_win_replay_select.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					SDL_UpdateWindowSurface(window->window);
				break;

				case 2: // Quitter
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_tie_win_quit_select.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					SDL_UpdateWindowSurface(window->window);
					break;

				default: // Neutre
					startScreen = SDL_LoadBMP("./assets/morpion/morpion_tie_win_neutral.bmp");
					if (startScreen == 0 || startScreen == NULL)
					{
						printf("ça a pas marché : %s", SDL_GetError());
						exit(-1);
					}
					SDL_BlitSurface(startScreen, NULL, windowMenu, &position);
					if (SDL_UpdateWindowSurface(window->window) != 0)
					{
						printf("Surface could not be updated -> SDL_Error: %s", SDL_GetError());
						exit(-1);
					}
					break;
			}
}