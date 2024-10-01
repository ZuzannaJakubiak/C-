/*
 * LevelBoundary.h
 *
 *  Created on: 6 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#ifndef GAMES_BREAKOUT_LEVELBOUNDARY_H_
#define GAMES_BREAKOUT_LEVELBOUNDARY_H_

#include "Excluder.h"

class AARectangle;
class Ball;

/**
@class LevelBoundary
@brief Klasa LevelBoundary reprezentuje granice w grze. Zawiera AARectangle, reprezentujacy granice. Posiada rowniez funkcje sprawdzenia czy dany obiekt Ball nie zderzyl sie z granica.
*/
class LevelBoundary
{
public:

	/*
	@brief Konstrktor
	*/
	LevelBoundary() {}

	/**
	@brief Konstruktor, jako argument przymuje AARectangle.
	@param boundary AARectangle that reprezentujacy granice.
	*/
	LevelBoundary(const AARectangle& boundary);

	/**
	@brief Sprawdza czy obiet Ball zderzyl sie z granica.
	@param ball Obiekt Ball (pilka).
	@param edge Krawedz z ktora zderzyla sie pilka.
	@return Prawda jezeli pilka zderzyla sie z krawedzia, falsz w innym przypadku.
	*/
	bool HasCollided(const Ball &ball, BoundaryEdge& edge);

	/**
	@brief Wyznaczenie AARectangle reprezentujacego granice levelu.
	@return AARectangle reprezentujacy granice levelu.
	*/
	inline const AARectangle& GetAARectangle() const {return mIncluder.GetAARectangle();}

private:
	Excluder mIncluder; /**< Obiekt Excluder reprezentujacy granice poziomu. */
};

#endif /* GAMES_BREAKOUT_LEVELBOUNDARY_H_ */
