#pragma once
#ifndef sprites_h
#define sprites_h

#include "SDL.h"

typedef struct sprite {
	int deltaX;
	int deltaY;
	int speed;
	int rotate;
	int defaultOrientation;
	int totalFrames;
	int alpha;
	SDL_Rect dstrect;
	SDL_Rect frame[10];
} sprite;
#endif