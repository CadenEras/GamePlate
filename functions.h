#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

// Define the size of the game board
#define ROWS 6
#define COLUMNS 7

// Define the size of each cell in the game board
#define CELL_SIZE 80
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500
#define PIECE_RADIUS 30
#define CELL_PADDING 30

int SDL_Init(Uint32 flags);
void SDL_Quit(void);
void SDL_DestroyWindow(SDL_Window* window);
void SDL_Delay(Uint32 ms);
const char* SDL_GetWindowTitle(SDL_Window* window);
void SDL_SetWindowTitle(SDL_Window* window, const char* title);
void SDL_GetWindowPosition(SDL_Window* window, int* x, int* y);
void SDL_SetWindowPosition(SDL_Window* window, int x, int y);
void SDL_GetWindowSize(SDL_Window* window, int* w, int* h);
void SDL_SetWindowSize(SDL_Window* window, int w, int h);
SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags);
void SDL_DestroyRenderer(SDL_Renderer* renderer);
int SDL_CreateWindowAndRenderer(int width, int height, Uint32 window_flags, SDL_Window** window, SDL_Renderer** renderer);

int board[ROWS][COLUMNS] = {0};

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    offsetx = 0;
    offsety = radius;
    d = radius - 1;

    while (offsety >= offsetx) {
        for (int i = x - offsety; i <= x + offsety; i++) {
            SDL_Rect rect = { i, y + offsetx, 1, 1 };
            SDL_RenderFillRect(renderer, &rect);
            rect.y = y - offsetx;
            SDL_RenderFillRect(renderer, &rect);
        }
        for (int i = x - offsetx; i <= x + offsetx; i++) {
            SDL_Rect rect = { i, y + offsety, 1, 1 };
            SDL_RenderFillRect(renderer, &rect);
            rect.y = y - offsety;
            SDL_RenderFillRect(renderer, &rect);
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx++;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety--;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety--;
            offsetx++;
        }
    }
}

void draw_board(SDL_Renderer* renderer)
{
    int cell_width = SCREEN_WIDTH / COLUMNS;
    int cell_height = SCREEN_HEIGHT / ROWS;
    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Draw vertical lines
    for (int i = 1; i < COLUMNS; i++) {
        SDL_RenderDrawLine(renderer, i * cell_width, 0, i * cell_width, SCREEN_HEIGHT);
    }

    // Draw horizontal lines
    for (int i = 1; i < ROWS; i++) {
        SDL_RenderDrawLine(renderer, 0, i * cell_height, SCREEN_WIDTH, i * cell_height);
    }

    // Draw the pieces
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == 1) {
                // Set the drawing color to red
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                // Draw the red piece
                SDL_RenderFillCircle(renderer, (j + 0.5) * CELL_SIZE, (i + 0.5) * CELL_SIZE, PIECE_RADIUS);
            } else if (board[i][j] == 2) {
                // Set the drawing color to yellow
                SDL_SetRenderDrawColor(renderer, 255, 191, 0, 255);
                // Draw the yellow piece
                SDL_RenderFillCircle(renderer, (j + 0.5) * CELL_SIZE, (i + 0.5) * CELL_SIZE, PIECE_RADIUS);
            }
        }
    }
}