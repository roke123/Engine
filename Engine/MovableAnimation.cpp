#include "MovableAnimation.h"

MovableAnimation::MovableAnimation( Animation * animation, float vx, float vy, float step )
	: Animation( *animation )
{
	step_x_ = 1 / vx * step;
	step_y_ = 1 / vy * step;
	animation_ = animation;
}

bool MovableAnimation::Draw( )
{
	rect_.x0 += step_x_;  
	rect_.x1 += step_x_;
	rect_.y0 += step_y_;
	rect_.y1 += step_y_;

	SetAnimationRect( rect_ );

	return Animation::Draw();
}