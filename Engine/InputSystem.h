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
	//��������
	~InputSystem();

	//��ʼ������
	bool Init( HINSTANCE hInstance, HWND hWnd );

	//���к���
	void Run();

	//ж�غ���
	void ShutDown();

	//��ѯ�������뺯���������������Ϊ��ϼ��б����ϼ���������ѡ
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
	//���캯��
	InputSystem();

	//����visualKey�Ƿ񱻰���
	bool KeyDown( DWORD visualKey );

	//����visualKey�Ƿ񱻷ſ���ָ���º�ſ���һ˲�䣩
	bool KeyUp( DWORD visualKey );

	//����visualKey�Ƿ񱻰�ס
	bool KeyPress( DWORD visualKey );

	//����visualKey�Ƿ��ͷţ�һֱû�б����£�
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