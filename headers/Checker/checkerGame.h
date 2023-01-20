//
// Created by gries on 16/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_CHECKERGAME_H
#define C_PAS_COOL_GAMEPLATE_CHECKERGAME_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interface.h"
#include "bases.h"

void initGame(SDL_Surface *screen, SDL_Window *window);
Position getMousePosition(SDL_Window *window);
int isPieceSelected(int turn, GridType grid[][8], Position mousePosition);
int isDestinationValid(int turn, GridType grid[][8], Position from, Position dest);
void updateGrid(int turn, GridType grid[][8], Position from, Position dest);
int removePiece(int turn, GridType grid[][8], Position from, Position dest);
int whoWin(GridType grid[][8]);

#endif //C_PAS_COOL_GAMEPLATE_CHECKERGAME_H
