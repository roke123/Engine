#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTiON_H__

#include "Matrix3x3.h"

#include <string>
using namespace std;

//��һ�������������任
void SetMatrix( Polygon2DType * polygon, const Matrix3x3_F& worldMatrix );

//��һ������������任
void SetMatrix( Rectangle2DType * rectangle, const Matrix3x3_F& worldMatrix );

//���������ľ���
float ComputeDistance( const Vertex2D_F& p0, const Vertex2D_F& p1 );

//���������ľ���
float ComputeDistance( float x0, float y0, float x1, float y1 );

//ȡ�õ�ǰϵͳ����ʱ�䣬�Ժ���Ϊ��λ
DWORD GetTickClock();

//�������������ĵ��
float Dot( const Vertex2D_F& v1, const Vertex2D_F& v2 );

wstring StringToWString(const std::string& s);

#endif	// end of GlobalFunction.h