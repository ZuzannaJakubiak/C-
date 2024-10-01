
#ifndef GAMES_BREAKOUT_PADDLE_H_
#define GAMES_BREAKOUT_PADDLE_H_

#include "Excluder.h"
#include <stdint.h>

class Screen;
class Ball;

	/**
	@enum PaddleDirection
	@brief Enumeracja reprezentujaca rozne kierunki, w ktorych moze poruszac sie belka.
	*/
	enum PaddleDirection
	{
	NONE = 0, /**< Belka sie nie porusza. */
	LEFT, /**< Belka rusza sie w lewo. */
	RIGHT /**< Belka rusza sie w prawo. */
	};

	/**

	@class Paddle

	@brief Klasa Paddle reprezentuje belke w grze Breakout.
	*/
	class Paddle: public Excluder
	{
public:

	/**
	@brief Szerokosc belki w pixelach.
	*/
	static const uint32_t PADDLE_WIDTH = 50;

	/**
	@brief Wysokosc belki w pixelach.
	*/
	static const uint32_t PADDLE_HEIGHT = 10;

	/**
	@brief Inicjalizacja belki.
	@param rect AARectangle reprezentujacy rozmiar i polozenie belki.
	@param boundary AARectangle reprezentujacy granice w ktorej miesci sie belka.
	*/
	void Init(const AARectangle& rect, const AARectangle& boundary);

	/**
	@brief Aktualizacja belki.
	@param dt Czas w milisekundach od ostatniej aktualizacji.
	@param ball Objekt Ball, ktory odbija sie od belki.
	*/
	void Update(uint32_t dt, Ball& ball);

	/**
	@brief Rysuje belke na ekranie.
	@param screen Ekran na ktorym rysuje belke.
	*/
	void Draw(Screen& screen);

	/**
	@brief Okresla czy pilka odbila sie od belki.
	@param Objekt Ball, ktory odbija sie od belki.
	@return Prawda jesli pilka odbila sie od belki, w innym przypadku falsz.
	*/
	bool Bounce(Ball& ball);

	/**
	@brief Okresla czy belka porusza sie w lewo.
	@return Prawda jezeli belka porusza sie w lewo, w innym przypadku falsz.
	*/
	inline bool IsMovingLeft() const {return mDirection == PaddleDirection::LEFT;}

	/**
	@brief Okresla czy belka porusza sie w prawo.
	@return Prawda jezeli belka porusza sie w prawo, w innym przypadku falsz.
	*/
	inline bool IsMovingRight() const {return mDirection == PaddleDirection::RIGHT;}

	/**
	@brief Ustawia kierunek ruchu belki.
	@param dir Kierunek ruchu.
	*/
	inline void SetMovementDirection(PaddleDirection dir) {mDirection = dir;}

	/**
	@brief Zatrzymanie ruchu belki
	*/
	//inline void StopMovement() {mDirection = PaddleDirection::NONE;}

	private:
	PaddleDirection mDirection; /**< Kierunek w ktorym porusza sie belka. */
	AARectangle mBoundary; /**< Granica w ktorej miesci sie belka */
	const float VELOCITY = 100.0f; /**< Predkosc ruchu belki w pixelach na sekunde. */
	const float CORNER_BOUNCE_AMT = 0.2f; /**< Odleglosc od brzegu belki, gdzie uderzenie pilki powoduje odbicie w tym samym kierunku */
};



#endif /* GAMES_BREAKOUT_PADDLE_H_ */
