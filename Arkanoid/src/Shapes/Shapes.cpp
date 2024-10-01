#include "Shapes.h"

void Shapes::MoveBy(const Vec2D& deltaOffset)
{
	for(Vec2D& point : mPoints) //iteracja po wektorze mPoints (punktach ksztaltu)
	{
		point = point + deltaOffset; //dodaje deltaOffset do aktualnego wektora
	}
}



