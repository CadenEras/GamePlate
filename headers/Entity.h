//
// Created by gries on 11/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_ENTITY_H
#define C_PAS_COOL_GAMEPLATE_ENTITY_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.h"

typedef struct {
	Vector2f position;
	SDL_Rect currentFrame;
	SDL_Texture *texture;
} Entity;

Entity *entity(Vector2f position, SDL_Texture *texture);
Vector2f getPosition(Entity *entity);
SDL_Rect getCurrentFrame(Entity *entity);
SDL_Texture *getTexture(Entity *entity);

#endif //C_PAS_COOL_GAMEPLATE_ENTITY_H
