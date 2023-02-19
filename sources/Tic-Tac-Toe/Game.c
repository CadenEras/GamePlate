// gcc sources/Tic-Tac-Toe/Game.c sources/Tic-Tac-Toe/Logic.c sources/Tic-Tac-Toe/Rendering.c -o main.out $(sdl2-config --cflags --libs) -lm


#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../../headers/Tic-Tac-Toe/Game.h"
#include "../../headers/Tic-Tac-Toe/Logic.h"
#include "../../headers/Tic-Tac-Toe/Rendering.h"
#include "../../headers/base/window.h"

int main_ttt(Window *window)
{

    // initialisation du jeu avec les cellules vides
    game_t game = {
        .board = { EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY },
        // le joueur X commence
        .player = PLAYER_X,
        // le jeu est en cours
        .state = RUNNING_STATE
    };

    // boucle d'événements qui s'arrête quand on clique sur le bouton
    // variable qui contient les événements en cours de traitement
    // et un indicateur qui indiquera qu'il est temps de rompre la boucle
    SDL_Event e;
    while (game.state != QUIT_STATE) {
        // extraction des événements de la file d'événements et activation de leurs types
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                game.state = QUIT_STATE;
                break;

            // à chaque itération on vérifie si le joueur a cliqué sur une cellule
            // si oui on appelle la fonction click_on_cell et on lui donne les coordonnées de la cellule cliquée
            case SDL_MOUSEBUTTONDOWN:
                click_on_cell(&game,
                              e.button.y / CELL_HEIGHT,
                              e.button.x / CELL_WIDTH);
                break;

            default: {}
            }
        }

        SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
        SDL_RenderClear(window->renderer);
        render_game(window->renderer, &game);
        SDL_RenderPresent(window->renderer);
    }

    return EXIT_SUCCESS;
}