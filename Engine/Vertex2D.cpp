#include "Vertex2D.h"

Vertex2D_F operator + ( const Vertex2D_F& v0, const Vertex2D_F& v1 )
{
	Vertex2D_F temp;
	temp.x = v0.x + v1.x;
	temp.y = v0.y + v1.y;

	return temp;
}

Vertex2D_F operator += ( Vertex2D_F& v0, const Vertex2D_F& v1 )
{
	v0.x += v1.x;
	v0.y += v1.y;

	return v0;
}