#include "Vec2D.h"
#include <cassert>
#include <cmath>

bool IsEqual(float x, float y) //porownanie 2 liczb z zadana tolerancja
{
	return fabsf(x-y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y) //to samo ale wieksze rowne
{
	return x > y || IsEqual(x, y);
}

const Vec2D Vec2D::Zero; //def stalej skladowej Zero klasy Vec2D, rownej obiektowi Vec 2D o wsp (0,0)

Vec2D operator*(float scalar, const Vec2D& vec) //mnozenie skalara i obiektu Vec2D (mnozenie wsporzednych)
{
	return vec * scalar;
}

bool Vec2D::operator==(const Vec2D& vec2) const //operator rownosci dwoch wektorow z zadana tolerancja
{
	return IsEqual(mX, vec2.mX) && IsEqual(mY, vec2.mY);
}

Vec2D Vec2D::operator-() const //negacja wektora
{
	return Vec2D(-mX, -mY);
}

Vec2D Vec2D::operator*(float scale) const //mnozenie wektora przez skale, zwraca wektor
{
	return Vec2D(scale * mX, scale * mY);
}

Vec2D Vec2D::operator/(float scale) const //dzielenie wektora przez skalar
{
	assert(fabsf(scale) > EPSILON); //skalar nie jest 0

	return Vec2D( mX / scale, mY / scale);
}

Vec2D Vec2D::operator+(const Vec2D& vec) const //dodawanie wektorow
{
	return Vec2D(mX + vec.mX, mY + vec.mY);
}

Vec2D Vec2D::operator-(const Vec2D& vec) const //odejmowanie wektorow
{
	return Vec2D(mX - vec.mX, mY - vec.mY);
}

Vec2D& Vec2D::operator-=(const Vec2D& vec) //odejmowanie i przypisywanie
{
	*this = *this - vec;
	return *this;
}


float Vec2D::Mag2() const //kwadrat dlugosci, do oblicznei dlugosci
{
	return Dot(*this);
}

float Vec2D::Mag() const // dlugosc
{
	return sqrtf(Mag2());
}


Vec2D Vec2D::GetUnitVec() const //wektor jednostkowy
{
	float mag = Mag();

	if(mag > EPSILON)			//Jezeli dlugosc >0 to dzieli wektor przez dlugosc
	{
		return *this / mag;
	}

	return Vec2D::Zero;			//inaczej 0
}

float Vec2D::Distance(const Vec2D& vec) const //odleglosc wektorow
{
	return (vec - *this).Mag(); //to dlugosc roznicy miedzy dwoma wektorami
}


float Vec2D::Dot(const Vec2D& vec) const //iloczyn skalarny
{
	return mX * vec.mX + mY * vec.mY;
}


Vec2D Vec2D::ProjectOnto(const Vec2D& vec2) const //rzut
{
	Vec2D unitVec2 = vec2.GetUnitVec();

	float dot = Dot(unitVec2);

	return unitVec2 * dot;
}
Vec2D Vec2D::Reflect(const Vec2D& normal) const //odbicie od normalnej
{
	//v - 2(v dot n)n - wzor
	return *this - 2 * ProjectOnto(normal);
}

void Vec2D::Rotate(float angle, const Vec2D& aroundPoint) // rotacja wektora o dany kat wokol danego punktu
{
	float cosine = cosf(angle);
	float sine = sinf(angle);

	Vec2D thisVec(mX, mY);

	thisVec -= aroundPoint;

	float xRot = thisVec.mX * cosine - thisVec.mY * sine;
	float yRot = thisVec.mX * sine + thisVec.mY * cosine;

	Vec2D rot = Vec2D(xRot, yRot);

	*this = rot + aroundPoint;
}

