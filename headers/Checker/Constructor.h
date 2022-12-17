//
// Created by gries on 16/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_CONSTRUCTOR_H
#define C_PAS_COOL_GAMEPLATE_CONSTRUCTOR_H

#pragma once

#include <SDL2/SDL.h>

#include "Checker.h"
#include "Highlighter.h"

typedef struct {
	int rox, col;
	SDL_Rect rect;
	SDL_Color backgroundColor;
	Checker *checker;
	Highlighter *highlighter;
	SDL_Renderer *renderer;
} Constructor;

Constructor *constructor();
void setLocation(Constructor *constructor, int row, int col);
void getLocation(Constructor *constructor, int *row, int *col);
void setRectTo(Constructor *constructor, SDL_Rect rect);
void setBackGroundColor(Constructor *constructor, SDL_Color color);
void setChecker(Constructor *constructor, Checker *checker);
enum HighlighterType getHighlighterType();
void setOutlineTo(Constructor *constructor, bool isOutline);
void renderConstructor(Constructor *constructor);
bool isMouseInside(Constructor *constructor);

// Flag and get constructor for possible removal
void setFlag(Constructor *constructor);
Constructor *getFlagged();

// Keep a track of which square made the jump to flag the checker
void setPreviousSquare(Constructor *constructor);
Constructor *getPreviousSquare();

#endif //C_PAS_COOL_GAMEPLATE_CONSTRUCTOR_H
