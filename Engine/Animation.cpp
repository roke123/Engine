#include "Animation.h"
#include "DrawTool.h"
#include <assert.h>

Animation::Animation( int * indexGroup, int frameNum ) : group_(0),
	state_( ANIMATIONDEAD )
{
	assert( frameNum > 0 );
	assert( indexGroup != 0 );

	frameNum_ = frameNum;

	frameIndex_ = new int[ frameNum ];

	memcpy( frameIndex_, indexGroup, sizeof(int) * frameNum );

	state_ = ANIMATIONRUN;
	curIndex_ = 0;
}

Animation::~Animation()
{
	delete [] frameIndex_;
}

bool Animation::Draw( )
{
	if( state_ == ANIMATIONDEAD )
		return false;

	ImageType ** imageSet = group_->frameGroup_;
	int index = frameIndex_[curIndex_];
	group_->drawTool_->DrawImage( *imageSet[index], group_->rect_,
		group_->alpha_ );

	++ curIndex_;
	if( curIndex_ >= frameNum_ )
	{
		state_ = ANIMATIONDEAD;
		return true;
	}

	return false;
}

void Animation::SetAnimationRect( const Rect_F& rc ) 
{ 
	group_->rect_ = rc;
}

Rect_F Animation::GetAnimationRect( ) 
{ 
	return group_->rect_;
}

void Animation::SetAnimationAlpha( float alpha ) 
{ 
	group_->alpha_ = alpha;
}

float Animation::GetAnimationAlpha() 
{ 
	return group_->alpha_;
}