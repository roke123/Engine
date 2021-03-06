#include "BoundingSphere.h"
#include "GlobalFunction.h"

void BoundingSphere::UpdateWithRectangle()
{
	Rectangle2DType * graph = (Rectangle2DType *)graph_;

	r_ = ComputeDistance( graph->worldVertex0, graph->worldVertexCenter );
	x_ = graph->worldVertexCenter.x;
	y_ = graph->worldVertexCenter.y;
}

void BoundingSphere::UpdateWithPolygon()
{
	Polygon2DType * graph = (Polygon2DType *)graph_;

	float r = 0.0f;

	for( int i = 0; i < graph->numVertex_; ++ i )
	{
		float temp = ComputeDistance( graph->worldVertexCenter, graph->worldVertexArray_[i] );
		if( temp > r )
			r = temp;
	}

	x_ = graph->worldVertexCenter.x;
	y_ = graph->worldVertexCenter.y;
	r_ = r;
}