#ifndef LOGIC_H_
#define LOGIC_H_

// modifier l'état du jeu en fonction de la position de la souris
// il gère un seul tour de jeu
void click_on_cell(game_t *game, int row, int column);

/**
 * @brief Calcule la position de la mouse a chaque mouvement
 * @return int Un entier representant une position dans le menu pause.
 */
int mousePositionEndTTT(SDL_Event e);

/**
 * @brief Calcule la position de la mouse a chaque click dans le menu principal.
 * @return int Un entier representant un choice dans le menu principal.
 */
int mouseClickEndTTT(SDL_Event e);

/**
 * @brief Display Main Checker menu.
 * @param choice Choice from the Main Checker menu.
 */
void displayEndTTT(int state, int choice, Window *window);

#endif  // LOGIC_H_