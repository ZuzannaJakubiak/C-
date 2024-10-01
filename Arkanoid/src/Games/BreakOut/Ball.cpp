/*
 * Ball.cpp
 *
 *  Created on: 6 sty 2023
 *      Author: Zuzanna Jakubiak
 */

#include "Ball.h"
#include "Screen.h"
#include "Circle.h"
#include <cmath>

const float Ball::RADIUS = 5.0f;

Ball::Ball():Ball(Vec2D::Zero, Ball::RADIUS)
{

}

Ball::Ball(const Vec2D& pos, float radius):mBBox(pos-Vec2D(radius, radius), radius*2.0f, radius*2.0f), mVelocity(Vec2D::Zero)
{

}

void Ball::Update(uint32_t dt)
{
	mBBox.MoveBy(mVelocity *static_cast<float>(dt) / 1000.0f);
}


void Ball::Draw(Screen& screen)
{
	Circle circ = {mBBox.GetCenterPoint(), GetRadius()};
	screen.Draw(circ, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge)
{
	if(edge.normal == DOWN_DIR)
	{
		mBBox.MoveTo(Vec2D(mBBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
	}
	else if(edge.normal == RIGHT_DIR)
	{
		mBBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBBox.GetTopLeftPoint().GetY()));
	}
	else if(edge.normal == UP_DIR)
	{
		mBBox.MoveTo(Vec2D(mBBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBBox.GetHeight()));
	}
	else if(edge.normal == LEFT_DIR)
	{
		mBBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() - mBBox.GetWidth(), mBBox.GetTopLeftPoint().GetY()));
	}

	pointOnEdge = edge.edge.ClosestPoint(mBBox.GetCenterPoint(), limitToEdge);
}

void Ball::Bounce(const BoundaryEdge& edge)
{
	Vec2D pointOnEdge;

	MakeFlushWithEdge(edge, pointOnEdge, false);

	mVelocity = mVelocity.Reflect(edge.normal);

}

void Ball::MoveTo(const Vec2D& point)
{
	mBBox.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
}


