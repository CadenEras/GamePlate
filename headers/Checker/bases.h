//
// Created by gries on 16/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_BASES_H
#define C_PAS_COOL_GAMEPLATE_BASES_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SQUARE_NUMBER 8
#define RED 1
#define BLACK 2
#define WHITE (-1)
#define EMPTY 3
#define FULL (-3)
#define UNDEFINED 4
#define RIGHT 5
#define LEFT 6
#define WHITE_LEFT 9
#define WHITE_RIGHT 10
#define RED_LEFT 11
#define RED_RIGHT 12

typedef struct GridType GridType;
struct GridType {
	int state, color;
};

typedef struct Position Position;
struct Position {
	int x, y;
};

#endif //C_PAS_COOL_GAMEPLATE_BASES_H
