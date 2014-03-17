#ifndef __INPUTSYSTEM_H__
#define __INPUTSYSTEM_H__

#include <dinput.h>
#include <memory>
using namespace std::tr1;

#include "InputControllerManager.h"
#include "InputController.h"

enum KEYBOARDSTATE
{
	KB_KEYDOWN = 0,
	KB_KEYUP = 1,
	KB_KEYPRESS = 2,
	KB_KEYRELEASE = 3
};

enum MOUSEKEYSTATE
{
	MK_KEYDOWN = 0,
	MK_KEYUP = 1,
	MK_KEYPRESS = 2,
	MK_KEYRELEASE = 3
};

enum MOUSEKEY
{
	MK_LEFTBUTTON = 0,
	MK_RIGHTBUTTON = 1,
	MK_MIDDLEBUTTON = 2,
};

class InputControllerManager;
class InputController;

class InputSystem;
typedef shared_ptr<InputSystem> InputSystemPtr;

class InputSystem
{
public:
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

	int GetMousePositionX()
	{
		return mousePos_.x;
	}

	int GetMousePositionY()
	{
		return mousePos_.y;
	}

	bool QueryMouseKey( MOUSEKEY mouseKey, MOUSEKEYSTATE keyState )
	{
		int result = (mouseState_.rgbButtons[ mouseKey ] & 0x80);
		int prevResult = (prevMouseState_.rgbButtons[ mouseKey ] & 0x80);

		switch( keyState )
		{
		case MK_KEYDOWN :
			return !prevResult && result;

		case MK_KEYPRESS :
			return prevResult && result;

		case MK_KEYUP :
			return prevResult && !result;

		case MK_KEYRELEASE :
			return !prevResult && !result;
		}

		return false;
	}

	void RegisterInputController( InputControllerPtr inputController )
	{
		inputManager_.RegisterController( inputController );
	}

	static InputSystemPtr GetInputSystem();

private:
	//构造函数
	InputSystem();

	//测试visualKey是否被按下
	bool KeyDown( DWORD visualKey );

	//测试visualKey是否被放开（指按下后放开的一瞬间）
	bool KeyUp( DWORD visualKey );

	//测试visualKey是否被按住
	bool KeyPress( DWORD visualKey );

	//测试visualKey是否被释放（一直没有被按下）
	bool KeyRelease( DWORD visualKey );

private:
	HWND hWnd_;

	LPDIRECTINPUT8 directInput_;
	LPDIRECTINPUTDEVICE8 keyboardDevice_;
	LPDIRECTINPUTDEVICE8 mouseDevice_;

	char keyboardKeys_[256];
	char prevKeyboardKeys_[256];

	DIMOUSESTATE mouseState_;
	DIMOUSESTATE prevMouseState_;
	POINT mousePos_;

	InputControllerManager inputManager_;
};

#endif	//end og InputSystem.h