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

	//���Ŷ���
	int Play( const string strAnimationName, int nLoopCount = 1 );

	//bFlagΪtrue��ͣ���ţ�Ϊfalse�ָ�
	int Pause( bool bFlag );

	//ANIMATION_STOP_RELEASEΪ������ɵ�ǰһ��ѭ����ֹͣ
	//ANIMATION_STOP_IMMEDIATEΪ����ֹͣ����
	int Stop( int nFlag = ANIMATION_STOP_IMMEDIATE );

public:
	//��Ӷ�����������
	void SetAnimation( const string animationName, Animation * animation );

	//���Ŷ���
	void Run( DrawTool * pDrawTool );

private:
	AnimationSystem * pAnimationSystem_;

	//ѭ�����Ŵ���
	int nLoopCount_;

	//������״̬
	int animationState_;

	//�ؼ�֡����
	ImageType ** frameGroup_;

	//������
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

typedef shared_ptr<AnimationGroup> AnimationGroupPtr;

#endif	//end of AnimationGroup.h