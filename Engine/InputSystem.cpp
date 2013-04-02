#include "InputSystem.h"

InputSystem::InputSystem() : directInput_(0), keyboardDevice_(0)
{
	//留空
}

InputSystem::~InputSystem()
{
	ShutDown();
}

bool InputSystem::Init( HINSTANCE hInstance, HWND hWnd )
{
	HRESULT result = 0;

	result = DirectInput8Create( hInstance, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (LPVOID *)&directInput_, NULL );

	if( FAILED( result ) )
	{
		MessageBox( 0, "Can't create a direct input", 0, 0 );
		return false;
	}

	result = directInput_->CreateDevice( GUID_SysKeyboard, &keyboardDevice_, NULL );

	if( FAILED( result ) )
	{
		MessageBox( 0, "Can't create a direct input device", 0, 0 );
		return false;
	}

	result = keyboardDevice_->SetDataFormat( &c_dfDIKeyboard );

	if( FAILED( result ) )
	{
		MessageBox( 0, "Set a wrong data format", 0, 0 );
		return false;
	}

	result = keyboardDevice_->SetCooperativeLevel( hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE );

	if( FAILED( result ) )
	{
		MessageBox( 0, "Set a wrong cooperative level", 0, 0 );
		return false;
	}

	result = keyboardDevice_->Acquire();

	if( FAILED( result ) )
	{
		MessageBox( 0, "Keyboard is losting", 0, 0 );
		return false;
	}	

	ZeroMemory( keyboardKeys_, sizeof( keyboardKeys_ ) );
	ZeroMemory( prevKeyboardKeys_, sizeof( prevKeyboardKeys_ ) );	

	return true;
}

void InputSystem::Run()
{
	HRESULT result = 0;

	memcpy( prevKeyboardKeys_, keyboardKeys_, sizeof( keyboardKeys_ ) );
	result = keyboardDevice_->GetDeviceState( sizeof( keyboardKeys_ ),
		keyboardKeys_ );

	while( result == DIERR_INPUTLOST )
	{
		result = keyboardDevice_->Acquire();
		if( FAILED( result ) )
			break;
	}

	if( FAILED( result ) )
	{
		MessageBox( 0, "input device goes wrong", 0, 0 );
		return;
	}
}

void InputSystem::ShutDown()
{
	if( directInput_ != 0 ) directInput_->Release();
	if( keyboardDevice_ != 0 ) keyboardDevice_->Release();

	directInput_ = 0;
	keyboardDevice_ = 0;
}

bool InputSystem::QueryKeyboard( DWORD visualKey, int State,
		DWORD * combine, int combineNum )
{
	bool result = false;
	int i = 0;	//循环数

	switch ( State )
	{
	case KB_KEYDOWN:
		result = KeyDown( visualKey );

		//组合键数大于0并且visualKey已被按下
		if( combineNum != 0 && result )
		{
			for( i = 0; i < combineNum; ++ i )
			{
				result = KeyDown( combine[i] );
				if( !result )
					break;
			}
		}

		break;

	case KB_KEYUP:
		result = KeyUp( visualKey );

		//组合键数大于0并且visualKey已被放开
		if( combineNum != 0 && result )
		{
			for( i = 0; i < combineNum; ++ i )
			{
				result = KeyUp( combine[i] );
				if( !result )
					break;
			}
		}

		break;

	case KB_KEYPRESS:
		result = KeyPress( visualKey );

		//组合键数大于0并且visualKey已被按住
		if( combineNum != 0 && result )
		{
			for( i = 0; i < combineNum; ++ i )
			{
				result = KeyPress( combine[i] );
				if( !result )
					break;
			}
		}

		break;

	case KB_KEYRELEASE:
		result = KeyRelease( visualKey );

		//组合键数大于0并且visualKey已被释放
		if( combineNum != 0 && result )
		{
			for( i = 0; i < combineNum; ++ i )
			{
				result = KeyRelease( combine[i] );
				if( !result )
					break;
			}
		}

		break;

	default:
		break;
	}

	return result;
}

bool InputSystem::KeyDown( DWORD visualKey )
{
	return  !( prevKeyboardKeys_[ visualKey ] & 0x80 ) &&
		( keyboardKeys_[ visualKey ] & 0x80 );
}

bool InputSystem::KeyUp( DWORD visualKey )
{
	return  ( prevKeyboardKeys_[ visualKey ] & 0x80 ) &&
		!( keyboardKeys_[ visualKey ] & 0x80 );
}

bool InputSystem::KeyPress( DWORD visualKey )
{
	return  ( prevKeyboardKeys_[ visualKey ] & 0x80 ) &&
		( keyboardKeys_[ visualKey ] & 0x80 );
}

bool InputSystem::KeyRelease( DWORD visualKey )
{
	return  !( prevKeyboardKeys_[ visualKey ] & 0x80 ) &&
		!( keyboardKeys_[ visualKey ] & 0x80 );
}