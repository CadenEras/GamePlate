//
// Created by gries on 16/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_HIGHLIGHTER_H
#define C_PAS_COOL_GAMEPLATE_HIGHLIGHTER_H

#pragma once

#include <SDL2/SDL.h>

enum HighlighterType {
	HIGHLIGHTER_TYPE_NONE,
	HIGHLIGHTER_TYPE_MOUSE_OVER,
	HIGHLIGHTER_TYPE_MOVALBE,
	HIGHLIGHTER_TYPE_SELECTED,
	HIGHLIGHTER_TYPE_NEXT_POSSIBLE_POSITION,
};

typedef struct {
	SDL_Renderer *renderer;
	int totalColors;
	SDL_Color colorCache[5];
	enum HighlighterType type;
	SDL_Color *color;
	SDL_Rect rect;
} Highlighter;

Highlighter *highlighter();
void setRect(Highlighter *highlighter, SDL_Rect rect);
void setType(Highlighter *highlighter, enum HighlighterType type);
enum HighlighterType getType(Highlighter *highlighter);
void renderHighlight(Highlighter *highlighter);

#endif //C_PAS_COOL_GAMEPLATE_HIGHLIGHTER_H
