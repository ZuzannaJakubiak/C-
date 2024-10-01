
#include"AARectangle.h"
#include <cmath>

AARectangle::AARectangle(): AARectangle(Vec2D::Zero,Vec2D::Zero) //konstruktor
{

}

AARectangle::AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height)
{
	mPoints.push_back(topLeft); //mPoints przechowuje gorny lewy punkt
	mPoints.push_back(Vec2D(topLeft.GetX() + width -1, topLeft.GetY() + height -1)); //oraz dolny prawy
}

AARectangle::AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight)
{
	mPoints.push_back(topLeft); //gorny lewy
	mPoints.push_back(bottomRight); //dolny prawy
}


float AARectangle::GetWidth() const
{
	return GetBottomRightPoint().GetX() - GetTopLeftPoint().GetX()+1; //szerokosc
}

float AARectangle::GetHeight() const
{
	return GetBottomRightPoint().GetY() - GetTopLeftPoint().GetY()+1; //wysokosc
}

void AARectangle::MoveTo(const Vec2D& position)
{
	float width = GetWidth();
	float height = GetHeight();

	SetTopLeftPoint(position); //Ustawia top left na danej pozycji
	//Ustawia bottom right na pozycji o wsp xy nowej + szerokosc i wysokosc -1
	SetBottomRightPoint(Vec2D(position.GetX() + width - 1, position.GetY() + height - 1));

}

Vec2D AARectangle::GetCenterPoint() const
{
	//Obliczenie srodka przez wsp xy top left i dodanie polowy wysokosci i szerokosci
	return Vec2D(GetTopLeftPoint().GetX() + GetWidth()/2.0f, GetTopLeftPoint().GetY() + GetHeight()/2.0f);
}

bool AARectangle::Intersects(const AARectangle& otherRect) const //zwraca true jak przestnie
{
	return !(otherRect.GetBottomRightPoint().GetX() < GetTopLeftPoint().GetX() || //inny prawy dolny x < gorny lewy x
			otherRect.GetTopLeftPoint().GetX() > GetBottomRightPoint().GetX()|| //inny gorny lewy x > dolny prawy x
			otherRect.GetBottomRightPoint().GetY() < GetTopLeftPoint().GetY() || //inny dolny prawy y < gorny lewy y
			otherRect.GetTopLeftPoint().GetY() > GetBottomRightPoint().GetY()); //inny gorny lewy y > dolny prawy y
}

bool AARectangle::ContainsPoint(const Vec2D& point) const
{
	//punkt x >= top left x i <= bottom right x
	bool withinX = point.GetX() >= GetTopLeftPoint().GetX() && point.GetX() <= GetBottomRightPoint().GetX();
	//punkt y >= top left y i <= bottom right y
	bool withinY = point.GetY() >= GetTopLeftPoint().GetY() && point.GetY() <= GetBottomRightPoint().GetY();

	return withinX && withinY;
	//sprawdza czy wsp x i y danego punktu zawieraja sie we wsp gorny lewy/ dolny prawy
}

std::vector<Vec2D> AARectangle::GetPoints() const
{
	std::vector<Vec2D> points;

	points.push_back(mPoints[0]); //top left
	points.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY())); //Top right
	points.push_back(mPoints[1]);//Bottom Right
	points.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY()));//Bottom left

	return points;
}




