#include "MyFactory.h"
#include "RectangleClipFilter.h"

shared_ptr< MyFactory > MyFactory::pMyFactory_ = NULL;

//////////////////////////////////////////////////创建ClipFilter对象//////////////////////////////////////////////////////

bool MyFactory::CreatePolygon2DClipFilter( const Polygon2DType& polygon, ClipFilter *& filter ) const
{
	//暂时留空
	return true;
}

bool MyFactory::CreateRectangleClipFilter( const Rectangle2DType& rect, ClipFilter *& filter ) const
{
	assert( filter == NULL );

	filter = new RectangleClipFilter( rect );

	if( filter == NULL )
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Matrix3x3_F MyFactory::CreateIdentityMatrix3x3()
{
	Matrix3x3_F result;
	memset( &result, 0, sizeof(Matrix3x3_F) );

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;

	return result;
}

Matrix3x3_F MyFactory::CreateTransformMatrix3x3( float move_x, float move_y )
{
	Matrix3x3_F result = CreateIdentityMatrix3x3();

	result.m[2][0] = move_x;
	result.m[2][1] = move_y;

	return result;
}

Matrix3x3_F MyFactory::CreateRotationMatrix3x3( float rat )
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
Matrix3x3_F MyFactory::CreateScaleMatrix3x3( float scale_x, float scale_y )
{
	Matrix3x3_F result = CreateIdentityMatrix3x3();

	result.m[0][0] = scale_x;
	result.m[1][1] = scale_y;

	return result;
}



