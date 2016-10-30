#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "sprite.h"
#include <math.h>

#define PI 3.14159265

enum output {TOP, RIGHT, CORNER};

enum direction { NORTH = 1, EAST, SOUTH, WEST };

void loadPNGImageToTexture(SDL_Renderer *renderer, int *w, int *h, SDL_Texture **spriteTexture, const char *file) {
	SDL_Surface *tempSurface = IMG_Load(file);
	*spriteTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(*spriteTexture, NULL, NULL, w, h);
}

void setAlpha(SDL_Texture *texture, Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

void alphaIncrease(SDL_Texture *texture, int *alpha, int rate) {
	*alpha += rate;
	SDL_SetTextureAlphaMod(texture, *alpha);
}

void alphaDecrease(SDL_Texture *texture, int *alpha, int rate) {
	*alpha -= rate;
	SDL_SetTextureAlphaMod(texture, *alpha);
}

void setRect(int x, int y, int w, int h, SDL_Rect *rect) {
	rect->x = x;	
	rect->y = y;	
	rect->w = w;	
	rect->h = h;
}

void setRectXY(int x, int y, SDL_Rect *rect) {
	rect->x = x;
	rect->y = y;
}

void copyRect(SDL_Rect *oldRect, SDL_Rect *newRect) {
	newRect->x = oldRect->x;
	newRect->y = oldRect->y;
	newRect->w = oldRect->w;
	newRect->h = oldRect->h;
}

bool testCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (leftA >= rightB)
		return false;
	if (leftB >= rightA)
		return false;
	if (topA >= bottomB)
		return false;
	if (topB >= bottomA)
		return false;

	return true;
}

void domainRestrict(int deltaX, int deltaY, int angle, SDL_Rect *rect, SDL_Rect domain) {
	/*int deltaX;
	int deltaY;

	int baseTan;
	baseTan = atan(720 / (domain.w - rect->x)) * 180 / PI;

	int quadrant = 0;
	float sinT;
	float cosT;

	int result;

	angle -= 180;

	/*Checks to see if rotation is greater or less than 360*/
	/*if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;

	/*Sets proper Quadrant*/
	/*if (angle < 90 && angle > 0) {
		quadrant = 1;
	}
	if (angle < 180 && angle > 90) {
		quadrant = 2;
		angle -= 90;
	}
	if (angle < 270 && angle > 180) {
		quadrant = 3;
		angle -= 180;
	}
	if (angle <= 359 && angle > 270) {
		quadrant = 4;
		angle -= 270;
	}
	if (angle == 0)
		quadrant = astroshark::EAST;
	if (angle == 90)
		quadrant = astroshark::NORTH;
	if (angle == 180)
		quadrant = astroshark::WEST;
	if (angle == 270)
		quadrant = astroshark::SOUTH;

	if (angle < 90 && angle > 0 || angle < 270 && angle > 180) {
		if (baseTan < angle)
			result = TOP;
		if (baseTan > angle)
			result = RIGHT;
		if (baseTan == angle)
			result = CORNER;
	}*/

	angle += 180;
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;

	int w;
	int h;

	w = domain.w - (domain.w - rect->x);
	h = domain.h - (domain.h - rect->y);

	//printf("%d, %d\n", w, h);
	//printf("%d\n", angle);

	int xInc;
	int yInc;
	bool stop = false;

	xInc = -1 * deltaX;
	yInc = deltaY;

	/*while (stop == false) {
		if (rect->x + deltaX >= w) {
			stop == true;
			break;
		}
		if (deltaY + rect->y >= h) {
			stop == true;
			break;
		}

		deltaX += xInc;
		deltaY += yInc;
	}

	deltaX -= xInc;
	deltaY -= yInc;*/

	rect->x += deltaX * 20;
	rect->y += deltaY * 20;
}

void rotationalMovement(int *deltaX, int *deltaY, int angle, int speed) {
	int quadrant = 0;
	float sinT;
	float cosT;

	/*Checks to see if rotation is greater or less than 360*/
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	
	if (angle == 0)
		quadrant = EAST;
	if (angle == 90)
		quadrant = NORTH;
	if (angle == 180)
		quadrant = WEST;
	if (angle == 270)
		quadrant = SOUTH;

	sinT = -1 * (sin(angle * PI / 180) * speed);
	cosT = cos(angle * PI / 180) * speed;

	*deltaX = cosT;
	*deltaY = sinT;

	switch (quadrant) {
	case NORTH:
		*deltaX = cosT;
		*deltaY = sinT + 1;
		break;
	case EAST:
		*deltaX = cosT - 1;
		*deltaY = sinT;
		break;
	case SOUTH:
		*deltaX = cosT;
		*deltaY = sinT - 1;
		break;
	case WEST:
		*deltaX = cosT + 1;
		*deltaY = sinT;
		break;
	}
}