#ifndef GAMES_EXCLUDER_H_
#define GAMES_EXCLUDER_H_

#include "AARectangle.h"
#include "Vec2D.h"
#include "Line2D.h"
#include <cmath>


enum EdgeType
{
	BOTTOM_EDGE = 0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};

static const Vec2D UP_DIR = {0, -1};
static const Vec2D DOWN_DIR = {0, 1};
static const Vec2D LEFT_DIR = {-1, 0};
static const Vec2D RIGHT_DIR = {1, 0};

/**
* @brief Struktura do przechowywania informacji o krawedzi
*/
struct BoundaryEdge
{
	Vec2D normal; /**<Normalna */
	Line2D edge; //**<Krawedz */
};


/**
 * @class Excluder
 * @brief Klasa Excluder reprezentuje obiekt, ktorego mozna uzyc do psrawdzania kolizji z innymi obiektami
 */
class Excluder
{
public:
    /**
     * @brief Wirtualny destruktor.
     */
    virtual ~Excluder() {}

    /**
     * @brief Inicjuje Excluder z podanym AARectangle.
     * @param rect AARectangle.
     * @param reverseNormals Flaga wskazujaca czy normalne powinny zostac odwrocone.
     */
    void Init(const AARectangle& rect, bool reverseNormals = false);

    /**
     * @brief Sprawdza, czy dany prostokat zderzyl się z Excluderem
     * @param rect Prostokat.
     * @param edge Krawedz Excludera z ktora zderzyl sie prostokat.
     * @return Prawda jezeli prostokat zderzyl sie z Excluderem, w innym przypadku falsz.
     */
    bool HasCollided(const AARectangle& rect, BoundaryEdge& edge) const;

    /**
     * @brief Wyznacza przesuniecie, aby uniknac uderzenia.
     * @param rect Prostokat ktpry zderzyl sie z Exculderem.
     * @return Offset (przesuniecie).
     */
    Vec2D GetCollisionOffset(const AARectangle& rect) const;

    /**
     * @brief Wyznacza prostokat uzywany przez Excluder.
     * @return AARectangle uzywany przez Excluder .
     */
    inline const AARectangle& GetAARectangle() const {return mAARect;}

    /**
     * @brief Przesuwa Excluder o dane przesuniecie.
     * @param delta Przesuniecie (wektor).
     */
    void MoveBy(const Vec2D& delta);

    /**
     * @brief Przesuwa Excluder do danego punktu.
     * @param point Punkt.
     */
    void MoveTo(const Vec2D& point);

    /**
     * @brief Pobiera okreslona krawedz Excludera..
     * @param edge Krawedz.
     * @return Okreslona krawedz.
     */
    const BoundaryEdge& GetEdge(EdgeType edge) const;

private:
    /**
     * @brief Ustawia krawedzie Excluder.
     */
    void SetupEdges();

    AARectangle mAARect; /**< AARectangle uzywany przez Excluder. */
    BoundaryEdge mEdges[NUM_EDGES]; /**< Krawedzie Excludera. */
    bool mReverseNormals; /**< Flaga wskazujaca czy normalne powinny zostac odwrocone */
};


#endif /* GAMES_EXCLUDER_H_ */
