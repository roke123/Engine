#include "Matrix3x3.h"

Vertex2D_F operator * ( const Vertex2D_F& vertex, const Matrix3x3_F& matrix )
{
	Vertex2D_F result;

	result.x = vertex.x * matrix.m[0][0] + vertex.y * matrix.m[1][0] +
		matrix.m[2][0];

	result.y = vertex.x * matrix.m[0][1] + vertex.y * matrix.m[1][1] +
		matrix.m[2][1];

	return result;
}

Matrix3x3_F operator * ( const Matrix3x3_F& matrix0, const Matrix3x3_F& matrix1 )
{
	Matrix3x3_F result;

	for( int row = 0; row < 3; ++ row )
		for( int col = 0; col < 3; ++ col )
		{
			float sum = 0;

			for( int index = 0; index < 3; ++ index )
				sum += matrix0.m[row][index] * matrix1.m[index][col];

			result.m[row][col] = sum;
		}
	return result;
}