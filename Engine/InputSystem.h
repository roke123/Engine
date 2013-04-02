#ifndef __INPUTSYSTEM_H__
#define __INPUTSYSTEM_H__

#include <dinput.h>

enum KEYBOARDSTATE
{
	KB_KEYDOWN = 0,
	KB_KEYUP = 1,
	KB_KEYPRESS = 2,
	KB_KEYRELEASE = 3
};

class InputSystem
{
public:
	//构造函数
	InputSystem();

	//析构函数
	~InputSystem();

	//初始化函数
	bool Init( HINSTANCE hInstance, HWND hWnd );

	//运行函数
	void Run();

	//卸载函数
	void ShutDown();

	//查询键盘输入函数，最后两个惨数为组合键列表和组合键数量，可选
	bool QueryKeyboard( DWORD visualKey, int State,
		DWORD * combine = NULL, int combineNum = 0 );

private:
	//测试visualKey是否被按下
	bool KeyDown( DWORD visualKey );

	//测试visualKey是否被放开（指按下后放开的一瞬间）
	bool KeyUp( DWORD visualKey );

	//测试visualKey是否被按住
	bool KeyPress( DWORD visualKey );

	//测试visualKey是否被释放（一直没有被按下）
	bool KeyRelease( DWORD visualKey );

private:
	LPDIRECTINPUT8 directInput_;
	LPDIRECTINPUTDEVICE8 keyboardDevice_;

	char keyboardKeys_[256];
	char prevKeyboardKeys_[256];
};

#endif	//end og InputSystem.h