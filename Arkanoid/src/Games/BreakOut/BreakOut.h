#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_


#include <string>
#include <stdint.h>
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"
#include <vector>

class GameController;
class Screen;

/**

@enum BreakoutGameStates
@brief Enumerator stanow gry.
IN_PLAY: W grze.
IN_SERVE: W gotowosci, przed rozpoczeciem.
IN_GAME_OVER: Koniec gry.
*/
enum BreakoutGameStates
{
IN_PLAY = 0, /**< W grze. */
IN_SERVE, /**< W gotowosci, przed rozpoczeciem. */
IN_GAME_OVER, /**< Koniec gry. */
};

/**
@class BreakOut
@brief Klasa Breakout jest odpowiedzialna za inicjalizacje, odswiezanie i rysowanie gry. Obsluguje tez stan gryi ilosc zyc..
@var NUM_LIVES
Liczba zyc.
@var INITIAL_BALL_SPEED
Predkosc pilki.
@var mPaddle
Kontrolowana belka.
@var mBall
Kontrolowana pilka.
@var mLevelBoundary
Granice levelu.
@var mLevels
Levele w grze.
@var mCurrentLevel
Aktualny level.
@var mGameState
Aktualny stan gry.
@var mLives
Liczba zyc pozostalych.
@var mYCutoff
Odciecie osi Y.
*/
class BreakOut
{
public:
	/**
	* @brief Inicjuje gre z danym GameController.
	* @param controller Dany GameController.
	*/
	virtual void Init(GameController& controller);

	/**
	* @brief Odswieza z gre co dany czas dt.
	* @param dt Czas.
	*/
	virtual void Update(uint32_t dt);

	/**
	* @brief Rysuje gre na ekranie.
	* @param screen Ekran do narysowania gry.
	*/
	virtual void Draw(Screen& screen);

	/**
	* @brief Getter nazwy gry.
	* @return Nazwa gry.
	*/
	virtual const std::string & GetName() const;
private:

	const int NUM_LIVES = 3; /**< Startowa liczba zyc. */

	/**
	* @brief Reset do danego levela.
	* @param toLevel Level do resetu.
	*/
	void ResetGame(size_t toLevel =0);

	/**
	* @brief Getter aktualnego levelu.
	* @return Aktualny level.
	*/
	BreakoutGameLevel& GetCurrentLevel() {return mLevels[mCurrentLevel];}

	/**
	* @brief Ustawienie stanu gry na IN_SERVE.
	*/
	void SetToServeState();

	/**
	* @brief Sprawdza czy pilka przekroczyla pewne odziecie osi Y.
	* @return Prawda jesli przekroczyla, inaczej falsz..
	*/
	bool IsBallPassedCutoffY() const;

	/**
	* @brief Odjecie jednego zycia.
	*/
	void ReduceLifeByOne();

	/**
	* @brief Sprawdza czy koniec gry.
	* @return Prawda jesli koniec gry, inaczej falsz.
	*/
	bool IsGameOver() const {return mLives < 0;}


	const float INITIAL_BALL_SPEED = 100; //.< Predkosc pilki.
	Paddle mPaddle; ///< Kontrolowana belka.
	Ball mBall; ///< Kontrolowana pilka.
	LevelBoundary mLevelBoundary; ///< Granice levelu.
	std::vector<BreakoutGameLevel> mLevels; ///< Levele w grze.
	size_t mCurrentLevel = 0; ///< Aktualny level.
	BreakoutGameStates mGameState; ///< Aktualny stan gry.
	int mLives; ///< Liczba pozostalych zyc.
	float mYCutoff; ///< Odciecie osi y

};





#endif /* GAMES_BREAKOUT_H_ */
