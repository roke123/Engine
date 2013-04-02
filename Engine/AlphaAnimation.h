#ifndef __ALPHAANIMATION_H__
#define __ALPHAANIMATION_H__

class Animation;

#include "Animation.h"

class AlphaAnimation : public Animation
{
public:
	//����һ��͸���ȱ仯�Ķ���
	AlphaAnimation( Animation * animation, float startAlpha, float alphaStep );

private:

	//override
	bool Draw();
	//��ʼ͸���ȣ����Ϊ1.0f����СΪ0.0f
	float curalpha_;

	//͸���Ȳ���
	float alphaStep_;

};	// end of class AlphaAnimation

#endif	// end of AlphaAnimation.h