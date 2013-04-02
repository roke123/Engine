#ifndef __SCALEANIMATION_H__
#define __SCALEANIMATION_H__

#include "Animation.h"

class Animation;

class ScaleAnimation : public Animation
{
public:
	//创建一个向着scale_x,scale_y进行变化的动画
	ScaleAnimation( Animation * animation, float scale_x, float scale_y );

private:
	//override
	bool Draw();

private:
	Animation * animation_;

	Rect_F rect;

	//当前放大倍数
	float scale_x_, scale_y_;

	//最终放大倍数
	float scale_x_step_, scale_y_step_;
};

#endif	//end of ScaleAnimation.h