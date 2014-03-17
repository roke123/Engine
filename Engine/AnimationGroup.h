#ifndef __ANIMATIONGROUP_H__
#define __ANIMATIONGROUP_H__

#include "Image.h"
#include "DrawTool.h"

#include <map>
#include <string>
#include <memory>
using namespace std;

enum ANIMATIONSTATEFLAG
{
	ANIMATION_STATE_STOPPED = 0,
	ANIMATION_STATE_PLAYING = 1,
	ANIMATION_STATE_PAUSED = 2,
	ANIMATION_STATE_INITIAL = 3,
};

enum ANIMATIONSTOPFLAG
{
	ANIMATION_STOP_RELEASE = 0,
	ANIMATION_STOP_IMMEDIATE = 1,
};

class AnimationGroup
{
	friend class AnimationSystem;
	friend class Animation;
public:
	AnimationGroup();
	~AnimationGroup();

	void SetAnimationRect( const Rect_F& rect );

	//播放动画
	int Play( const string strAnimationName, int nLoopCount = 1 );

	//bFlag为true暂停播放，为false恢复
	int Pause( bool bFlag );

	//ANIMATION_STOP_RELEASE为播放完成当前一个循环后停止
	//ANIMATION_STOP_IMMEDIATE为立刻停止声音
	int Stop( int nFlag = ANIMATION_STOP_IMMEDIATE );

public:
	//添加动画到动画组
	void SetAnimation( const string animationName, Animation * animation );

	//播放动画
	void Run( DrawTool * pDrawTool );

private:
	AnimationSystem * pAnimationSystem_;

	//循环播放次数
	int nLoopCount_;

	//动画组状态
	int animationState_;

	//关键帧序列
	ImageType ** frameGroup_;

	//动画组
	map< string, Animation * > animationSet_;

	//表示动画组所在位置和长宽
	Rect_F rect_;

	//动画组所使用的透明度
	float alpha_;

	//当前正在播放的动画指针
	Animation * curAnimation_;

	//当前动画运行次数
	int curtime_;
};

typedef shared_ptr<AnimationGroup> AnimationGroupPtr;

#endif	//end of AnimationGroup.h