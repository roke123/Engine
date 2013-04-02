#ifndef __MYFACTORY_H__
#define __MYFACTORY_H__

#include <memory>
#include <assert.h>
using namespace std;

#include "ClipFilter.h"
#include "Matrix3x3.h"

class MyFactory
{
public:
	//pMyFactory_使用了引用计数因此不需要考虑析构问题
	~MyFactory() {};

	//////////////////////////////////////////////////创建ClipFilter对象//////////////////////////////////////////////////////

	//创建方形裁剪器
	bool CreateRectangleClipFilter( const Rectangle2DType& rect, ClipFilter *& filter ) const;

	//创建多边形裁剪器
	bool CreatePolygon2DClipFilter( const Polygon2DType& polygon, ClipFilter *& filter ) const;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////创建各种图形/////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////创建各种矩阵/////////////////////////////////////////////////////////

	//创建单位矩阵
	Matrix3x3_F CreateIdentityMatrix3x3();

	//创建平移矩阵
	Matrix3x3_F CreateTransformMatrix3x3( float move_x, float move_y );

	//创建旋转矩阵，采用弧度作为输入
	Matrix3x3_F CreateRotationMatrix3x3( float rat );

	//创建缩放矩阵
	Matrix3x3_F CreateScaleMatrix3x3( float scale_x, float scale_y );

	static MyFactory * GetMyFactory() 
	{
		if( pMyFactory_ == NULL )
		{
			pMyFactory_.reset( new MyFactory() );
		}

		return pMyFactory_.get();
	}

private:
	MyFactory() {}

private:
	//引用计数的单实例指针
	static shared_ptr< MyFactory > pMyFactory_; 
};

#endif