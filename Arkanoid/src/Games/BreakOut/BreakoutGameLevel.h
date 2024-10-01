#ifndef GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_
#define GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_

#include "Block.h"
#include <vector>
#include <stdint.h>

class Screen;
class Ball;
class AARectangle;

/**
* @brief Struktura do przechowywania informacji o komendzie
*/
struct LayoutBlock
{
	char symbol = '-'; //**< Symbol bloku */
	int hp = 0; //**< Hp dla bloku */
	Color color = Color::Black(); //**< Kolor bloku */
};

/**
@class BreakoutGameLevel
@brief Klasa BreakoutGameLevel reprezentuje level w grze.
*/
class BreakoutGameLevel
{
public:

	/**
	@brief Konstruktor.
	*/
	BreakoutGameLevel();

	/**
	@brief Zaladowanie levelu z danymi blokami.
	@param blocks Bloki do zaladowania.
	*/



	void Load(const std::vector<Block>& blocks);

	/**
	@brief Aktualizacja poziomu.
	@param dt Czas w milisekundach od ostatniej aktualizacji.
	@param ball pilka.
	*/
	void Update(uint32_t dt, Ball& ball);

	/**
	@brief Rysowanie levelu.
	@param screen Ekran do rysowania..
	*/
	void Draw(Screen& screen);

	/**
	@brief Sprawdzenie czy level jest ukonczony.
	@return Prawda jezeli jest ukonczony, w innym przypadku falsz.
	*/
	bool IsLevelComplete() const;

	/**
	@brief Ladowanie leveli z pliku.
	@param filePath Sciezka do pliku.
	@return Wekor obiektow BreakoutGameLevel.
	*/
	static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string& filePath);

	void Delete();


private:

	static const int BLOCK_WIDTH = 16; /**< Szerokosc kazdego bloku. */
	static const int BLOCK_HEIGHT = 8; /**< Wysokosc kazdego bloku. */
	//	void CreateDefaultLevel(const AARectangle& boundary);
	std::vector<Block> mBlocks; /**< Bloczki w levelu. */
	int Points();
	int MaxPoints();

};

#endif /* GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_ */
