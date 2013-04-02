#ifndef __ANIMATIONGROUP_H__
#define __ANIMATIONGROUP_H__

#include "Image.h"
#include "Animation.h"
#include "RefObject.h"

#include <map>
#include <string>
using namespace std;

enum ANIMATIONRUNFLAG
{
	ANIMATION_RUN_ONCE = 1,
	ANIMATION_RUN_LOOP = -1
};

class Animation;
class DrawTool;

class AnimationGroup : public RefObject
{
	friend class Animation;
	friend class D2DDrawTool;
public:
	AnimationGroup();
	~AnimationGroup();

	bool Run( );

	void SetAnimationRect( const Rect_F& rect );

	void SetAnimation( const string& animationName, int time );

	//释放AnimationGroup资源
	void Release();

private:
	void SetAnimation( const string animationName, Animation * animation );

private:
	DrawTool * drawTool_;

	//关键帧序列
	ImageType ** frameGroup_;

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

#endif	//end of AnimationGroup.h