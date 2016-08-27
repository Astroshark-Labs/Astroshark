#include "SDL.h"
#include "SDL_image.h"

void loadPNGImageToTexture(SDL_Renderer *renderer, int *w, int *h, SDL_Texture **spriteTexture, const char *file) {
	SDL_Surface *tempSurface = IMG_Load(file);
	*spriteTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	SDL_QueryTexture(*spriteTexture, NULL, NULL, w, h);
}

void alphaIncrease(SDL_Texture *texture, int *alpha, int rate) {
	*alpha += rate;
	SDL_SetTextureAlphaMod(texture, *alpha);
}

void alphaDecrease(SDL_Texture *texture, int *alpha, int rate) {
	*alpha -= rate;
	SDL_SetTextureAlphaMod(texture, *alpha);
}