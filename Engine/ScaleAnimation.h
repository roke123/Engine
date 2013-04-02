#ifndef __SCALEANIMATION_H__
#define __SCALEANIMATION_H__

#include "Animation.h"

class Animation;

class ScaleAnimation : public Animation
{
public:
	//����һ������scale_x,scale_y���б仯�Ķ���
	ScaleAnimation( Animation * animation, float scale_x, float scale_y );

private:
	//override
	bool Draw();

private:
	Animation * animation_;

	Rect_F rect;

	//��ǰ�Ŵ���
	float scale_x_, scale_y_;

	//���շŴ���
	float scale_x_step_, scale_y_step_;
};

#endif	//end of ScaleAnimation.h