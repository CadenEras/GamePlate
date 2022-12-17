//
// Created by gries on 16/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_CHECKER_H
#define C_PAS_COOL_GAMEPLATE_CHECKER_H

#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

enum CheckerType {
	CHECKER_TYPE_NONE,
	CHECKER_TYPE_WHITE,
	CHECKER_TYPE_BLACK,
	CHECKER_TYPE_WHITE_KING,
	CHECKER_TYPE_BLACK_KING,
};

typedef struct {
	SDL_Renderer *renderer;
	int totalTextures;
	SDL_Texture *textureCache[5];
	SDL_Texture *outlineTexture;
	enum CheckerType type;
	SDL_Rect rect;
	SDL_Texture *texture;
	SDL_Rect outlineRect;
	bool isOutline;
} Checker;

Checker *checker();
void setCheckerType(Checker *checker, enum CheckerType type);
enum CheckerType getCheckerType(Checker *checker);
void focusTexture(Checker *checker, SDL_Rect rect);
void setOutline(Checker *checker, bool isOutline);
void renderChecker(Checker *checker);

#endif //C_PAS_COOL_GAMEPLATE_CHECKER_H
