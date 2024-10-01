#ifndef SHAPES_LINE2D_H_
#define SHAPES_LINE2D_H_

#include "Vec2D.h"

/**
* @class Line2D
* @brief Klasa reprezntujaca linie 2D zdefiniowana przez dwa punkty, zapewnia metody do ustawiania oraz uzyskiwania tych punktow, sprawdzania rownosci linii, wyznaczania najkrotszego dystansu od punktu oraz wyznaczania najblizszego punktu na linii do danego punktuan.
	* @var Line2D::mP0
	* Pierwszy punkt linii
	*
	* @var Line2D::mP1
	* Drugi punkt linii
*/
class Line2D
{
public:

    /**
    * @brief Konstruktor domyslny.
	*/
    Line2D();

    /**
    * @brief Konstruktor z podanymi wspolrzednymi dla obu punktow
    * @param x0 Wspolrzedna x pierwszego punktu
    * @param y0 Wspolrzedna y pierwszego punktu
    * @param x1 Wspolrzedna x drugiego punktu
    * @param y1 Wspolrzedna y drugiego punktu
    */
    Line2D(float x0, float y0, float x1, float y1);

    /**
    * @brief Konstrukotor z podanymi punktami Vec2D
    * @param p0 Pierwszy punkt
    * @param p1 Drugi punkt
    */
    Line2D(const Vec2D& p0, const Vec2D& p1);

    /**
	* @brief Metoda sprawdzajaca pierwszy punky linii
	* @return Pierwszy punkt
	*/
	inline const Vec2D& GetP0() const {return mP0;}

	/**
	* @brief Metoda sprawdzajaca drugi punky linii
	* @return Drugi punkt
	*/
	inline const Vec2D& GetP1() const {return mP1;}

	/**
    * @brief Metoda ustawiajaca pierwszy punky linii
    * @param p0 Nowy punkt poczatkowy
    */
    inline void SetP0(const Vec2D& p0) {mP0 = p0;}

    /**
    * @brief Metoda ustawiajaca drugi punky linii
    * @param p1 Nowy punkt koncowy
    */
    inline void SetP1(const Vec2D& p1) {mP1 = p1;}

    /**
    * @brief Metoda sprawdzajaca rownosc linii z inna
    * @param line Linia do porownania
    * @return Prawda jezeli rowne, w innym przypadku falsz
    */
    bool operator==(const Line2D& line) const;

    /**
    * @brief Metoda wyznaczajaca minimalna odleglosc od punktu do linii
    * @param p Punkt
    * @param limitToSegment Okresla, czy ograniczyc odleglosc do segmentu, czy nie
    * @return Minimalna odleglosc od punktu do linii
    */
    float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const;

    /**
    * @brief Metoda wyznaczjaca najblizszy punkt na linii do danego punktu
    * @param p punkt
    * @param limitToSegment Okresla, czy ograniczyc odleglosc do segmentu, czy nie
    * @return Punkt na linii najblizszy do danego punktu
    */
    Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment = false) const;

    /**
    * @brief Metoda wyznaczajaca dlugosc linii
    * @return Dlugosc linii
    */
    float Length() const;

private:
    /**
    * @var Line2D::mP0
    * Pierwszy punkt linii
    */
    Vec2D mP0;

    /**
    * @var Line2D::mP1
    * Drugi punkt linii
    */
    Vec2D mP1;
};

#endif /* SHAPES_LINE2D_H_ */

