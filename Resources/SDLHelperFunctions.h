/* 
 * File:   SDL_Helper_Functions.h
 * Author: EX350002
 *
 * Created on 5 de junio de 2014, 16:08
 */
#ifndef SDLHELPERFUNCTIONS_H
#define	SDLHELPERFUNCTIONS_H

#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer, int screenWidth, int screenHeight);

void CloseSDL(SDL_Window*& window, SDL_Renderer*& renderer);

#endif	/* SDLHELPERFUNCTIONS_H */

