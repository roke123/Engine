#ifndef __ALPHAANIMATION_H__
#define __ALPHAANIMATION_H__

class Animation;

#include "Animation.h"

class AlphaAnimation : public Animation
{
public:
	//创建一个透明度变化的动画
	AlphaAnimation( Animation * animation, float startAlpha, float alphaStep );

private:

	//override
	bool Draw();
	//初始透明度，最大为1.0f，最小为0.0f
	float curalpha_;

	//透明度步幅
	float alphaStep_;

};	// end of class AlphaAnimation

#endif	// end of AlphaAnimation.h