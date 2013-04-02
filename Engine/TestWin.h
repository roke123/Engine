#ifndef __TESTWIN_H__
#define __TESTWIN_H__

#include <Windows.h>
#include <D2D1.h>
#include <D2DErr.h>
#include <dinput.h>
#include "SwapChain2D.h"
#include "MyFactory.h"
#include "IntersectionSystem.h"
#include "MovableBoundingImage.h"
#include "InputSystem.h"

class TestWin
{
public:
	TestWin( );
	~TestWin( );

	bool WinInit( HINSTANCE hInstance, int width, int height, bool isWindow );
	friend LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

	virtual void WinRender( );

	virtual void WinUpdate( );

	void WinShutDown( );

private:
	virtual bool LoadContent( );
	virtual void UnloadContent( );

private:
	//·ÀÖ¹¸´ÖÆ´°¿Ú
	TestWin( const TestWin& t ) { };
	TestWin operator = ( const TestWin& t ) { };

private:
	bool isOpenClipFilter;

	IntersectionSystem intersectionSystem_;
	InputSystem inputSystem_;

	HINSTANCE hInstance_;
	HWND hWnd_;

	ID2D1Factory * d2dFactory_;
	SwapChain2D swapChain2d_;

	Matrix3x3_F transform, rotation, scale;

	Polygon2DType * polygon;
	Rectangle2DType * rectangle;
	ImageType * image;
	MovableBoundingImage * image1;
	AnimationGroup * animationGroup_;
};

#endif	//end of TestWin.h