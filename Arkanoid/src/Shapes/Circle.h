#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include"Shapes.h"
/**
* @class Circle
* @brief Klasa reprezentujaca okrąg 2D zdefiniowany przez punkt srodkowy oraz promien, dziedziczy po klasie Shapes. Zapewnia metody do uzyskania punktu środkowego oraz promienia.
*
* @var Circle::mRadius
* Promien okregu
*/
class Circle: public Shapes
{
public:

    /**
    * @brief Domyslny konstruktor
    */
    Circle();

    /**
    * @brief Konstruktor z punktem srodkowym i promieniem
    * @param center Punkt srodkowy
    * @param radius Promien
    */
    Circle(const Vec2D& center, float radius);

    /**
    * @brief Metoda wyznaczajaca punkt srodkowy okregu
    * @return Srodek okregu
    */
    inline virtual Vec2D GetCenterPoint() const override {return mPoints[0];}

    /**
    * @brief Metoda wyznaczajaca promien okregu
    * @return Promien okregu
    */
    inline float GetRadius() const {return mRadius;}

private:
    /**
    * @var Circle::mRadius
    * Promien okregu
    */
    float mRadius;
};

#endif /* SHAPES_CIRCLE_H_ */
