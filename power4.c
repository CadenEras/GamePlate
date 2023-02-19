#include "power4.h"

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO)){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    window = SDL_CreateWindow("Connect_4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 500, SDL_WINDOW_SHOWN);

    if(NULL == window){
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    int player = 1;
    int winner = 0;
    int board[ROWS][COLUMNS] = {0};

    while (1) {
    // Handle events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        // Quit the game if the window is closed
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        // Get the column that the player clicked on
        int column = event.button.x / CELL_SIZE;
        if (board[0][column] != 0) {
          // If the column is full, ignore the click
          continue;
        }

        // Place the player's piece in the lowest available row in the column
        for (int i = ROWS - 1; i >= 0; i--) {
          if (board[i][column] == 0) {
            board[i][column] = player;
            break;
          }
        }

        // Check for a win
        for (int i = 0; i < ROWS; i++) {
          for (int j = 0; j < COLUMNS; j++) {
            if (board[i][j] == player) {
              // Check for a horizontal win
              if (j + 3 < COLUMNS && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player) {
                winner = player;
              }

              // Check for a vertical win
              if (i + 3 < ROWS && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player) {
                winner = player;
              }

              // Check for a diagonal win (down-right)
              if (i + 3 < ROWS && j + 3 < COLUMNS && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player) {
                winner = player;
              }

              // Check for a diagonal win (down-left)
              if (i + 3 < ROWS && j - 3 >= 0 && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player) {
                winner = player;
              }
            }
          }
        }

        // Switch to the other player's turn
        player = (player == 1) ? 2 : 1;
      }
    }

    // Draw the game board
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    draw_board(renderer, board);

    // Check for a win or tie
    if (winner != 0) {
      printf("Player %d wins!\n", winner);
      break;
    } else if (board[0][0] != 0 && board[0][1] != 0 && board[0][2] != 0 && board[0][3] != 0 && board[0][4] != 0 && board[0][5] != 0 && board[0][6] != 0) {
      printf("Tie game!\n");
      break;
    }

    // Update the screen
    SDL_RenderPresent(renderer);

    // Delay for a short time to control the frame rate
    SDL_Delay(10);
  }

    statut = EXIT_SUCCESS;
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}
