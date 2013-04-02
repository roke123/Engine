#include "ScaleAnimation.h"

ScaleAnimation::ScaleAnimation( Animation * animation, float scale_x, float scale_y )
	: Animation( *animation )
{
	scale_x_step_ = scale_x / frameNum_;
	scale_y_step_ = scale_y / frameNum_;
	scale_x_ = 1.0f;
	scale_y_ = 1.0f;
}

bool ScaleAnimation::Draw()
{
	Rect_F temp;
	temp.x0 = rect_.x0 * scale_x_;
	temp.x1 = rect_.x1 * scale_x_;
	temp.y0 = rect_.y0 * scale_y_;
	temp.y1 = rect_.y1 * scale_y_;

	SetAnimationRect( temp );

	bool result = Animation::Draw();

	scale_x_ += scale_x_step_;
	scale_y_ += scale_y_step_;

	if( scale_x_ < 0.0f )
		scale_x_ = 0.0f;

	if( scale_y_ < 0.0f )
		scale_y_ = 0.0f;

	return result;
}