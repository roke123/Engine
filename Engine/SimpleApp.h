#ifndef __SIMPLEAPP_H__
#define __SIMPLEAPP_H__

#include "WMain.h"

typedef LRESULT ( CALLBACK * WndProc )( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

class SimpleApp
{
public:
	SimpleApp( ) {};

	~SimpleApp( )
	{
		ShutDown();
	}

	//初始化应用
	virtual bool Init( HINSTANCE hInstance, int width, int height,
		bool isWindow, WndProc process  );

	//运行应用
	virtual void Run( ) = 0;

	//卸载应用
	virtual void ShutDown( ) { };

protected:
	//加载初始资源
	virtual bool LoadContent( ) { return true; }
	virtual void UnloadContent( ) { };

private:
	//防止复制应用
	SimpleApp( const SimpleApp& t ) { };
	
protected:
	HINSTANCE hInstance_;
	HWND hWnd_;
	int width_, height_;
	bool isWindow_; 
};

#endif	// end of SimpleApp.h