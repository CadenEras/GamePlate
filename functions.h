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
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PIECE_RADIUS 30


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

// Draw the game board using SDL2
/*void draw_board(SDL_Renderer* renderer) {
  // Set the color for the red pieces
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  // Set the color for the yellow pieces
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      // Calculate the position of the cell in the window
      int x = j * CELL_SIZE;
      int y = i * CELL_SIZE;

      // Draw a rectangle for the cell
      SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
      if (board[i][j] == 1) {
        SDL_RenderFillRect(renderer, &rect);
      } else if (board[i][j] == 2) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      }
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}*/

void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int r) {
  int offsetx, offsety, d;
  offsetx = 0;
  offsety = r;
  d = r - 1;
  while (offsety >= offsetx) {
    SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
    SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
    SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
    SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
    SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
    SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
    SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
    SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
    if (d >= 2 * offsetx) {
      d -= 2 * offsetx + 1;
      offsetx++;
    } else if (d < 2 * (r - offsety)) {
      d += 2 * offsety - 1;
      offsety--;
    } else {
      d += 2 * (offsety - offsetx - 1);
      offsety--;
      offsetx++;
    }
  }
}

void draw_piece(SDL_Renderer* renderer, int row, int col, int player) {
  int centerx = x * CELL_SIZE + CELL_SIZE / 2; // calculate the x position of the center of the piece
  int centery = y * CELL_SIZE + CELL_SIZE / 2; // calculate the y position of the center of the piece
  int radius = PIECE_RADIUS; // use the predefined constant for the piece radius

for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLUMNS; col++) {
        double distance = sqrt((col * CELL_SIZE + CELL_SIZE / 2 - centerx) * (col * CELL_SIZE + CELL_SIZE / 2 - centerx) +
                               (row * CELL_SIZE + CELL_SIZE / 2 - centery) * (row * CELL_SIZE + CELL_SIZE / 2 - centery));
        if (distance <= radius) {
            // draw the piece color based on the current player
            if (player == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red for player 1
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 191, 0, 255); // blue for player 2
            }
            SDL_RenderDrawPoint(renderer, col * CELL_SIZE + CELL_SIZE / 2, row * CELL_SIZE + CELL_SIZE / 2);
        }
    }
}

  /*int x = col * CELL_SIZE + CELL_SIZE / 2;
  int y = row * CELL_SIZE + CELL_SIZE / 2;

  if (player == 1) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  } else {
    SDL_SetRenderDrawColor(renderer, 255, 191, 0, 255);
  }

  SDL_RenderDrawCircle(renderer, x, y, PIECE_RADIUS);*/
}

void draw_board(SDL_Renderer* renderer) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (board[i][j] != 0) {
        draw_piece(renderer, i, j, board[i][j]);
      }
    }
  }

  // Draw the grid lines
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  for (int i = 0; i <= ROWS; i++) {
    SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
  }
  for (int i = 0; i <= COLUMNS; i++) {
    SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
  }
}

