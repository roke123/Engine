#include "AlphaAnimation.h"

AlphaAnimation::AlphaAnimation( Animation * animation, float startAlpha, float alphaStep )
	: Animation( *animation ), fStartAlpha_( startAlpha ), fCurAlpha_( startAlpha )
{
	alphaStep_ = alphaStep;
}

void AlphaAnimation::Reset()
{
	fCurAlpha_ = fStartAlpha_;
}

bool AlphaAnimation::Draw( DrawTool * pDrawTool )
{
	SetAnimationAlpha( fCurAlpha_ );

	bool result = Animation::Draw( pDrawTool );

	fCurAlpha_ += alphaStep_;

	if( fCurAlpha_ < 0.0f )
		fCurAlpha_ = 0.0f;

	if( fCurAlpha_ > 1.0f )
		fCurAlpha_ = 1.0f;

	return result;
}