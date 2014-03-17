#include <assert.h>
#include "Animation.h"

Animation::Animation( int * indexGroup, int frameNum ) : group_(0)
{
	assert( frameNum > 0 );
	assert( indexGroup != 0 );

	frameNum_ = frameNum;

	frameIndex_ = new int[ frameNum ];

	memcpy( frameIndex_, indexGroup, sizeof(int) * frameNum );

	curIndex_ = 0;
}

void Animation::Reset()
{
	curIndex_ = 0;
}

Animation::~Animation()
{
	delete [] frameIndex_;
}

bool Animation::Draw( DrawTool * pDrawTool )
{
	ImageType ** imageSet = group_->frameGroup_;
	int index = frameIndex_[curIndex_];
	pDrawTool->DrawImage( *imageSet[index], group_->rect_,
		group_->alpha_ );

	++ curIndex_;
	if( curIndex_ >= frameNum_ )
		return true;

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