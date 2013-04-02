#ifndef __D2DDRAWTOOL_H__
#define __D2DDRAWTOOL_H__

#include "DrawTool.h"
#include "SwapChain2D.h"
#include <wincodec.h>

class SwapChain2D;

class D2DDrawTool : public DrawTool
{
public:
	D2DDrawTool( SwapChain2D * swapChain );
	~D2DDrawTool();

	//��ʼ������
	bool Init();

	//ж��DrawTool
	void ShutDown();

	///////////////////////////////////////////////////override/////////////////////////////////////////////

	int DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1, const Color_F& c ) const;

	int DrawPolygon( const Polygon2DType& polygon, const Color_F& c ) const;

	void Clear( const Color_F& color ) const; 

	//��ʵ�Ķ����
	void DrawSolidPolygon( const Polygon2DType& polygon, const Color_F& color ) const;

	//��������
	void DrawSolidTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, const Color_F& color ) const;

	//��ʵ�ľ���
	void DrawSolidRectangle( const Rectangle2DType& rectangle, const Color_F& color ) const;

	//��ͼ��
	void DrawImage( ImageType& image, const Rect_F& destination, float alpha = 1.0f ) const;

	//��ͼ��
	void DrawImage( ImageType& image, const Rect_F& destination,const Rect_F& source,
		float alpha = 1.0f ) const;

	//���ļ��д���image
	HRESULT CreateImageFromFile( const wstring filename, ImageType ** image ) const;

	//����һ��������
	bool CreateAnimationGroupWithFile( const wstring& filename,
		const Rect_F& rc, AnimationGroup *& group );

private:
	//��ֱ��by��ˢ
	void DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1
		, ID2D1SolidColorBrush * brush ) const;

	//��ƽ��������
	void DrawSolidTopTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, ID2D1SolidColorBrush * brush ) const;

	//��ƽ��������
	void DrawSolidButtonTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, ID2D1SolidColorBrush * brush ) const;

	////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	SwapChain2D * swapChain_;

	IWICImagingFactory2 * wicFactory_;
};	//end of class D2DDrawTool

#endif	//end of D2DDrawTool.h