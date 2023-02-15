#include <math.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL2_gfxPrimitives.h>

#include "../../headers/Tic-Tac-Toe/Game.h"
#include "../../headers/Tic-Tac-Toe/Rendering.h"

const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 255, .g = 50, .b = 50 };
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 100, .b = 255 };
const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .b = 100 };

void render_grid(SDL_Renderer *renderer, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (int i = 1; i < N; ++i) {
        SDL_RenderDrawLine(renderer,
                           i * CELL_WIDTH, 0,
                           i * CELL_WIDTH, SCREEN_HEIGHT);
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
//     thickLineRGBA(renderer,
//                   center_x - half_box_side,
//                   center_y - half_box_side,
//                   center_x + half_box_side,
//                   center_y + half_box_side,
//                   10,
//                   color->r,
//                   color->g,
//                   color->b,
//                   255);
//     thickLineRGBA(renderer,
//                   center_x + half_box_side,
//                   center_y - half_box_side,
//                   center_x - half_box_side,
//                   center_y + half_box_side,
//                   10,
//                   color->r,
//                   color->g,
//                   color->b,
//                   255);
//}

void render_o(SDL_Renderer *renderer,
              int row, int column,
              const SDL_Color *color)
{
    const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
    const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;
    int radius;
    const int diameter = (radius * 2);
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, center_x + x, center_y - y);
        SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
        SDL_RenderDrawPoint(renderer, center_x - x, center_y - y);
        SDL_RenderDrawPoint(renderer, center_x - x, center_y + y);
        SDL_RenderDrawPoint(renderer, center_x + y, center_y - x);
        SDL_RenderDrawPoint(renderer, center_x + y, center_y + x);
        SDL_RenderDrawPoint(renderer, center_x - y, center_y - x);
        SDL_RenderDrawPoint(renderer, center_x - y, center_y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

    // filledCircleRGBA(renderer,
    //                  center_x, center_y, half_box_side + 5,
    //                  color->r, color->g, color->b, 255);
    // filledCircleRGBA(renderer,
    //                  center_x, center_y, half_box_side - 5,
    //                  0, 0, 0, 255);
    //}

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

void render_game(SDL_Renderer *renderer, const game_t *game)
{
    switch (game->state) {
    case RUNNING_STATE:
        render_running_state(renderer, game);
        break;

    case PLAYER_X_WON_STATE:
        render_game_over_state(renderer, game, &PLAYER_X_COLOR);
        break;

    case PLAYER_O_WON_STATE:
        render_game_over_state(renderer, game, &PLAYER_O_COLOR);
        break;

    case TIE_STATE:
        render_game_over_state(renderer, game, &TIE_COLOR);
        break;

    default: {}
    }
}