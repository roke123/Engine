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

	//��ʼ��Ӧ��
	virtual bool Init( HINSTANCE hInstance, int width, int height,
		bool isWindow, WndProc process  );

	//����Ӧ��
	virtual void Run( ) = 0;

	//ж��Ӧ��
	virtual void ShutDown( ) { };

protected:
	//���س�ʼ��Դ
	virtual bool LoadContent( ) { return true; }
	virtual void UnloadContent( ) { };

private:
	//��ֹ����Ӧ��
	SimpleApp( const SimpleApp& t ) { };
	
protected:
	HINSTANCE hInstance_;
	HWND hWnd_;
	int width_, height_;
	bool isWindow_; 
};

#endif	// end of SimpleApp.h