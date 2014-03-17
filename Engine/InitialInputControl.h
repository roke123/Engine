#ifndef __INITIALINPUTCONTROL_H__
#define __INITIALINPUTCONTROL_H__

#include <InputSystem.h>
#include <Default.h>

#include "InitialInterface.h"

class InitialInputControl : public InputController
{
	REGISTER_TARGET( InitialInterface );

public:
	InitialInputControl() : InputController()
	{
		//Áô¿Õ
	}

	void InputHandler( InputSystem * inputSystem )
	{
		int x = inputSystem->GetMousePositionX();
		int y = inputSystem->GetMousePositionY();

		if( x > target_->startGameBox_.x0 && x < target_->startGameBox_.x1 )
			if( y > target_->startGameBox_.y0 && x < target_->startGameBox_.y1 )
			{
				target_->iReadyChoose_ = CK_STARTGAME;
				
				if( inputSystem->QueryMouseKey( MK_LEFTBUTTON, MK_KEYDOWN ) )
					target_->iChoose_ = CK_STARTGAME;
			}

		if( x > target_->optionBox_.x0 && x < target_->optionBox_.x1 )
			if( y > target_->optionBox_.y0 && x < target_->optionBox_.y1 )
			{
				target_->iReadyChoose_ = CK_OPTION;;
				
				if( inputSystem->QueryMouseKey( MK_LEFTBUTTON, MK_KEYDOWN ) )
					target_->iChoose_ = CK_OPTION;;
			}

		if( x > target_->endGameBox_.x0 && x < target_->endGameBox_.x1 )
			if( y > target_->endGameBox_.y0 && x < target_->endGameBox_.y1 )
			{
				target_->iReadyChoose_ = CK_ENDGAME;
				
				if( inputSystem->QueryMouseKey( MK_LEFTBUTTON, MK_KEYDOWN ) )
					target_->iChoose_ = CK_ENDGAME;
			}
	}
};

#endif	// end of InitialInputControl