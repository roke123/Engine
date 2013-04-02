#ifndef __DRAWTOOL_H__
#define __DRAWTOOL_H__

#include <D2D1.h>
#include "GraphType.h"
#include "MyFactory.h"
#include "Image.h"
#include "AnimationBase.h"

#include <string>
using namespace std;

class AnimationGroup;

class DrawTool : public RefObject
{
public:
	//��ʼ����Ļͼ��ü���
	DrawTool() : RefObject(), screenClipFilter_(0) 
	{

	}

	//���������������ڼ̳�
	virtual ~DrawTool() 
	{ 
		ShutDown();
	};

	//��ʼ������
	virtual bool Init()
	{
		return true;
	}

	//ж��DrawTool
	virtual void ShutDown() 
	{
		if( screenClipFilter_ ) delete screenClipFilter_;

		screenClipFilter_ = 0;
	}

	//����һ��ֱ��
	virtual int DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1, const Color_F& c )const = 0;

	//����һ��������߿�
	virtual int DrawPolygon( const Polygon2DType& polygon, const Color_F& c ) const = 0;

	//����ǰ����
	virtual void Clear( const Color_F& color = BLACK ) const = 0;

	//��ʵ�Ķ����
	virtual void DrawSolidPolygon( const Polygon2DType& polygon, const Color_F& color ) const = 0;

	//��ʵ��������
	virtual void DrawSolidTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, const Color_F& color ) const = 0;

	//��ʵ�ľ���
	virtual void DrawSolidRectangle( const Rectangle2DType& rectangle, const Color_F& color ) const = 0;

	//��ͼ��
	virtual void DrawImage( ImageType& image, const Rect_F& destination, float alpha = 1.0f ) const = 0;

	//��ͼ��
	virtual void DrawImage( ImageType& image, const Rect_F& destination,const Rect_F& source,
		float alpha = 1.0f ) const = 0;

	//���ļ��д���Image
	virtual HRESULT CreateImageFromFile( const wstring filename, ImageType ** image ) const = 0;

	//����һ�������
	bool CreatePolygon2D( Vertex2D_F * pVertexList, int numVertex, Polygon2DType ** pPolygon ) const;

	//����һ������
	bool CreateRectangle2D( const Vertex2D_F& p0, const Vertex2D_F& p1, Rectangle2DType ** pRectangle ) const;
	bool CreateRectangle2D( const Vertex2D_F& p0, int width, int height, Rectangle2DType ** pRectangle ) const;

	//����һ��������
	virtual bool CreateAnimationGroupWithFile( const wstring& filename,
		const Rect_F& rc, AnimationGroup *& group ) = 0;

protected:
	ClipFilter * screenClipFilter_;

};

#endif	//end of DrawTool.h