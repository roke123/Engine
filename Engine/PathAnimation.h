#ifndef __PATHANIMATION_H__
#define __PATHANIMATION_H__

#include "Animation.h"

class Animation;

class PathAnimation : public Animation
{
public:
	//����һ����·���ƶ��Ķ���
	PathAnimation( Animation * animation, Vertex2D_F * path, int pathNum );

	~PathAnimation()
	{
		delete [] pathSet_;
	}

private:
	//override
	bool Draw();

private:
	Animation * animation_;

	//·���㼯
	Vertex2D_F * pathSet_;

	//·��������
	int pathNum_;

	

	//��ǰ·����
	float curPoint_;

	//·��������/����֡��
	float pointStep_;
};	//end of class PathAnimation

#endif	//end of PathAnimation.h