#ifndef GAMES_BREAKOUT_BLOCK_H_
#define GAMES_BREAKOUT_BLOCK_H_

#include "Excluder.h"

#include "Color.h"

class Ball;
class Screen;
struct BoundaryEdge;


/**
@class Block
@brief Klasa Block reprezentujaca bloki w grze.
*/
class Block: public Excluder
{
public:

	/**
	@brief UNBREAKABLE stala do wskazania, ze blok jest niezniszczalny.
	*/
	static const int UNBREAKABLE = -1;

	/**
	@brief Konstruktor.
	*/
	Block();

	/**
	@brief Inicjalizacja bloku z danymi parametrami..
	@param rect AARectangle reprezentujacy pozycje i rozmiar bloku.
	@param hp Hp bloku.
	@param outlineColor Kolor konturow bloku.
	@param fillColor Kolor wypelnienia.
	*/
	void Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);

	/**
	@brief Rysuje blok na ekranie.
	@param screen Ekran.
	*/
	void Draw(Screen& screen);

	/**
	@brief Obsluguje kolizje pilki z blokiem.
	@param ball Pilka.
	@param edge Granica bloku z ktora zderzyla sie pilka.
	*/
	void Bounce(Ball& ball, const BoundaryEdge& edge);

	/**
	@brief Redukcja Hp o 1.
	*/
	void ReduceHP();

	/**
	@brief Sprawdza Hp bloku.
	@return Hp bloku.
	*/
	inline int GetHP() const {return mHp;}

	/**
	@brief Sprawdza czy blok jest zniszczony.
	@return Prawda jezeli zniszczony, inaczej falsz..
	*/
	inline bool IsDestroyed() const {return mHp == 0;}

	/**
	@brief Sprawdza kolor konturow.
	@return Kolor konturow.
	*/
    //inline const Color& GetOutlineColor() const {return mOutlineColor;}

	/**
	@brief Sprawdza kolor wypelnienia.
	@return Kolor wypelnienia.
	*/
	//inline const Color& GetFillColor() const {return mFillColor;}

	void AddPoint();

	void Delete();

	private:
	Color mOutlineColor; /**< Kolor konturow. */
	Color mFillColor; /**< Kolor wypelnienia. */

	int mHp; /**< Hp. */
};

#endif /* GAMES_BREAKOUT_BLOCK_H_ */
