#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTiON_H__

#include "Matrix3x3.h"

#include <string>
using namespace std;

//对一个多边形做矩阵变换
void SetMatrix( Polygon2DType * polygon, const Matrix3x3_F& worldMatrix );

//对一个矩形做矩阵变换
void SetMatrix( Rectangle2DType * rectangle, const Matrix3x3_F& worldMatrix );

//计算两点间的距离
float ComputeDistance( const Vertex2D_F& p0, const Vertex2D_F& p1 );

//计算两点间的距离
float ComputeDistance( float x0, float y0, float x1, float y1 );

//取得当前系统启动时间，以毫秒为单位
DWORD GetTickClock();

//计算两个向量的点积
float Dot( const Vertex2D_F& v1, const Vertex2D_F& v2 );

wstring StringToWString(const std::string& s);

#endif	// end of GlobalFunction.h