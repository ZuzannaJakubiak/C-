/*
 * Ball.h
 *
 *  Created on: 6 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#ifndef GAMES_BREAKOUT_BALL_H_
#define GAMES_BREAKOUT_BALL_H_

#include "AARectangle.h"
#include <stdint.h>
#include <Excluder.h>

class Screen;
struct BoundaryEdge;

/**
@class Ball
@brief Klasa Ball reprezentujaca pilke w grze.
*/
class Ball
{
public:

	/**
	@brief Konstruktor.
	*/
	Ball();

	/**
	@brief Konstruktor przyjmujacy jako argumenty pozycje i promien.
	@param pos Pozycja.
	@param radius Promien.
	*/
	Ball(const Vec2D& pos, float radius);

	/**
	@brief Aktualizacja pilki.
	@param dt Czas w milisekundach od ostatniej aktualizacji.
	*/
	void Update(uint32_t dt);

	/**
	@brief Rysuje pilke na ekranie.
	@param screen Ekran.
	*/
	void Draw(Screen& screen);

	/**
	@brief Wyrownanie pilki z zadana krawedzia.
	@param edge Krawedz do wyrownania.
	@param pointOnEdge Odniesienie do punktu na krawedzi, z ktorym pilka zostanie wyrownana.
	@param limitToEdge Czy ograniczyc pilke do krawedzi .
	*/
	void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);

	/**
	@brief Zatrzymanie ruchu pilki.
	*/
	inline void Stop() {mVelocity = Vec2D::Zero;}

	/**
	@brief Przesuniecie pilki do konkretnego punktu.
	@param point Punkt
	*/
	void MoveTo(const Vec2D& point);

	/**
	@brief Odbicie pilki od krawedzi.
	@param edge Krawedz.
	*/
	void Bounce(const BoundaryEdge& edge);

	/**
	@brief Uzyskanie prostokoatu ograniczajacego pilke
	@return AARectangle prostokat ograniczajacy pilke
	*/
	inline const AARectangle GetBoundingRect() const {return mBBox;}

	/**
	@brief Ustawienie predkosci pilki
	@param vel Predkosc
	*/

	inline void SetVelocity(const Vec2D& vel) {mVelocity = vel;}

	/**
	@brief Sprawdzenie predkosci pilki
	@return Predkosc pilki
	*/
	inline Vec2D GetVelocity() const {return mVelocity;}

	/**
	@brief Sprawdzenie promienia pilki
	@return Promien pilki
	*/
	inline float GetRadius() const {return mBBox.GetWidth()/2.0f;}

	/**
	@brief Sprawdzenie pozycji pilki
	@return Pozycja pilki
	*/
	inline Vec2D GetPosition() const {return mBBox.GetCenterPoint();}

private:
	AARectangle mBBox; /*< Prostokoat ograniczajacy pilke */
	Vec2D mVelocity; /*< Predkosc pilki */
	static const float RADIUS; /**< Promien pilki */
};



#endif /* GAMES_BREAKOUT_BALL_H_ */
