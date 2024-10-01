#include "Line2D.h"
#include <cmath>

Line2D::Line2D():Line2D(Vec2D::Zero, Vec2D::Zero) //konstruktor linii z 2 wektorow zerowa
{

}

Line2D::Line2D(float x0, float y0, float x1, float y1): Line2D(Vec2D(x0, y0), Vec2D(x1, y1))
{//Konstrukotor z podanymi punktami Vec2D

}

Line2D::Line2D(const Vec2D& p0, const Vec2D& p1):mP0(p0), mP1(p1)
{//konstruktor z 2 wektorow mP0 i mP1

}

bool Line2D::operator==(const Line2D& line) const //operator porownania
{
	return line.GetP0() == mP0 && line.GetP1() == mP1; //Czy mP0 i mP1 równe z P0 i P1 z podanej linii
}

float Line2D::MinDistanceFrom(const Vec2D& p, bool limitToSegment) const //dystans z p do linii
{
	return p.Distance(ClosestPoint(p, limitToSegment)); //uzycie Distance z Vec2D
}

Vec2D Line2D::ClosestPoint(const Vec2D& p, bool limitToSegment) const
{
	Vec2D p0ToP = p - mP0; //wektor od mP0 do p

	Vec2D p0ToP1 = mP1 - mP0; //wektor od mP0 do mP1 (wektor wzdluz linii)

	float l2 = p0ToP1.Mag2(); //kwadrat slugosci wektora mP0 do p

	float dot = p0ToP.Dot(p0ToP1); //iloczyn skalarny obu wektorow

	float t = dot / l2; //pozycja nablizszego punktu na linii wzdluz wektora P0P1

	if(limitToSegment) //jak limit true
	{//zapewnienie, ze najblizszy punkt znajduje sie w segmencie miedzy dwoma punktami tworzacymi linie
		t = std::fmax(0, std::fmin(1.0f, t));// obcina t tak, by zmiescila sie w przedziale od 0 do 1
	}

	return mP0 + p0ToP1 * t; // zwraca najblizszy punkt na linii
}


float Line2D::Length() const
{
	return mP1.Distance(mP0); //Odleglosc miedzy punktami mP1 i mP0
}



