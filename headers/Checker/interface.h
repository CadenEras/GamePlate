//
// Created by gries on 16/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_INTERFACE_H
#define C_PAS_COOL_GAMEPLATE_INTERFACE_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "checkerGame.h"

enum HighlighterType {
	HIGHLIGHTER_TYPE_NONE,
	HIGHLIGHTER_TYPE_MOUSE_OVER,
	HIGHLIGHTER_TYPE_MOVALBE,
	HIGHLIGHTER_TYPE_SELECTED,
	HIGHLIGHTER_TYPE_NEXT_POSSIBLE_POSITION,
};



void printBoard(SDL_Surface *screen, GridType grid[][8]);
void initBoard(GridType grid[][8]);

#endif //C_PAS_COOL_GAMEPLATE_INTERFACE_H
