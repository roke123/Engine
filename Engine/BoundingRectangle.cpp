#include "BoundingRectangle.h"
#include "GlobalFunction.h"

void BoundingRectangle::UpdateWithRectangle()
{
	Rectangle2D * graph = (Rectangle2D *)graph_;

	min_x = graph->worldVertex0.x; 
	max_x = graph->worldVertex1.x;
	min_y = graph->worldVertex0.y;
	max_y = graph->worldVertex1.y;
	float temp = 0.0f;

	if( max_x < min_x )
	{
		temp = max_x;
		max_x = min_x;
		min_x = temp;
	}
	
	if( max_y < min_y )
	{
		temp = max_y;
		max_y = min_y;
		min_y = temp;
	}
}

void BoundingRectangle::UpdateWithPolygon()
{
	Polygon2D * graph = (Polygon2D *)graph_;

	min_x = graph->worldVertexArray_[0].x, 
	max_x = graph->worldVertexArray_[0].x,
	min_y = graph->worldVertexArray_[0].y,
	max_y = graph->worldVertexArray_[0].y;

	for( int i = 1; i < graph->numVertex_; ++ i )
	{
		if( graph->worldVertexArray_[i].x < min_x )
			min_x = graph->worldVertexArray_[i].x;
		else if ( graph->worldVertexArray_[i].x > max_x )
			max_x = graph->worldVertexArray_[i].x;

		if( graph->worldVertexArray_[i].y < min_y )
			min_y = graph->worldVertexArray_[i].y;	
		else if ( graph->worldVertexArray_[i].y > max_y )
			max_y = graph->worldVertexArray_[i].y;
	}
}