#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "GraphType.h"
#include "AnimationGroup.h"

class Animation
{
	friend class AnimationGroup;
public:
	//ʹ��һ��������ָ����֡�������г�ʼ������
	Animation( int * indexGroup, int frameNum );

	//����������
	virtual ~Animation();

protected:
	//���øö���
	virtual void Reset();

	//ʹ��drawTool��һ֡����,������Ϸ���true����Ȼ����false
	virtual bool Draw( DrawTool * pDrawTool );

	//���ö����滭�ı߿�
	void SetAnimationRect( const Rect_F& rc );

	Rect_F GetAnimationRect( ) ;

	//���ö���͸����
	void SetAnimationAlpha( float alpha );

	float GetAnimationAlpha();

protected:
	//�����Ķ�����ָ��
	AnimationGroup * group_;

	//֡�������У�-1Ϊ�������������֡
	int * frameIndex_;

	Rect_F rect_;

	//��ǰ֡
	int curIndex_;

	//��ɶ�����֡����
	int frameNum_;

	int state_;

};	//end of class Animation

#endif	//end of Animation.h