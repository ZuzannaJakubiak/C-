#include"Circle.h"

Circle::Circle(): Circle(Vec2D::Zero, 0) //konstruktor 0
{

}

Circle::Circle(const Vec2D& center, float radius):mRadius(radius)
{
	mPoints.push_back(center); //dodanie do wektora mPoints srodka
}


