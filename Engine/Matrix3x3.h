#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__

#include "GraphType.h"

class Matrix3x3_F
{
	//���ڴ����������Ԫ��
	friend class MyFactory;

public:
	//�����붥��˷�
	friend Vertex2D_F operator * ( const Vertex2D_F& vertex, const Matrix3x3_F& matrix );

	//���������˷�
	friend Matrix3x3_F operator * ( const Matrix3x3_F& matrix0, const Matrix3x3_F& matrix1 );

private:
	float m[3][3];
};	//end of class Matrix3x3_F

#endif	//end of Matrix3x3.h