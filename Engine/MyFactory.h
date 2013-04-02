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
	//pMyFactory_ʹ�������ü�����˲���Ҫ������������
	~MyFactory() {};

	//////////////////////////////////////////////////����ClipFilter����//////////////////////////////////////////////////////

	//�������βü���
	bool CreateRectangleClipFilter( const Rectangle2DType& rect, ClipFilter *& filter ) const;

	//��������βü���
	bool CreatePolygon2DClipFilter( const Polygon2DType& polygon, ClipFilter *& filter ) const;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////��������ͼ��/////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////�������־���/////////////////////////////////////////////////////////

	//������λ����
	Matrix3x3_F CreateIdentityMatrix3x3();

	//����ƽ�ƾ���
	Matrix3x3_F CreateTransformMatrix3x3( float move_x, float move_y );

	//������ת���󣬲��û�����Ϊ����
	Matrix3x3_F CreateRotationMatrix3x3( float rat );

	//�������ž���
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
	//���ü����ĵ�ʵ��ָ��
	static shared_ptr< MyFactory > pMyFactory_; 
};

#endif