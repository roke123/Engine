#include "AnimationGroup.h"
#include "GlobalFunction.h"
#include "GraphType.h"
#include "Animation.h"

AnimationGroup::AnimationGroup() : RefObject(), drawTool_( 0 ), frameGroup_( 0 ),
	curtime_( -1 ), alpha_( 1.0f )
{

}

AnimationGroup::~AnimationGroup()
{
	Release();
}

void AnimationGroup::SetAnimation( const string animationName, Animation * animation )
{
	animation->group_ = this;
	animation->rect_ = rect_;
	animationSet_.insert( make_pair( animationName, animation ) );
}

void AnimationGroup::SetAnimation( const string& animationName, int time )
{
	curAnimation_ = animationSet_.find( animationName )->second;
	curtime_ = time;
}

void AnimationGroup::SetAnimationRect( const Rect_F& rect )
{
	rect_ = rect;
}

//ÊÍ·ÅAnimationGroup×ÊÔ´
void AnimationGroup::Release()
{
	typedef map< string, Animation * >::iterator ite;

	ite cur = animationSet_.begin();
	for( ; cur != animationSet_.end(); ++ cur )
	{
		delete cur->second;
	}

	delete [] frameGroup_;
}

bool AnimationGroup::Run()
{
	if( curtime_ > 0 )
	{
		if( curAnimation_->Draw() )
			-- curtime_;
		return false;
	}

	return true;
}