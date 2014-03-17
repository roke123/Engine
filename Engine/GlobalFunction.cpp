#include "GlobalFunction.h"
#include <math.h>
#include <time.h>
#include <assert.h>
#include <sys/timeb.h> 

void SetMatrix( Polygon2D * polygon, const Matrix3x3_F& worldMatrix )
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

void SetMatrix( Rectangle2D * rectangle, const Matrix3x3_F& worldMatrix )
{
	rectangle->worldVertex0 = rectangle->p0 * worldMatrix;
	rectangle->worldVertex1 = rectangle->p1 * worldMatrix;

	rectangle->worldVertexCenter.x = (rectangle->worldVertex0.x + rectangle->worldVertex1.x) / 2;
	rectangle->worldVertexCenter.y = (rectangle->worldVertex0.y + rectangle->worldVertex1.y) / 2; 
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

long GetTickClock()
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

bool CreatePolygon2DClipFilter( const Polygon2D& polygon, ClipFilterPtr * filter )
{
	//暂时留空
	return true;
}

bool CreateRectangleClipFilter( const Rectangle2D& rect, ClipFilterPtr * filter )
{
	assert( filter == NULL );

	filter->reset( new RectangleClipFilter( rect ) );

	if( filter == NULL )
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix3x3_F CreateIdentityMatrix3x3()
{
	Matrix3x3_F result;
	memset( &result, 0, sizeof(Matrix3x3_F) );

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;

	return result;
}

Matrix3x3_F CreateTransformMatrix3x3( float move_x, float move_y )
{
	Matrix3x3_F result = CreateIdentityMatrix3x3();

	result.m[2][0] = move_x;
	result.m[2][1] = move_y;

	return result;
}

Matrix3x3_F CreateRotationMatrix3x3( float rat )
{
	Matrix3x3_F result = CreateIdentityMatrix3x3();

	//对x分量
	result.m[1][0] = sin( rat );
	result.m[0][0] = cos( rat );

	//对y分量
	result.m[1][1] = cos( rat );
	result.m[0][1] = -sin( rat );
	
	return result;
}

//创建缩放矩阵
Matrix3x3_F CreateScaleMatrix3x3( float scale_x, float scale_y )
{
	Matrix3x3_F result = CreateIdentityMatrix3x3();

	result.m[0][0] = scale_x;
	result.m[1][1] = scale_y;

	return result;
}
