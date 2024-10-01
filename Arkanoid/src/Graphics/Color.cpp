/*
 * Color.cpp
 *
 *  Created on: 1 sty 2023
 *      Author: Zuzanna Jakubiak
 */


#include<SDL2/SDL.h>
#include"Color.h"

const SDL_PixelFormat* Color::mFormat = nullptr;
void Color::InitColorFormat(const SDL_PixelFormat * format)
{
	Color::mFormat = format;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	mColor = SDL_MapRGBA(mFormat, r, g, b, a);
}





