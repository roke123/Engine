#include "TankFight.h"

#include <InputSystem.h>
#include <IntersectionSystem.h>
#include <SoundSystem.h>
#include <AnimationSystem.h>
#include <TimeSystem.h>

LRESULT CALLBACK WndProcess( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_DESTROY :
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}

TankFight::TankFight( ) : SimpleApp()
{
	bgm_ = NULL;
}

TankFight::~TankFight()
{
	ShutDown();
}

bool TankFight::Init( HINSTANCE hInstance, int width, int height,
				   bool isWindow, WndProc process  )
{
	SimpleApp::Init( hInstance, width, height, isWindow, process );

	RECT rc = { 0, 0, width, height };

	if( !swapChain_.Init( 1, hWnd_, rc, 60 ) )
	{
		MessageBox( 0, "Can't create a swap chain", 0, 0 );
		return false;
	}

	InputSystem::GetInputSystem()->Init( hInstance, hWnd_ );
	IntersectionSystem::GetIntersectionSystem()->Init( (float)width, (float)height );
	SoundSystem::GetSoundSystem()->Init();
	AnimationSystem::GetAnimationSystem()->Init( swapChain_.GetDrawTool() );
	TimeSystem::GetTimeSystem()->Init();

    return LoadContent( );
}

void TankFight::Render()
{
	swapChain_.BeginDraw();

	swapChain_.GetDrawTool()->Clear();

	if( initialInterface_.GetChoose() == CK_ENDGAME )
	{
		PostQuitMessage( 0 );
	}
	else if ( initialInterface_.GetChoose() == CK_STARTGAME )
	{
		initialInterface_.ShutDown();

		bgm_->Play(1, 0);

		static bool flag = true;
		static int num = 0;
		if( flag )
		{
			wstring g = L"第";
			g += (num + 48);
			g += L"关";
			swapChain_.GetDrawTool()->Clear();
			Rect_F r = { 350, 300, 500, 400 };
			Color_F c = { 1.0f, 1.0f, 1.0f, 1.0f };
			swapChain_.GetDrawTool()->DrawString( 
				g.c_str(),
				r,
				c
				);

			string file = "map/map";
			file += (num + 48);
			file += ".txt";
			if( !map_.LoadMap( file.c_str(), swapChain_.GetDrawTool() ) )
			{
				PostQuitMessage( 0 );
				return;
			}
			flag = false;

			swapChain_.Flip();
			swapChain_.BeginDraw();
			swapChain_.GetDrawTool()->Clear();

			Sleep(1000);
		}
		
		map_.Draw( swapChain_.GetDrawTool() );

		if( map_.IsWin() )
		{
			map_.UnLoadMap();
			++ num;
			flag = true;
			
			swapChain_.GetDrawTool()->Clear();
			Rect_F r = { 350, 300, 500, 400 };
			Color_F c = { 1.0f, 1.0f, 1.0f, 1.0f };
			if( num > 1 )
			{			
				swapChain_.GetDrawTool()->DrawString( 
					L"恭喜你已经顺利通关",
					r,
					c
					);
			} 
			else
			{			
				swapChain_.GetDrawTool()->DrawString( 
					L"恭喜你已经胜利，准备进入下一关",
					r,
					c
					);
				
			}
			swapChain_.Flip();
			swapChain_.BeginDraw();
			swapChain_.GetDrawTool()->Clear();
			Sleep(1000);
		}

		if( map_.IsEnd() )
		{
			map_.UnLoadMap();
			initialInterface_.Reset();
			flag = true;
			bgm_->Stop(SOUND_STOP_IMMEDIATE);

			swapChain_.GetDrawTool()->Clear();
			Rect_F r = { 350, 300, 500, 400 };
			Color_F c = { 1.0f, 1.0f, 1.0f, 1.0f };
			swapChain_.GetDrawTool()->DrawString( 
				L"胜败乃兵家常事，请重新再来",
				r,
				c
				);
			swapChain_.Flip();
			swapChain_.BeginDraw();
			swapChain_.GetDrawTool()->Clear();
			Sleep(1000);
		}
	}
	else
		initialInterface_.Draw( swapChain_.GetDrawTool() );

	InputSystem::GetInputSystem()->Run();
	IntersectionSystem::GetIntersectionSystem()->Run();
	SoundSystem::GetSoundSystem()->Run();
	AnimationSystem::GetAnimationSystem()->Run();
	TimeSystem::GetTimeSystem()->Run();

	swapChain_.Flip();
}

void TankFight::ShutDown()
{
	map_.ShutDown();
	swapChain_.ShutDown();
	InputSystem::GetInputSystem()->ShutDown();
	TimeSystem::GetTimeSystem()->Shutdown();
	IntersectionSystem::GetIntersectionSystem()->ShutDown();
	SoundSystem::GetSoundSystem()->ShutDown();
	AnimationSystem::GetAnimationSystem()->ShutDown();
}

void TankFight::Run()
{
	if( GetAsyncKeyState( VK_ESCAPE ) )
	{
		PostQuitMessage(0);
	}

	Render();
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow )
{
	UNREFERENCED_PARAMETER( prevInstance );
    UNREFERENCED_PARAMETER( cmdLine );

	TankFight application;

	bool result = application.Init( hInstance, 800, 640, false, WndProcess );

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
			application.Run();
		}
    }

	application.ShutDown();

	return static_cast<int>( msg.wParam );
}