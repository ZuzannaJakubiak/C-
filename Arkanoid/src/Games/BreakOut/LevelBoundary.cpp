#include "LevelBoundary.h"
#include "Ball.h"

LevelBoundary::LevelBoundary(const AARectangle& boundary)
{
	mIncluder.Init(boundary, true); //Init granice poziomu, reverse normals
}

bool LevelBoundary::HasCollided(const Ball &ball, BoundaryEdge& edge)
{
	for( int i = 0; i < NUM_EDGES; ++i) //dla kazdej krawedzi
	{
		BoundaryEdge collisionEdge = mIncluder.GetEdge(static_cast<EdgeType>(i)); //kolizyjna granica
		if(collisionEdge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius()) //Jezeli min dystans miedzy srodkiem pilki a linia < promienien
		{
			edge = collisionEdge; //krawedz jest kolizyjna
			return true;
		}
	}
	return false;
}

