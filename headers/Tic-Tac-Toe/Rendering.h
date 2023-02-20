#ifndef RENDERING_H_
#define RENDERING_H_

// rendu du jeu sans modifier son etat
int render_game(SDL_Renderer *renderer, game_t *game);

//  rendu de la grille de jeu avec une couleur
void render_grid(SDL_Renderer *renderer, const SDL_Color *color);

//
void render_x(SDL_Renderer *renderer, int row, int column, const SDL_Color *color);
void render_o(SDL_Renderer *renderer, int row, int column, const SDL_Color *color);

//
void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color);

// permet d'utiliser les couleurs de la SDL
void render_running_state(SDL_Renderer *renderer, const game_t *game);

// 
void render_game_over_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color);


#endif  // RENDERING_H_