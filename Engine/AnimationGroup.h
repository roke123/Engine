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

	//�ͷ�AnimationGroup��Դ
	void Release();

private:
	void SetAnimation( const string animationName, Animation * animation );

private:
	DrawTool * drawTool_;

	//�ؼ�֡����
	ImageType ** frameGroup_;

	map< string, Animation * > animationSet_;

	//��ʾ����������λ�úͳ���
	Rect_F rect_;

	//��������ʹ�õ�͸����
	float alpha_;

	//��ǰ���ڲ��ŵĶ���ָ��
	Animation * curAnimation_;

	//��ǰ�������д���
	int curtime_;
};

#endif	//end of AnimationGroup.h