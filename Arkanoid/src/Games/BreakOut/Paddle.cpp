#include "Paddle.h"
#include "Screen.h"
#include "Ball.h"
#include <cmath>

void Paddle::Init(const AARectangle& rect, const AARectangle& boundary)
{
	Excluder::Init(rect);//Init Excludera jako rect
	mBoundary = boundary;//granice
	mDirection = PaddleDirection::NONE; //kierunek NONE
}

void Paddle::Update(uint32_t dt, Ball& ball)
{
	//jezeli jest kolizja to odbicie od krawedzi)
	if(GetAARectangle().ContainsPoint(ball.GetPosition()))
	{
		Vec2D pointOnEdge;
		//Wyrownanie krawedzi pilki z punktem na krawedzi
		ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
	}

	if(mDirection != PaddleDirection::NONE) //jezeli belka sie porusza
	{
		Vec2D dir; //Vec2D przechowujacy kierunek
		if(mDirection == PaddleDirection::LEFT) //jezeli w lewo
		{
			dir = LEFT_DIR; //to kierunek w lewo
		}
		else
		{
			dir = RIGHT_DIR; //w prawo
		}

		Vec2D dx = dir * VELOCITY * static_cast<float>(dt) / 1000.0f; // przesuniecie


		MoveBy(dx);

		const AARectangle& aaRect = GetAARectangle();
		//Belka nie moze poruszac sie poza swoimi granicami
		if(IsGreaterThanOrEqual(mBoundary.GetTopLeftPoint().GetX(), aaRect.GetTopLeftPoint().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetTopLeftPoint().GetX(), aaRect.GetTopLeftPoint().GetY()));
		}
		else if(IsGreaterThanOrEqual(aaRect.GetBottomRightPoint().GetX(), mBoundary.GetBottomRightPoint().GetX()))
		{
			MoveTo(Vec2D(mBoundary.GetBottomRightPoint().GetX() - aaRect.GetWidth(), aaRect.GetTopLeftPoint().GetY()));
		}
	}
}

void Paddle::Draw(Screen& screen)
{
	screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue()); //render na ekranie
}

bool Paddle::Bounce(Ball& ball)
{
	BoundaryEdge edge; //granica balki
	if(HasCollided(ball.GetBoundingRect(), edge)) //jezeli kolicja ball i granicy belki
	{
			Vec2D pointOnEdge; //punkty na granicy

			ball.MakeFlushWithEdge(edge, pointOnEdge, true); //Wyrownanie

			if(edge.edge == GetEdge(TOP_EDGE).edge) //Jezeli granica to gorna granica
			{
				float edgeLength = edge.edge.Length(); //dlugosc
				//odleglosc od krawedzi w zakresie 0-1
				float tx = (pointOnEdge.GetX() - edge.edge.GetP0().GetX())/edgeLength;

				if(((tx <= CORNER_BOUNCE_AMT) && ball.GetVelocity().GetX() >0) ||
					(tx >= (1.0f - CORNER_BOUNCE_AMT) && ball.GetVelocity().GetX() < 0))
				{
					ball.SetVelocity(-ball.GetVelocity()); //negacja
					return true;
				}
			}

			ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal)); //inaczej odbicie wzgledem normalnej
			return true;
	}

	return false;
}



