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
	//���캯��
	InputSystem();

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

private:
	//����visualKey�Ƿ񱻰���
	bool KeyDown( DWORD visualKey );

	//����visualKey�Ƿ񱻷ſ���ָ���º�ſ���һ˲�䣩
	bool KeyUp( DWORD visualKey );

	//����visualKey�Ƿ񱻰�ס
	bool KeyPress( DWORD visualKey );

	//����visualKey�Ƿ��ͷţ�һֱû�б����£�
	bool KeyRelease( DWORD visualKey );

private:
	LPDIRECTINPUT8 directInput_;
	LPDIRECTINPUTDEVICE8 keyboardDevice_;

	char keyboardKeys_[256];
	char prevKeyboardKeys_[256];
};

#endif	//end og InputSystem.h