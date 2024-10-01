/*
 * ScreenBuffer.cpp
 *
 *  Created on: 1 sty 2023
 *      Author: Zuzanna Jakubiak
 */



#include "ScreenBuffer.h"
#include <SDL2/SDL.h>
#include <cassert>

ScreenBuffer::ScreenBuffer():mSurface(nullptr)
{

}

ScreenBuffer::~ScreenBuffer()
{
	if(mSurface)
	{
		SDL_FreeSurface(mSurface);
	}
}

void ScreenBuffer::Init(uint32_t format, uint32_t width, uint32_t height)
{
	mSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
	Clear();
}


void ScreenBuffer::Clear(const Color& c)
{
	assert(mSurface);
	if(mSurface)
	{
		SDL_FillRect(mSurface, nullptr, c.GetPixelColor());
	}
}

void ScreenBuffer::SetPixel(const Color& color, int x, int y)
{
	assert(mSurface);

	if(mSurface && (y < mSurface->h && y >= 0 && x >= 0 && x < mSurface->w))
	{
		SDL_LockSurface(mSurface);

			uint32_t * pixels = (uint32_t*)mSurface->pixels;

			size_t index = GetIndex(y, x);
//			Color surfaceColor = Color(pixels[index]); //destinationColor
			pixels[index] = Color(color).GetPixelColor();

			SDL_UnlockSurface(mSurface);
	}
}

uint32_t ScreenBuffer::GetIndex(int row, int column)
{
	assert(mSurface);
	if(mSurface)
	{
		return row * mSurface->w + column;
	}
	return 0;
}



