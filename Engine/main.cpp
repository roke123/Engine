#include <Windows.h>
#include "TestWin.h"

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow )
{
	UNREFERENCED_PARAMETER( prevInstance );
    UNREFERENCED_PARAMETER( cmdLine );

	TestWin windows;

	bool result = windows.WinInit( hInstance, 800, 640, false );

    if( result == false )
        return -1;

    MSG msg = { 0 };

    while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        } else {
			windows.WinUpdate();
			windows.WinRender();
		}
    }

	windows.WinShutDown();

	return static_cast<int>( msg.wParam );
}