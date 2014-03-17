#ifndef BULLETTIMECONTROL_H__
#define BULLETTIMECONTROL_H__

#include <TimeSystem.h>
#include <Default.h>

#include "Bullet.h"

class BulletTimeControl : public TimeController
{
	REGISTER_TARGET( Bullet );

public:
	BulletTimeControl() : TimeController()
	{
		moveX_ = 0.0f, moveY_ = 0.0f;
	}

	void TimeHandler( long delta )
	{	
		moveX_ += target_->speedX_;
		moveY_ += target_->speedY_;

		Matrix3x3_F worldMatrix = CreateTransformMatrix3x3( moveX_, moveY_ );
		SetMatrix( target_->rect_, worldMatrix );
	}

public:
	float moveX_, moveY_;
	
};

#endif	// end of BulletTimeController.h