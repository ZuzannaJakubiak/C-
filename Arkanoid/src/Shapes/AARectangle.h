#ifndef SHAPES_AARECTANGLE_H_
#define SHAPES_AARECTANGLE_H_

#include "Shapes.h"

/**
@class AARectangle
@brief Klasa AARectangle reprezentuje wyrownany do osi ksztalt prostokata, dziedziczy po klasie Shapes.
*/
class AARectangle: public Shapes
{
public:

	/**
	@brief Konstruktor domyslny
	*/
	AARectangle();

	/**
	@brief Konstruktor z parametrami: gorny lewy punkt, szerokosc wysokosc jako argumenty.
	@param topLeft Punkt w gornym lewym rogu.
	@param width Szerokosc prostokata.
	@param height Wysokosc prostokata
	*/
	AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);

	/**
	@brief Konstruktor z parametrami: gorny lewy punkt i dolny prawy punkt jako argumenty.
	@param topLeft Punkt w gornym lewym rogu.
	@param bottomRight Punkt w dolnym prawym rogu.
	*/
	AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

	/**
	@brief Metoda do ustawiania gornego lewego naroznika prostokata
	@param topLeft Nowy punkt w gornym lewym rogu.
	*/
	inline void SetTopLeftPoint(const Vec2D topLeft) {mPoints[0] = topLeft;}

	/**
	@brief Metoda do ustawiania dolnego prawego naroznika prostokata
	@param bottomRight Nowy punkt w prawym dolnym rogu.
	*/
	inline void SetBottomRightPoint(const Vec2D bottomRight) {mPoints[1] = bottomRight;}

	/**
	@brief Metoda do wyznaczania gornego lewego naroznika prostokata
	@return topLeft Punkt w gornym lewym rogu.
	*/
	Vec2D GetTopLeftPoint() const {return mPoints[0];}

	/**
	@brief Metoda do wyznaczania dolnego prawego naroznika prostokata
	@return topLeft Punkt w prawym dolnym rogu.
	*/
	Vec2D GetBottomRightPoint() const {return mPoints[1];}

	/**
	@brief Metoda do wyznaczania szerokosci prostokata
	@return Szerokosc
	*/
	float GetWidth() const;

	/**
	@brief Metoda do wyznaczania dlugosci prostokata
	@return Wysokosc prostokata
	*/
	float GetHeight() const;

	/**
	@brief Metoda do przesuniecia prostokata do nowej pozycji
	@param position Nowa pozycja
	*/
	void MoveTo(const Vec2D& position);

	/**
	 * @brief Metoda do wyznaczenia srodka prostokata
	 * @return Punkt srodka prostokata
	 */
	virtual Vec2D GetCenterPoint() const override;

	/**
	 * @brief Metoda sprawdzajaca czy prostokat przecina inny
	 * @param otherRect Inny prostokat
	 * @return Prawda, jezeli prostokat przecina inny, falsz jesli nie
	 */
	bool Intersects(const AARectangle& otherRect) const;

	/**
	 * @brief Metoda sprawdzahaca czy punkt zawiera sie w prostokacie
	 * @param point Punkt do sprawdzenia
	 * @return Prawda, jezeli punkt zawiera sie w prostokacie, w przeciwnym przypadku falsz
	 */
	bool ContainsPoint(const Vec2D& point) const;

	/**
	 * @brief Metoda wyznaczajaca 4 wierzcholki prostokata
	 * @return Wektor ze zbiorem punktow
	 */
	virtual std::vector<Vec2D> GetPoints() const override;
};


#endif /* SHAPES_AARECTANGLE_H_ */
