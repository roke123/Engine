#ifndef __PATHANIMATION_H__
#define __PATHANIMATION_H__

#include "Animation.h"

class Animation;

class PathAnimation : public Animation
{
public:
	//创建一个按路径移动的动画
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

	//路径点集
	Vertex2D_F * pathSet_;

	//路径点数量
	int pathNum_;

	

	//当前路径点
	float curPoint_;

	//路径点数量/动画帧数
	float pointStep_;
};	//end of class PathAnimation

#endif	//end of PathAnimation.h