#ifndef __ANIMATIONSYSTEM_H__
#define __ANIMATIONSYSTEM_H__

#include "DrawTool.h"
#include "GlobalFunction.h"
#include "Animation.h"
#include "AnimationGroup.h"

#include <list>
using namespace std;

class AnimationSystem
{
	friend class AnimationGroup;
public:
	//构造与析构函数
	AnimationSystem();
	~AnimationSystem();

	//初始化函数
	bool Init( DrawTool * drawTool_ );

	//卸载函数
	void ShutDown();

	//运行时函数，用于播放动画
	void Run();

	//创建一个动画组
	bool CreateAnimationGroupWithFile( const wstring& filename,
		const Rect_F& rc, AnimationGroupPtr * group );

	static AnimationSystem * GetAnimationSystem()
	{
		static AnimationSystem animationSystem;

		return &animationSystem;
	}

private:
	//添加动画组到播放列表
	void AddAnimationList( AnimationGroupPtr animationGroup );

private:
	//播放动画的列表
	list< AnimationGroupPtr > animationGroupList;

	//绘图工具
	DrawTool * drawTool_;
};

#endif	// end of AnimationSystem.h