#ifndef __GLOBALFUNCTION_H__
#define __GLOBALFUNCTiON_H__

#include "Matrix3x3.h"
#include "RectangleClipFilter.h"

#include <string>
using namespace std;

//��һ�������������任
void SetMatrix( Polygon2D * polygon, const Matrix3x3_F& worldMatrix );

//��һ������������任
void SetMatrix( Rectangle2D * rectangle, const Matrix3x3_F& worldMatrix );

//���������ľ���
float ComputeDistance( const Vertex2D_F& p0, const Vertex2D_F& p1 );

//���������ľ���
float ComputeDistance( float x0, float y0, float x1, float y1 );

//ȡ�õ�ǰϵͳ����ʱ�䣬�Ժ���Ϊ��λ
long GetTickClock();

//�������������ĵ��
float Dot( const Vertex2D_F& v1, const Vertex2D_F& v2 );

wstring StringToWString(const std::string& s);

//�������βü���
bool CreateRectangleClipFilter( const Rectangle2D& rect, ClipFilterPtr * filter );

//��������βü���
bool CreatePolygon2DClipFilter( const Polygon2D& polygon, ClipFilterPtr * filter );

//������λ����
Matrix3x3_F CreateIdentityMatrix3x3();

//����ƽ�ƾ���
Matrix3x3_F CreateTransformMatrix3x3( float move_x, float move_y );

//������ת���󣬲��û�����Ϊ����
Matrix3x3_F CreateRotationMatrix3x3( float rat );

//�������ž���
Matrix3x3_F CreateScaleMatrix3x3( float scale_x, float scale_y );

#endif	// end of GlobalFunction.h