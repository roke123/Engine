#include "AnimationGroup.h"
#include "GlobalFunction.h"
#include "GraphType.h"
#include "Animation.h"
#include "AnimationSystem.h"

AnimationGroup::AnimationGroup() : frameGroup_( 0 ),
	curtime_( -1 ), alpha_( 1.0f )
{
	animationState_ = ANIMATION_STATE_INITIAL;
	nLoopCount_ = 0;
}

AnimationGroup::~AnimationGroup()
{
	typedef map< string, Animation * >::iterator ite;

	ite cur = animationSet_.begin();
	for( ; cur != animationSet_.end(); ++ cur )
	{
		delete cur->second;
	}

	delete [] frameGroup_;
}

void AnimationGroup::SetAnimation( const string animationName, Animation * animation )
{
	animation->group_ = this;
	animation->rect_ = rect_;
	animationSet_.insert( make_pair( animationName, animation ) );
}

void AnimationGroup::SetAnimationRect( const Rect_F& rect )
{
	rect_ = rect;
}

void AnimationGroup::Run( DrawTool * pDrawTool )
{
	if( curAnimation_->Draw( pDrawTool ) )
	{
		animationState_ = ANIMATION_STATE_STOPPED;
		curAnimation_->Reset();
	} 
	else
	{
		animationState_ = ANIMATION_STATE_PLAYING;
	}
}

int AnimationGroup::Play( const string strAnimationName, int nLoopCount )
{
	if( animationState_ == ANIMATION_STATE_STOPPED
		|| animationState_ == ANIMATION_STATE_INITIAL )
	{
		curAnimation_ = animationSet_.find( strAnimationName )->second;
		nLoopCount_ = nLoopCount;
		pAnimationSystem_->AddAnimationList( AnimationGroupPtr( this ) );
	}

	return animationState_;
}

int AnimationGroup::Pause( bool bFlag )
{
	if( animationState_ == ANIMATION_STATE_PLAYING && bFlag )
		animationState_ = ANIMATION_STATE_PAUSED;
	else if(  animationState_ == ANIMATION_STATE_PAUSED && !bFlag )
		animationState_ = ANIMATION_STATE_PLAYING;

	return animationState_;
}

int AnimationGroup::Stop( int nFlag )
{
	if( nFlag == ANIMATION_STOP_IMMEDIATE )
	{
		nLoopCount_ = 0;
		nFlag = ANIMATION_STATE_STOPPED;
	}
	else
	{
		//设置为最后一次循环
		nLoopCount_ = 1;
	}

	return animationState_;
}