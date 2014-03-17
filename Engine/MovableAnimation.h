#ifndef __MOVABLEANIMATION_H__
#define __MOVABLEANIMATION_H__

#include "Animation.h"
#include "GraphType.h"

class MovableAnimation : public Animation
{
public:
	//����һ�����򶨲����ƶ��Ķ���
	MovableAnimation( Animation * animation, float vx, float vy, float step );

private:
	//override
	bool Draw( DrawTool * pDrawTool );

	//���øö���
	void Reset();

private:
	Animation * animation_;

	//��ʼ����λ��
	Rect_F StartRect_;

	//��ǰ����λ��
	Rect_F CurRect_;

	//�ƶ�����
	float step_x_, step_y_;

	//�Ƿ��һ֡��־
	bool bFirstFlag;
};	//end of class MovableAnimation

#endif	//end of MovableAnimation.h