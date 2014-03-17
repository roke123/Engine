#ifndef __TANKINPUTCONTROL_H__
#define __TANKINPUTCONTROL_H__

#include <InputSystem.h>
#include <Default.h>
#include <GlobalFunction.h>

#include "Tank.h"

class TankInputControl : public InputController
{
	REGISTER_TARGET( Tank );
public:
	TankInputControl() : InputController()
	{
		moveX_ = 0.0f, moveY_ = 0.0f;
	}

	void InputHandler( InputSystem * inputSystem )
	{
		if( inputSystem->QueryKeyboard( DIK_F, KB_KEYDOWN ) )
		{		
			target_->Fire();
		}

		if( target_->IsBounding_ )
		{
			moveX_ = lastMoveX_;
			moveY_ = lastMoveY_;
			*target_->rect_ = lastRect_;
			target_->IsBounding_ = false;
			return;
		}

		lastMoveX_ = moveX_;
		lastMoveY_ = moveY_;
		lastRect_ = *target_->rect_;

		if( inputSystem->QueryKeyboard( DIK_UP, KB_KEYPRESS ) )
		{		
			moveY_ -= target_->speedY_;
			target_->direction_ = DIK_UP;
			target_->curImage_ = target_->imageSet_[0];
		}
		else if( inputSystem->QueryKeyboard( DIK_LEFT, KB_KEYPRESS ) )
		{
			moveX_ -= target_->speedX_;
			target_->direction_ = DIK_LEFT;
			target_->curImage_ = target_->imageSet_[1];
		}
		else if( inputSystem->QueryKeyboard( DIK_DOWN, KB_KEYPRESS ) )
		{
			moveY_ += target_->speedY_;
			target_->direction_ = DIK_DOWN;
			target_->curImage_ = target_->imageSet_[2];
		}
		else if( inputSystem->QueryKeyboard( DIK_RIGHT, KB_KEYPRESS ) )
		{
			moveX_ += target_->speedX_;
			target_->direction_ = DIK_RIGHT;
			target_->curImage_ = target_->imageSet_[3];
		}

		Matrix3x3_F transform = CreateTransformMatrix3x3( moveX_, moveY_ );

		SetMatrix( target_->rect_, transform );
	}

private:
	float moveX_, moveY_;

	float lastMoveX_, lastMoveY_;
	Rectangle2D lastRect_;
};

#endif	// end of TankInputControl