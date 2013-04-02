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
	//初始化屏幕图像裁剪器
	DrawTool() : RefObject(), screenClipFilter_(0) 
	{

	}

	//虚析构函数，用于继承
	virtual ~DrawTool() 
	{ 
		ShutDown();
	};

	//初始化函数
	virtual bool Init()
	{
		return true;
	}

	//卸载DrawTool
	virtual void ShutDown() 
	{
		if( screenClipFilter_ ) delete screenClipFilter_;

		screenClipFilter_ = 0;
	}

	//划出一条直线
	virtual int DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1, const Color_F& c )const = 0;

	//画出一个多边形线框
	virtual int DrawPolygon( const Polygon2DType& polygon, const Color_F& c ) const = 0;

	//清理当前画面
	virtual void Clear( const Color_F& color = BLACK ) const = 0;

	//画实心多边形
	virtual void DrawSolidPolygon( const Polygon2DType& polygon, const Color_F& color ) const = 0;

	//画实心三角形
	virtual void DrawSolidTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, const Color_F& color ) const = 0;

	//画实心矩形
	virtual void DrawSolidRectangle( const Rectangle2DType& rectangle, const Color_F& color ) const = 0;

	//画图像
	virtual void DrawImage( ImageType& image, const Rect_F& destination, float alpha = 1.0f ) const = 0;

	//画图像
	virtual void DrawImage( ImageType& image, const Rect_F& destination,const Rect_F& source,
		float alpha = 1.0f ) const = 0;

	//从文件中创建Image
	virtual HRESULT CreateImageFromFile( const wstring filename, ImageType ** image ) const = 0;

	//创建一个多边形
	bool CreatePolygon2D( Vertex2D_F * pVertexList, int numVertex, Polygon2DType ** pPolygon ) const;

	//创建一个矩形
	bool CreateRectangle2D( const Vertex2D_F& p0, const Vertex2D_F& p1, Rectangle2DType ** pRectangle ) const;
	bool CreateRectangle2D( const Vertex2D_F& p0, int width, int height, Rectangle2DType ** pRectangle ) const;

	//创建一个动画组
	virtual bool CreateAnimationGroupWithFile( const wstring& filename,
		const Rect_F& rc, AnimationGroup *& group ) = 0;

protected:
	ClipFilter * screenClipFilter_;

};

#endif	//end of DrawTool.h