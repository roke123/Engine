#ifndef BULLETTIMECONTROL_H__
#define BULLETTIMECONTROL_H__

#include <TimeSystem.h>
#include <Default.h>
#include <ctime>
#include <boost\random.hpp>

#include "Enemy.h"

class EnemyTimeController : public TimeController
{
	REGISTER_TARGET( Enemy );

public:
	EnemyTimeController() : TimeController()
	{
		moveX_ = 0.0f, moveY_ = 0.0f;
		choose_ = 0;
	}

	void TimeHandler( long delta )
	{	
		if( target_->IsBounding_ )
		{
			moveX_ = lastMoveX_;
			moveY_ = lastMoveY_;
			*target_->rect_ = lastRect_;
			target_->IsBounding_ = false;
			
			switch( choose_ )
			{
			case 0: choose_ = 1; break;
			case 1: choose_ = 2; break;
			case 2: choose_ = 3; break;
			case 3: choose_ = 0; break;
			}
		}

		if( (int)Random() == 4 )
		{
			target_->Fire();
			choose_ = (int)Random() % 4;
		}

		lastMoveX_ = moveX_;
		lastMoveY_ = moveY_;
		lastRect_ = *target_->rect_;

		switch( choose_ )
		{
		case 0:
			moveY_ -= target_->speedY_;
			target_->direction_ = 0;
			target_->curImage_ = target_->imageSet_[0];
			break;
		case 1:
			moveX_ -= target_->speedX_;
			target_->direction_ = 1;
			target_->curImage_ = target_->imageSet_[1];
			break;

		case 2:
			moveY_ += target_->speedY_;
			target_->direction_ = 2;
			target_->curImage_ = target_->imageSet_[2];
			break;

		case 3:
			moveX_ += target_->speedX_;
			target_->direction_ = 3;
			target_->curImage_ = target_->imageSet_[3];
			break;
		}

		Matrix3x3_F transform = CreateTransformMatrix3x3( moveX_, moveY_ );

		SetMatrix( target_->rect_, transform );
	}

public:
	static boost::random::variate_generator<boost::mt19937, 
		boost::uniform_real<> > Random;

	int choose_;

	float moveX_, moveY_;

	float lastMoveX_, lastMoveY_;
	Rectangle2D lastRect_;
};

boost::random::variate_generator<boost::mt19937, 
	boost::uniform_real<> > EnemyTimeController::Random(
		boost::mt19937(), boost::uniform_real<>(0, 50) );

#endif	// end of BulletTimeController.h