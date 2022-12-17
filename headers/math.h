//
// Created by gries on 09/12/2022.
//

#ifndef C_PAS_COOL_GAMEPLATE_MATH_H
#define C_PAS_COOL_GAMEPLATE_MATH_H

#pragma once

#include <stdio.h>

typedef struct {
	float x, y;
} Vector2f;

Vector2f initVector2f();
Vector2f addVector2f(float x, float y);

#endif //C_PAS_COOL_GAMEPLATE_MATH_H
