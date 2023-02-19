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

void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void draw_board(SDL_Renderer* renderer, int board[ROWS][COLUMNS])
{
    int cell_width = (SCREEN_WIDTH - 2 * CELL_PADDING) / COLUMNS;
    int cell_height = (SCREEN_HEIGHT - 2 * CELL_PADDING) / ROWS;
    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Draw vertical lines
    for (int i = 0; i <= COLUMNS; i++) {
        SDL_RenderDrawLine(renderer, CELL_PADDING + i * cell_width, CELL_PADDING, CELL_PADDING + i * cell_width, SCREEN_HEIGHT - CELL_PADDING);
    }

    // Draw horizontal lines
    for (int i = 0; i <= ROWS; i++) {
        SDL_RenderDrawLine(renderer, CELL_PADDING, CELL_PADDING + i * cell_height, SCREEN_WIDTH - CELL_PADDING, CELL_PADDING + i * cell_height);
    }

    // Draw the pieces
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == 1) {
                // Set the drawing color to red
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                // Draw the red piece
                SDL_RenderFillCircle(renderer, CELL_PADDING + (j + 0.5) * cell_width, CELL_PADDING + (i + 0.5) * cell_height, PIECE_RADIUS);
            } else if (board[i][j] == 2) {
                // Set the drawing color to yellow
                SDL_SetRenderDrawColor(renderer, 255, 191, 0, 255);
                // Draw the yellow piece
                SDL_RenderFillCircle(renderer, CELL_PADDING + (j + 0.5) * cell_width, CELL_PADDING + (i + 0.5) * cell_height, PIECE_RADIUS);
            }
        }
    }
}
