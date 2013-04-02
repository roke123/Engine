#include "PathAnimation.h"

PathAnimation::PathAnimation( Animation * animation, Vertex2D_F * path, int pathNum )
	: Animation( *animation )
{
	memcpy( pathSet_, path, sizeof( Vertex2D_F ) * pathNum );
	pathNum_ = pathNum;
	curPoint_ = 0.0f;
	pointStep_ = (float)pathNum_ / frameNum_;
}

bool PathAnimation::Draw()
{
	rect_.x0 += pathSet_[ (int)curPoint_ ].x;
	rect_.x1 += pathSet_[ (int)curPoint_ ].x;
	rect_.y0 += pathSet_[ (int)curPoint_ ].y;
	rect_.y1 += pathSet_[ (int)curPoint_ ].y;

	SetAnimationRect( rect_ );

	bool result = Animation::Draw();

	curPoint_ += pointStep_;

	return result;
}