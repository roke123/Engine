#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "GraphType.h"
#include "AnimationGroup.h"

class Animation
{
	friend class AnimationGroup;
public:
	//使用一个动画组指针与帧索引序列初始化动画
	Animation( int * indexGroup, int frameNum );

	//虚析构函数
	virtual ~Animation();

protected:
	//重置该动画
	virtual void Reset();

	//使用drawTool画一帧动画,播放完毕返回true，不然返回false
	virtual bool Draw( DrawTool * pDrawTool );

	//设置动画绘画的边框
	void SetAnimationRect( const Rect_F& rc );

	Rect_F GetAnimationRect( ) ;

	//设置动画透明度
	void SetAnimationAlpha( float alpha );

	float GetAnimationAlpha();

protected:
	//所属的动画组指针
	AnimationGroup * group_;

	//帧索引序列，-1为空索引，代表空帧
	int * frameIndex_;

	Rect_F rect_;

	//当前帧
	int curIndex_;

	//组成动画的帧数量
	int frameNum_;

	int state_;

};	//end of class Animation

#endif	//end of Animation.h