#pragma once
#ifndef textures_h
#define textures_h

#include "SDL.h"
/*USE ONE TEXTURE FOR ALL NEED TO UPDATE THIS*/

void loadTexturefromIMG(SDL_Renderer *renderer, SDL_Texture **texture, char *file);

extern SDL_Texture *splash_screenTexture;

extern SDL_Texture *astroshark_titleTexture;

extern SDL_Texture *buttons_texture;

extern SDL_Texture *background_texture;

extern SDL_Texture *amadeusShip_texture;

extern SDL_Texture *laserSpritesheet_texture;

extern SDL_Texture *asteroidSpritesheet_texture;
#endif