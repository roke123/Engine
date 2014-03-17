#include "SimpleApp.h"

bool SimpleApp::Init( HINSTANCE hInstance, int width, int height
					 , bool isWindow, WndProc process )
{
	WNDCLASSEX wndClass = { 0 };
    wndClass.cbSize = sizeof( WNDCLASSEX ) ;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = process;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
    wndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wndClass.lpszMenuName = "坦克大战Demo";
    wndClass.lpszClassName = "TestWin";

	HRESULT result = 0;

	if( !RegisterClassEx( &wndClass ) )
	{
		MessageBox( 0, "Can't register a window", 0, 0 );
		return false;
	}

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

	hWnd_ = CreateWindow( "TestWin", 0, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 200, 25
		, rc.right - rc.left,rc.bottom - rc.top, 0, 0, hInstance, 0 );

	if( !hWnd_ )
	{
		MessageBox( 0, "Can't Create a window", 0, 0 );
		return false;
	}

	ShowWindow( hWnd_, SW_SHOW );

	//填充基本属性
	hInstance_ = hInstance;
	width_ = width;
	height_ = height;
	isWindow_ = isWindow;

	return true;
}
