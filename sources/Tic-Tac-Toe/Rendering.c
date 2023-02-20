#include <math.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../headers/Tic-Tac-Toe/Game.h"
#include "../../headers/Tic-Tac-Toe/Rendering.h"


// Couleurs utilisees pour le rendu du jeu
const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 255, .g = 50, .b = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .b = 255 };
const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .b = 100 };



void render_grid(SDL_Renderer *renderer, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (int i = 1; i < N; ++i) {
        // colonnes
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, SCREEN_HEIGHT);
        // lignes
        SDL_RenderDrawLine(renderer,
                           0,            i * CELL_HEIGHT,
                           SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}

void render_x(SDL_Renderer *renderer,
              int row, int column,
              const SDL_Color *color)
{
    
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    SDL_RenderDrawLine(renderer,
                center_x - half_box_side,
                center_y - half_box_side,
                center_x + half_box_side,
                center_y + half_box_side);

    SDL_RenderDrawLine(renderer,
                center_x + half_box_side,
                center_y - half_box_side,
                center_x - half_box_side,
                center_y + half_box_side);
}


void render_o(SDL_Renderer *renderer,
              int row, int column,
              const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;
    const int size = 100;

    int halfSize = size / 2;
    int x1 = center_x - halfSize; // Coin inférieur gauche
    int y1 = center_y + halfSize;
    int x2 = center_x; // Sommet supérieur
    int y2 = center_y - halfSize;
    int x3 = center_x + halfSize; // Coin inférieur droit
    int y3 = center_y + halfSize;

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(renderer, x3, y3, x1, y1);
 
    // ************ CIRCLE ************
    // const int radius = 85; // rayon du cercle
    // const float pi = 3.14;

    // for (double angle = 0; angle < pi * 2; angle += 0.01) {
    //     int x = center_x + radius * cos(angle);
    //     int y = center_y + radius * sin(angle);
    //     SDL_RenderDrawPoint(renderer, x, y);
    // }

}
    
    // *********** TRIANGLE ************
    // int size = 150;

    // int halfSize = size / 2;
    // int x1 = center_x - halfSize;
    // int y1 = center_y + halfSize;
    // int x2 = center_x;
    // int y2 = center_y - halfSize;
    // int x3 = center_x + halfSize;
    // int y3 = center_y + halfSize;

    // SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    // SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    // SDL_RenderDrawLine(renderer, x3, y3, x1, y1);


    // *********** CROSS ************
    //     SDL_RenderDrawLine(renderer,
    //             center_x - half_box_side,
    //             center_y - half_box_side,
    //             center_x + half_box_side,
    //             center_y + half_box_side);

    // SDL_RenderDrawLine(renderer,
    //             center_x + half_box_side,
    //             center_y - half_box_side,
    //             center_x - half_box_side,
    //             center_y + half_box_side);



void render_board(SDL_Renderer *renderer,
                  const int *board,
                  const SDL_Color *player_x_color,
                  const SDL_Color *player_o_color)
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            switch (board[i * N + j]) {
            case PLAYER_X:
                render_x(renderer, i, j, player_x_color);
                break;

            case PLAYER_O:
                render_o(renderer, i, j, player_o_color);
                break;

            default: {}
            }
        }
    }
}

void render_running_state(SDL_Renderer *renderer, const game_t *game)
{
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer,
                 game->board,
                 &PLAYER_X_COLOR,
                 &PLAYER_O_COLOR);
}

void render_game_over_state(SDL_Renderer *renderer,
                            const game_t *game,
                            const SDL_Color *color)
{
    render_grid(renderer, color);
    render_board(renderer,
                 game->board,
                 color,
                 color);
}

int render_game(SDL_Renderer *renderer, game_t *game)
{
    int state=0;
    switch (game->state) {
    case RUNNING_STATE:
        render_running_state(renderer, game);
        break;

    case PLAYER_X_WON_STATE:
        game->isEnded = 1;
        render_game_over_state(renderer, game, &PLAYER_X_COLOR);
        state = 1;
        break;

    case PLAYER_O_WON_STATE:
        game->isEnded = 1;
        render_game_over_state(renderer, game, &PLAYER_O_COLOR);
        state = 2;
        break;

    case TIE_STATE:
        game->isEnded = 1;
        render_game_over_state(renderer, game, &TIE_COLOR);
        state = 3;
        break;

    default:
        game->isEnded = 0;
        break;
    }
    return state;
}
