// gcc sources/Tic-Tac-Toe/Game.c sources/Tic-Tac-Toe/Logic.c sources/Tic-Tac-Toe/Rendering.c -o main.out $(sdl2-config --cflags --libs) -lm


#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../../headers/Tic-Tac-Toe/Game.h"
#include "../../headers/Tic-Tac-Toe/Logic.h"
#include "../../headers/Tic-Tac-Toe/Rendering.h"

int main(int argc, char *argv[])
{
    // initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Tic Tac Toe",
                                          1280, 800,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    // Gestions des erreurs
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // contient les informations du contexte d'affichage
    // déclarant un pointeur sur un renderer ( plus pratique)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                //acceler la carte graphique
                                                SDL_RENDERER_ACCELERATED |
                                                // synchronisation du rendu avec la fréquence de rafraichissement de l'écran
                                                SDL_RENDERER_PRESENTVSYNC);
    // gestion des erreurs
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render_game(renderer, &game);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}