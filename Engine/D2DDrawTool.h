#ifndef __D2DDRAWTOOL_H__
#define __D2DDRAWTOOL_H__

#include "DrawTool.h"
#include "SwapChain2D.h"
#include <wincodec.h>
#include <DWrite.h>

class SwapChain2D;

class D2DDrawTool : public DrawTool
{
public:
	D2DDrawTool( SwapChain2D * swapChain );
	~D2DDrawTool();

	//初始化函数
	bool Init();

	//卸载DrawTool
	void ShutDown();

	///////////////////////////////////////////////////override/////////////////////////////////////////////

	int DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1, const Color_F& c ) const;

	int DrawPolygon( const Polygon2D& polygon, const Color_F& c ) const;

	void Clear( const Color_F& color ) const; 

	//画实心多边形
	void DrawSolidPolygon( const Polygon2D& polygon, const Color_F& color ) const;

	//画三角形
	void DrawSolidTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, const Color_F& color ) const;

	//画实心矩形
	void DrawSolidRectangle( const Rectangle2D& rectangle, const Color_F& color ) const;

	//画图像
	void DrawImage( ImageType& image, const Rect_F& destination, float alpha = 1.0f ) const;

	//画图像
	void DrawImage( ImageType& image, const Rect_F& destination,const Rect_F& source,
		float alpha = 1.0f ) const;

	//从文件中创建image
	HRESULT CreateImageFromFile( const wstring filename, ImageType ** image ) const;

	HRESULT CreateImageFormImage( const Rect_U& rect, ImageType * inImage, ImageType ** outImage ) const;

	HRESULT DrawString( const wchar_t * str, Rect_F rc, Color_F color );

	HRESULT SetTextFormat( const wchar_t * familyName, float fontSize,
		const wchar_t * localName );

private:
	//画直线by画刷
	void DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1
		, ID2D1SolidColorBrush * brush ) const;

	//画平顶三角形
	void DrawSolidTopTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, ID2D1SolidColorBrush * brush ) const;

	//画平底三角形
	void DrawSolidButtonTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, ID2D1SolidColorBrush * brush ) const;

	////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	SwapChain2D * swapChain_;

	IWICImagingFactory2 * wicFactory_;

	IDWriteFactory * pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;

};	//end of class D2DDrawTool

#endif	//end of D2DDrawTool.h