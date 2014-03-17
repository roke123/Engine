#ifndef __ALPHAANIMATION_H__
#define __ALPHAANIMATION_H__

#include "Animation.h"

class AlphaAnimation : public Animation
{
public:
	//����һ��͸���ȱ仯�Ķ���
	AlphaAnimation( Animation * animation, float startAlpha, float alphaStep );

private:
	//override
	bool Draw( DrawTool * pDrawTool );

	//���øö���
	void Reset();

	//��ʼ͸���ȣ����Ϊ1.0f����СΪ0.0f
	float fStartAlpha_;

	//��ǰ͸����
	float fCurAlpha_;

	//͸���Ȳ���
	float alphaStep_;

};	// end of class AlphaAnimation

#endif	// end of AlphaAnimation.h