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
	//��������������
	AnimationSystem();
	~AnimationSystem();

	//��ʼ������
	bool Init( DrawTool * drawTool_ );

	//ж�غ���
	void ShutDown();

	//����ʱ���������ڲ��Ŷ���
	void Run();

	//����һ��������
	bool CreateAnimationGroupWithFile( const wstring& filename,
		const Rect_F& rc, AnimationGroupPtr * group );

	static AnimationSystem * GetAnimationSystem()
	{
		static AnimationSystem animationSystem;

		return &animationSystem;
	}

private:
	//��Ӷ����鵽�����б�
	void AddAnimationList( AnimationGroupPtr animationGroup );

private:
	//���Ŷ������б�
	list< AnimationGroupPtr > animationGroupList;

	//��ͼ����
	DrawTool * drawTool_;
};

#endif	// end of AnimationSystem.h