#ifndef __MOVABLEANIMATION_H__
#define __MOVABLEANIMATION_H__

#include "Animation.h"
#include "GraphType.h"

class Animation;

class MovableAnimation : public Animation
{
public:
	//创建一个定向定步幅移动的动画
	MovableAnimation( Animation * animation, float vx, float vy, float step );

private:
	//override
	bool Draw();

private:
	Animation * animation_;

	Rect_F rect_;

	//移动方向
	float step_x_, step_y_;
};	//end of class MovableAnimation

#endif	//end of MovableAnimation.h