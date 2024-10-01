/*
 * Screen.h
 *
 *  Created on: 1 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_

#include<stdint.h>
#include"ScreenBuffer.h"
#include"Color.h"
#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>

class Vec2D;
class Line2D;
class AARectangle;
class Circle;
struct SDL_Window;
struct SDL_Surface;
struct SDL_Font;
struct SDL_Renderer;

/**
@class Screen
@brief Klasa Screen zapewnia interfejs do rysowania ksztaltow i obrazow 2D na ekranie przy uzyciu biblioteki SDL.
*/
class Screen
{
public:

	/**
	@brief Konstruktor
	*/
	Screen();

	/**
	@brief Destruktor
	*/
	~Screen();

	/**
	@brief Inicjuje ekran z zadana szerokoscia, wysokoscia i wspolczynnikiem powiekszenia.
	@param w Szerokosc ekranu.
	@param h Wysokosc ekranu.
	@param mag Wspolczynnik powiekszenia.
	@return Wskaznik do SDL Window
	*/
	SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);

	/**
	* @brief Zamienia bufor poprzedni z kolejnym aby wyswietlic ksztalty na ekranie.
	*/
	void SwapScreens();

	/**
	 * @brief Metoda do wyznaczania szerokosci ekranu.
	 * @return Szerokosc ekranu.
	 */
	inline uint32_t Width() const {return mWidth;}

	/**
	 * @brief Metoda do wyznaczania wysokosci ekranu.
	 * @return Wysokosc ekranu
	 */
	inline uint32_t Height() const {return mHeight;}

	/**
	 * @brief Rysuje pojedynczy piksel na ekranie w okreslonej pozycji z podanym kolorem
	 * @param x Wspolrzedna x pixela.
	 * @param y Wspolrzedna y pixela.
	 * @param color Kolor.
	 */
	void Draw(int x, int y, const Color& color);

	/**
	 * @brief Rysuje na ekranie linie o podanym kolorze..
	 * @param line Linia.
	 * @param color Kolor linii.
	 */
	void Draw(const Line2D& line, const Color& color);

	/**
	 * @brief Rysuje na ekranie wyrownany do osi prostokat o podanym kolorze
	 * @param rect Prostokat.
	 * @param color Kolor.
	 * @param fill Flaga wskazujaca czy prostokat powinien byc wypelniony.
	 * @param fillColor Kolor wypelniena.
	*/
	void Draw(const AARectangle& rect, const Color& color, bool fill = false, const Color& fillColor = Color::White());

	/**
	* @brief Rysuje na ekranie okrag o danym kolorze.
	* @param circle Okrag.
	* @param color Kolor okregu.
	* @param fill Flaga wskazujaca czy prostokat powinien byc wypelniony.
	* @param fillColor Kolor wypelnienia
	*/
	void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());

private:

	/**
	 * @brief Konstruktor kopiujacy dla klasy Screen.
	 */
	Screen(const Screen& screen);
	/**
	 * @brief Operator przypisania dla klasy Screen.
	 */
	Screen operator=(const Screen& screen);

	/**
	 * @brief Czyszczenie ekranu.
	 */
	void ClearScreen();
	/**
	 * @brief Wypełnia wielokat podanym kolorem.
	 * @param points Punkty tworzace wielokat.
	 * @param color Kolor wypelnienia.
	 */
	void FillPoly(const std::vector<Vec2D>& points, const Color& color);



	uint32_t mWidth; /**< Szerokosc ekranu */
	uint32_t mHeight; /**< Wysokosc ekranu */

	Color mClearColor; /**< Kolor do czyszczenia ekranu. */
	ScreenBuffer mBackBuffer; /**< Bufor poprzedni */

	SDL_Window* moptrWindow; /**< Wskaznik do SDL window. */
	SDL_Surface* mnoptrWindowSurface; /**< Wskaznik do powierzchni SDL window. */

};




#endif /* GRAPHICS_SCREEN_H_ */
