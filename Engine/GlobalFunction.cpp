#include "GlobalFunction.h"
#include <math.h>
#include <time.h>
#include <sys/timeb.h> 

void SetMatrix( Polygon2DType * polygon, const Matrix3x3_F& worldMatrix )
{
	float sum_x = 0.0f, sum_y = 0.0f;

	for( int i = 0; i < polygon->numVertex_; ++ i )
	{
		polygon->worldVertexArray_[i] = polygon->pVertexArray_[i] * worldMatrix;
		sum_x += polygon->worldVertexArray_[i].x;
		sum_y += polygon->worldVertexArray_[i].y;
	}

	polygon->worldVertexFirst = polygon->worldVertexArray_[0];
	polygon->worldVertexCenter.x = sum_x / polygon->numVertex_;
	polygon->worldVertexCenter.y = sum_y / polygon->numVertex_;
}

void SetMatrix( Rectangle2DType * rectangle, const Matrix3x3_F& worldMatrix )
{
	rectangle->worldVertex0 = rectangle->p0 * worldMatrix;
	rectangle->worldVertex1 = rectangle->p1 * worldMatrix;

	rectangle->worldVertexCenter.x = (rectangle->worldVertex0.x - rectangle->worldVertex1.x) / 2;
	rectangle->worldVertexCenter.y = (rectangle->worldVertex0.y - rectangle->worldVertex1.y) / 2; 
}

float ComputeDistance( const Vertex2D_F& p0, const Vertex2D_F& p1 )
{
	float x = p0.x - p1.x, y = p0.y - p1.y;
	return sqrt( x * x + y * y );
}

float ComputeDistance( float x0, float y0, float x1, float y1 )
{
	float x = x0 - x1, y = y0 - y1;
	return sqrt( x * x + y * y );
}

DWORD GetTickClock()
{
	return GetTickCount();
}

float Dot( const Vertex2D_F& v1, const Vertex2D_F& v2 )
{
	return v1.x * v2.y - v1.y * v2.x;
}

wstring StringToWString(const std::string& s)
{
	 std::wstring temp(s.length(),L' ');
	 std::copy(s.begin(), s.end(), temp.begin());
	 return temp;
}