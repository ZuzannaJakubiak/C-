#ifndef UTILS_VEC2D_H_
#define UTILS_VEC2D_H_

#include <iostream>

static const float EPSILON = 0.0001f; //tolerance

const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

/**
* @class Vec2D
* @brief Klasa 2D vector, z podstawowymi operacjami matematycznym, takimi jak dodawanie, odejmowanie, mnozenie skalarne, metody do okreslenia wielkosci wektora, odleglosci miedzy wektorami, rotacji wektora wokol punktu.
* @var Vec2D::mX
* Wspolrzedna x wektora
* @var Vec2D::mY
* Wspolrzedna y wektora
* @var Vec2D::Zero
* Staly wektor o wsporzednych (0, 0)
*/
class Vec2D {

public:

    /**
    * @brief Staly wektor o wsporzednych (0,0)
    */
    static const Vec2D Zero;

    /**
    * @brief Metoda konstruujaca wektor o wspolrzednych (0,0)
    */
    Vec2D(): Vec2D(0,0){}

    /**
    * @brief Metoda konstruujaca wektor o danych wspolrzednych
    * @param x Wspolrzedna x wektorar
    * @param y Wspolrzedna y wektora
    */
    Vec2D(float x, float y): mX(x), mY(y){}

    /**
    * @brief Metoda ustawiajace wspolrzedna x wektora
    * @param x Nowa wspolrzedna x
    */
    inline void SetX(float x) {mX = x;}

    /**
    * @brief Metoda ustawiajace wspolrzedna y wektora
    * @param y Nowa wspolrzedna y
    */
    inline void SetY(float y) {mY = y;}

    /**
    * @brief Metoda sprawdzajaca wspolrzedna x wektora
    * @param x Wspolrzedna x
    */
    inline float GetX() const {return mX;}

    /**
    * @brief Metoda sprawdzajaca wspolrzedna y wektora
    * @param y Wspolrzedna y
    */
    inline float GetY() const {return mY;}

    /**
    * @brief Metoda sprawdzajaca rownosc dwoch wektorow
    * @param vec2 Wektor do porownania
    * @return Prawda, jezeli wektory sa rowne, w innych przypadkach falsz
    */
    bool operator==(const Vec2D& vec2) const;

    /**
    * @brief Metoda do negacji wektora
    * @return Zanegowany wektor
    */
    Vec2D operator-() const;

    /**
    * @brief Metoda skalujaca wektor przez skalar
    * @param scale Skalar przez ktory mnozy sie wektor
    * @return Przeskalowany wektor
    */
    Vec2D operator*(float scale) const;

    /**
    * @brief Metoda dzielaca wektor przez skalar
    * @param scale Skalar przez ktory dzieli sie wektor
    * @return Wektor podzielony
    */
    Vec2D operator/(float scale) const;

    /**
    * @brief Metoda dodajaca dwa wektory
    * @param vec Wektor do dodania
    * @return Suma wektorow
    */
    Vec2D operator+(const Vec2D& vec) const;

    /**
    * @brief Metoda odejmujaca dwa wektory
    * @param vec Wektor do odjecia
    * @return Roznica miedzy wektorami
    * */

    Vec2D operator-(const Vec2D& vec) const;

    /**
    * @brief Metoda odejmujaca wektor od aktualnego wektora
    * @param vec Wektor do odjecia
    * @return Referencja do aktualnego wektora
    */
    Vec2D& operator-=(const Vec2D& vec);

    /**
    * @brief  Metoda wyznaczjaca kwadrat wielkosci wektora
    * @return Kwadrat wielkosi wektora
    */
    float Mag2() const;

    /**
    * @brief Metoda wyznaczajaca wielkosc wektora
    * @return Wielkosc wektora
    */
    float Mag() const;

    /**
    * @brief Metoda wyznaczajaca wektor jednostkowy o tym samym kierunku co aktualny wektor
    * @return Wektor jednostkowy
    */
    Vec2D GetUnitVec() const;

    /**
    * @brief Metoda wyznaczajaca odleglosc miedzy dwoma wektorami
    * @param vec Wektor do ktorego mierzona jest odleglosc
    * @return Odleglosc miedzy wektorami
    */
    float Distance(const Vec2D& vec) const;

    /**
    * @brief Metoda wyznaczajaca iloczyn skalarny dwoch wektorow
    * @param vec Wektor z ktorym ma byc wyznaczony iloczyn skalarny
    * @return Iloczyn skalarny
    */
    float Dot(const Vec2D& vec) const;

    /**
    * @brief Metoda wyznaczajaca rzut wektora
    * @param vec2 Wektor do wyznaczenia rzutu
    * @return Rzut wektora
    */
    Vec2D ProjectOnto(const Vec2D& vec2) const;

    /**
    * @brief Metoda wyznaczajaca odbicie wektora wzgledem danej normalnej
    * @param normal Normalna
    * @return Odbity wektor
    */
    Vec2D Reflect(const Vec2D& normal) const;

    /**
    * @brief Metoda obracajaca aktualny wektor wokol punktu o podany kat
    * @param angle Kat obrotu (w radianach)
    * @param aroundPoint Punkt wokol ktorego nastepuje obrot
    * @return Obrocony wektor
    */
    void Rotate(float angle, const Vec2D& aroundPoint);

    /**
    * @brief Mnozenie skalara przez wektor
    * @param scalar skalar do mnozenia
    * @param vec Wektor do mnozenia
    * @return Wynik mnozenia skalara i wektora
    */
    friend Vec2D operator*(float scalar, const Vec2D& vec);

	private:
	float mX, mY;
};




#endif /* UTILS_VEC2D_H_ */
