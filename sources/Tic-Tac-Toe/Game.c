//gcc main.c sources/base/window.c  sources/Tic-Tac-Toe/Game.c sources/Tic-Tac-Toe/Logic.c sources/Tic-Tac-Toe/Rendering.c -o main.out $(sdl2-config --cflags --libs) -lm -lSDL2_image

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../../headers/Tic-Tac-Toe/Game.h"
#include "../../headers/Tic-Tac-Toe/Logic.h"
#include "../../headers/Tic-Tac-Toe/Rendering.h"
#include "../../headers/base/window.h"

int main_ttt(Window *window)
{
    int state = 0;
    int choice = 0;
    int menu = 1;
    int pos = 0;
    int click = 0;

    // initialisation du jeu avec les cellules vides
    game_t game = {
        .board = { EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY },
        // le joueur X commence
        .player = PLAYER_X,
        // le jeu est en cours
        .state = RUNNING_STATE,
        .isEnded = 0
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
        state = render_game(window->renderer, &game);
        menu = 1;
        if (game.isEnded == 1) {
            if (game.state == PLAYER_X_WON_STATE) {
                displayEndP1TTT(pos, window);
            } else if (game.state == PLAYER_O_WON_STATE) {
                displayEndP2TTT(pos, window);
            } else if (game.state == TIE_STATE) {
                displayEndTieTTT(pos, window);
            }
            while (menu == 1) {
                while (SDL_PollEvent(&e)) {
                    if (game.state == PLAYER_X_WON_STATE) {
                       switch (e.type) {
                            case SDL_KEYDOWN:
                                switch (e.key.keysym.sym) {
                                    case SDLK_ESCAPE:
                                        menu = 0;
                                        break;
                                    default:
                                        break;
                                } // Fin switch touche choisi
                            case SDL_MOUSEMOTION:
                                pos = mousePositionEndTTT(e);
                                displayEndP1TTT(pos, window);
                                break;
                                // Fin du cas : la souris bouge
                            case SDL_MOUSEBUTTONUP:
                                switch (e.button.button) {
                                case SDL_BUTTON_LEFT:
                                    click = mouseClickEndTTT(e);
                                    switch (click) {
                                        case 1:
                                            // on replay
                                            game.isEnded = 0;
                                            menu = 0;
                                            break;
                                        case 2:
                                            // on sort
                                            menu = 0;
                                            game.state = QUIT_STATE;
                                            break;
                                        default:
                                            break;
                                    } 
                                    break;
                                default:
                                    break;
                                } 
                            default:
                                break;
                        } 
                    } else if (game.state == PLAYER_O_WON_STATE) {
                        switch (e.type) {
                            case SDL_KEYDOWN:
                                switch (e.key.keysym.sym) {
                                    case SDLK_ESCAPE:
                                        menu = 0;
                                        break;
                                    default:
                                        break;
                                } // Fin switch touche choisi
                            case SDL_MOUSEMOTION:
                                pos = mousePositionEndTTT(e);
                                displayEndP2TTT(pos, window);
                                break;
                                // Fin du cas : la souris bouge
                            case SDL_MOUSEBUTTONUP:
                                switch (e.button.button) {
                                case SDL_BUTTON_LEFT:
                                    click = mouseClickEndTTT(e);
                                    switch (click) {
                                        case 1:
                                            // on replay
                                            game.isEnded = 0;
                                            menu = 0;
                                            break;
                                        case 2:
                                            // on sort
                                            game.state = QUIT_STATE;
                                            break;
                                        default:
                                            break;
                                    } 
                                    break;
                                default:
                                    break;
                                } 
                            default:
                                break;
                        } 
                    } else if (game.state == TIE_STATE) {
                        switch (e.type) {
                            case SDL_KEYDOWN:
                                switch (e.key.keysym.sym) {
                                    case SDLK_ESCAPE:
                                        menu = 0;
                                        break;
                                    default:
                                        break;
                                } // Fin switch touche choisi
                            case SDL_MOUSEMOTION:
                                pos = mousePositionEndTTT(e);
                                displayEndTieTTT(pos, window);
                                break;
                                // Fin du cas : la souris bouge
                            case SDL_MOUSEBUTTONUP:
                                switch (e.button.button) {
                                case SDL_BUTTON_LEFT:
                                    click = mouseClickEndTTT(e);
                                    switch (click) {
                                        case 1:
                                            // on replay
                                            game.isEnded = 0;
                                            menu = 0;
                                            break;
                                        case 2:
                                            // on sort
                                            game.state = QUIT_STATE;
                                            break;
                                        default:
                                            break;
                                    } 
                                    break;
                                default:
                                    break;
                                } 
                            default:
                                break;
                        } 
                    } 
                    
                }
            }
        }
        
        SDL_RenderPresent(window->renderer);
 
    }
    
    return EXIT_SUCCESS;
}