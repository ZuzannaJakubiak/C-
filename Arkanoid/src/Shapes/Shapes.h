#ifndef SHAPES_SHAPES_H_
#define SHAPES_SHAPES_H_

#include "Vec2D.h"
#include <vector>

/**
* @class Shapes
* @brief Klasa bazowa, zapewnia mozliwosc uzyskania punktu srodkowego oraz wektora punktow tworzacych dany ksztalt oraz metode do przesuniecia ksztaltu o dany offset
*/
class Shapes
{
public:

    /**
    * @brief Metoda do wyznaczenia punktu srodkowego
    * @return Punkt srodkowy
    */
    virtual Vec2D GetCenterPoint() const = 0;

    /**
    * @brief Destruktor
    */
    virtual ~Shapes() {};

    /**
    * @brief Metoda do wyznaczania wektora punktow tworzacych ksztalt
    * @return Wektor punktow
    */
    inline virtual std::vector<Vec2D>GetPoints() const {return mPoints;}

    /**
    * @brief Metoda do przesuniecia ksztaltu o dany offset
    * @param deltaOffset Offset do przesunicia
    */
    void MoveBy(const Vec2D& deltaOffset);

protected:
    /**
    * @brief Wektor punktow tworzacych ksztalt
    */
    std::vector<Vec2D> mPoints;
};

#endif /* SHAPES_SHAPES_H_ */


