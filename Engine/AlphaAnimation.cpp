#include "AlphaAnimation.h"

AlphaAnimation::AlphaAnimation( Animation * animation, float startAlpha, float alphaStep )
	: Animation( *animation ), curalpha_( startAlpha )
{
	alphaStep_ = alphaStep;
}

bool AlphaAnimation::Draw()
{
	SetAnimationAlpha( curalpha_ );

	bool result = Animation::Draw();

	curalpha_ += alphaStep_;

	if( curalpha_ < 0.0f )
		curalpha_ = 0.0f;

	if( curalpha_ > 1.0f )
		curalpha_ = 1.0f;

	return result;
}