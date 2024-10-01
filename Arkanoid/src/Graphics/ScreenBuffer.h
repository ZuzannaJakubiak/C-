#ifndef GRAPHICS_SCREENBUFFER_H_
#define GRAPHICS_SCREENBUFFER_H_

#include <stdint.h>
#include "Color.h"

class Color;
struct SDL_Surface;

/**
@class ScreenBuffer
@brief Klasa przechowujaca pixele ekranu przed tym jak sa wyswietlane.
*/
class ScreenBuffer
{
public:

	/**
	@brief Konstruktor
	*/
	ScreenBuffer();

	/**
	@brief Konstruktor kopiujacy.
	*/
	ScreenBuffer(const ScreenBuffer& screenBuffer);

	/**
	@brief Destruktor
	*/
	~ScreenBuffer();

	/**

	@brief Operator przypisania dla klasy ScreenBuffer
	*/
	ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

	/**
	@brief Inicjuje ScreenBuffer z podanym formatem, szerokoscia i wysokoscia.
	@param format Format ScreenBuffera.
	@param width Szerokosc.
	@param height Wysokosc.
	*/
	void Init(uint32_t format, uint32_t width, uint32_t height);

	/**
	@brief Funkcja gettera dla powierzchni SDL ScreenBuffera.
	@return Wskaznik do powierzchni SDL ScreenBuffera.
	*/
	inline SDL_Surface * GetSurface() {return mSurface;}

	/**
	@brief Czysci ScreenBuffer na dany kolor.
	@param c Kolor.
	*/
	void Clear(const Color& c = Color::Black());

	/**
	@brief Ustawia piksel w danej pozycji na dany kolor.
	@param color Kolor pixela.
	@param x Wspolrzedna x pixela.
	@param y Wspolrzedna y pixela.
	*/
	void SetPixel(const Color& color, int x, int y);

private:

	SDL_Surface * mSurface; /**< Wskaznik do powierzchni SDL ScreenBuffera */

	/**
	* @brief Pobiera indeks piksela w danej pozycji.
	* @param row Wiersz pixela.
	* @param column Kolumna pixela
	* @return Index pixela na danej pozycji.
	*/
	uint32_t GetIndex(int row, int column);
};





#endif /* GRAPHICS_SCREENBUFFER_H_ */

