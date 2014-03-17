#ifndef __MOVABLEANIMATION_H__
#define __MOVABLEANIMATION_H__

#include "Animation.h"
#include "GraphType.h"

class MovableAnimation : public Animation
{
public:
	//创建一个定向定步幅移动的动画
	MovableAnimation( Animation * animation, float vx, float vy, float step );

private:
	//override
	bool Draw( DrawTool * pDrawTool );

	//重置该动画
	void Reset();

private:
	Animation * animation_;

	//初始动画位置
	Rect_F StartRect_;

	//当前动画位置
	Rect_F CurRect_;

	//移动方向
	float step_x_, step_y_;

	//是否第一帧标志
	bool bFirstFlag;
};	//end of class MovableAnimation

#endif	//end of MovableAnimation.h