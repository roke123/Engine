#include "MovableAnimation.h"

MovableAnimation::MovableAnimation( Animation * animation, float vx, float vy, float step )
	: Animation( *animation )
{
	step_x_ = 1 / vx * step;
	step_y_ = 1 / vy * step;
	animation_ = animation;
	bFirstFlag = true;
}

void MovableAnimation::Reset()
{
	CurRect_ =  StartRect_;
	bFirstFlag = true;
}

bool MovableAnimation::Draw( DrawTool * pDrawTool )
{
	if( bFirstFlag )
	{
		CurRect_ = StartRect_ = GetAnimationRect();
		bFirstFlag = false;
	}

	CurRect_.x0 += step_x_;  
	CurRect_.x1 += step_x_;
	CurRect_.y0 += step_y_;
	CurRect_.y1 += step_y_;

	SetAnimationRect( rect_ );

	return Animation::Draw( pDrawTool );
}