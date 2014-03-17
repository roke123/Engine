#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__

#include <memory>
using namespace std::tr1;

#include "Vertex2D.h"

class Matrix3x3_F
{
public:
	//矩阵与顶点乘法
	friend Vertex2D_F operator * ( const Vertex2D_F& vertex, const Matrix3x3_F& matrix );

	//矩阵与矩阵乘法
	friend Matrix3x3_F operator * ( const Matrix3x3_F& matrix0, const Matrix3x3_F& matrix1 );

public:
	float m[3][3];
};	//end of class Matrix3x3_F

typedef shared_ptr<Matrix3x3_F> Matrix3x3_FPtr;

#endif	//end of Matrix3x3.h