#ifndef __DRAWTOOL_H__
#define __DRAWTOOL_H__

#include <D2D1.h>
#include "GraphType.h"
#include "Image.h"
#include "ClipFilter.h"

#include <string>
using namespace std;

class AnimationGroup;

class DrawTool
{
public:
	//初始化屏幕图像裁剪器
	DrawTool() : screenClipFilter_(0) 
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
		screenClipFilter_ = 0;
	}

	//划出一条直线
	virtual int DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1, const Color_F& c )const = 0;

	//画出一个多边形线框
	virtual int DrawPolygon( const Polygon2D& polygon, const Color_F& c ) const = 0;

	//清理当前画面
	virtual void Clear( const Color_F& color = BLACK ) const = 0;

	//画实心多边形
	virtual void DrawSolidPolygon( const Polygon2D& polygon, const Color_F& color ) const = 0;

	//画实心三角形
	virtual void DrawSolidTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, const Color_F& color ) const = 0;

	//画实心矩形
	virtual void DrawSolidRectangle( const Rectangle2D& rectangle, const Color_F& color ) const = 0;

	//画图像
	virtual void DrawImage( ImageType& image, const Rect_F& destination, float alpha = 1.0f ) const = 0;

	//画图像
	virtual void DrawImage( ImageType& image, const Rect_F& destination,const Rect_F& source,
		float alpha = 1.0f ) const = 0;

	//从文件中创建Image
	virtual HRESULT CreateImageFromFile( const wstring filename, ImageType ** image ) const = 0;

	virtual HRESULT CreateImageFormImage( const Rect_U& rect, ImageType * inImage, ImageType ** outImage ) const = 0;

	virtual HRESULT DrawString( const wchar_t * str, Rect_F rc, Color_F color ) = 0;

	virtual HRESULT SetTextFormat( const wchar_t * familyName, float fontSize,
								   const wchar_t * localName ) = 0;

	//创建一个多边形
	bool CreatePolygon2D( Vertex2D_F * pVertexList, int numVertex, Polygon2D ** pPolygon ) const;

	//创建一个矩形
	bool CreateRectangle2D( const Vertex2D_F& p0, const Vertex2D_F& p1, Rectangle2D ** pRectangle ) const;
	bool CreateRectangle2D( const Vertex2D_F& p0, int width, int height, Rectangle2D ** pRectangle ) const;

protected:
	ClipFilterPtr screenClipFilter_;

};

#endif	//end of DrawTool.h