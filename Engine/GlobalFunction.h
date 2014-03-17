#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTiON_H__

#include "Matrix3x3.h"
#include "RectangleClipFilter.h"

#include <string>
using namespace std;

//对一个多边形做矩阵变换
void SetMatrix( Polygon2D * polygon, const Matrix3x3_F& worldMatrix );

//对一个矩形做矩阵变换
void SetMatrix( Rectangle2D * rectangle, const Matrix3x3_F& worldMatrix );

//计算两点间的距离
float ComputeDistance( const Vertex2D_F& p0, const Vertex2D_F& p1 );

//计算两点间的距离
float ComputeDistance( float x0, float y0, float x1, float y1 );

//取得当前系统启动时间，以毫秒为单位
long GetTickClock();

//计算两个向量的点积
float Dot( const Vertex2D_F& v1, const Vertex2D_F& v2 );

wstring StringToWString(const std::string& s);

//创建方形裁剪器
bool CreateRectangleClipFilter( const Rectangle2D& rect, ClipFilterPtr * filter );

//创建多边形裁剪器
bool CreatePolygon2DClipFilter( const Polygon2D& polygon, ClipFilterPtr * filter );

//创建单位矩阵
Matrix3x3_F CreateIdentityMatrix3x3();

//创建平移矩阵
Matrix3x3_F CreateTransformMatrix3x3( float move_x, float move_y );

//创建旋转矩阵，采用弧度作为输入
Matrix3x3_F CreateRotationMatrix3x3( float rat );

//创建缩放矩阵
Matrix3x3_F CreateScaleMatrix3x3( float scale_x, float scale_y );

#endif	// end of GlobalFunction.h