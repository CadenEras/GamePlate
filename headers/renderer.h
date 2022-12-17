//
// Created by gries on 04/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_RENDERER_H
#define C_PAS_COOL_GAMEPLATE_RENDERER_H

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Entity.h"

typedef struct {
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Renderer *renderer;
} Renderer;

//Defining screen size by constant
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Renderer *makeWindow(const char *title, int width, int height);
SDL_Texture *createTexture(Renderer *ready, const char *file);
void cleanEverything(Renderer *ready);
void clear(Renderer *ready);
void render(Entity *entity, Renderer *ready);
void display();

#endif //C_PAS_COOL_GAMEPLATE_RENDERER_H
