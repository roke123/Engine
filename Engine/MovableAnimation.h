#ifndef __MOVABLEANIMATION_H__
#define __MOVABLEANIMATION_H__

#include "Animation.h"
#include "GraphType.h"

class Animation;

class MovableAnimation : public Animation
{
public:
	//����һ�����򶨲����ƶ��Ķ���
	MovableAnimation( Animation * animation, float vx, float vy, float step );

private:
	//override
	bool Draw();

private:
	Animation * animation_;

	Rect_F rect_;

	//�ƶ�����
	float step_x_, step_y_;
};	//end of class MovableAnimation

#endif	//end of MovableAnimation.h