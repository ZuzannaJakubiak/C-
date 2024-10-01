/*
 * Excluder.cpp
 *
 *  Created on: 4 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#include "Excluder.h"
#include <cmath>
#include <cassert>

void Excluder::Init(const AARectangle& rect, bool reverseNormals)
{
	mAARect = rect; //prostokat
	mReverseNormals = reverseNormals;
	SetupEdges();
}

bool Excluder::HasCollided(const AARectangle& rect, BoundaryEdge& edge) const
{
	if (mAARect.Intersects(rect)) //czy parametr przecina mAARect
	{
		//y min i max  tych prostoktow
		float yMin = mAARect.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ? mAARect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = mAARect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? mAARect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		//wysokosc na tego 'przeciecia'
		float ySize = yMax - yMin;

		//to samo dla x
		float xMin = mAARect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? mAARect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = mAARect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? mAARect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = xMax - xMin;

		if(xSize > ySize) //jezeli szerokosc wieksza od wysokosci
		{
			if(rect.GetCenterPoint().GetY() > mAARect.GetCenterPoint().GetY()) //jezeli y srodka > y srodka Rect (jest nad)
			{
				edge = mEdges[BOTTOM_EDGE];
			}
			else //jest pod
			{
				edge = mEdges[TOP_EDGE];
			}
		}
		else
		{
			if(rect.GetCenterPoint().GetX() < mAARect.GetCenterPoint().GetX()) //jezeli x srodka < x srodka Rect (jest z lewej)
			{
				edge = mEdges[LEFT_EDGE];
			}
			else //jest z prawej
			{
				edge = mEdges[RIGHT_EDGE];
			}
		}

		return true;
	}

	return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& rect) const
{
	BoundaryEdge edge; //granica
	Vec2D offset = Vec2D::Zero;

	if(HasCollided(rect, edge)) //kolizja prostokata i granicy
	{
		float yMin = mAARect.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ? mAARect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();
		float yMax = mAARect.GetBottomRightPoint().GetY() <= rect.GetBottomRightPoint().GetY() ? mAARect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

		float ySize = yMax - yMin;

		float xMin = mAARect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ? mAARect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();
		float xMax = mAARect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ? mAARect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

		float xSize = xMax - xMin;

		//Jezeli Y normalnej nie jest rowne 0
		if(!IsEqual(edge.normal.GetY(), 0))
		{
			offset = (ySize + 1) * edge.normal;
		}
		else
		{
			offset = (xSize + 1) * edge.normal;
		}
	}
	return offset;
}

void Excluder::MoveBy(const Vec2D& delta)
{
	mAARect.MoveBy(delta);
	SetupEdges();
}

void Excluder::MoveTo(const Vec2D& point)
{
	mAARect.MoveTo(point);
	SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
	assert(edge != NUM_EDGES);

	return mEdges[edge];
}

void Excluder::SetupEdges()
{
	mEdges[TOP_EDGE].edge = {mAARect.GetTopLeftPoint().GetX(), mAARect.GetTopLeftPoint().GetY(), mAARect.GetBottomRightPoint().GetX(), mAARect.GetTopLeftPoint().GetY()};
	mEdges[TOP_EDGE].normal = UP_DIR;

	mEdges[LEFT_EDGE].edge = {mAARect.GetTopLeftPoint().GetX(), mAARect.GetTopLeftPoint().GetY(), mAARect.GetTopLeftPoint().GetX(), mAARect.GetBottomRightPoint().GetY()};
	mEdges[LEFT_EDGE].normal = LEFT_DIR;

	mEdges[BOTTOM_EDGE].edge = {mAARect.GetTopLeftPoint().GetX(), mAARect.GetBottomRightPoint().GetY(), mAARect.GetBottomRightPoint().GetX(), mAARect.GetBottomRightPoint().GetY()};
	mEdges[BOTTOM_EDGE].normal = DOWN_DIR;

	mEdges[RIGHT_EDGE].edge = {mAARect.GetBottomRightPoint().GetX(), mAARect.GetTopLeftPoint().GetY(), mAARect.GetBottomRightPoint().GetX(), mAARect.GetBottomRightPoint().GetY()};
	mEdges[RIGHT_EDGE].normal = RIGHT_DIR;

	if(mReverseNormals)
	{
		for(auto& edge : mEdges)
		{
			edge.normal = -edge.normal;
		}
	}
}



