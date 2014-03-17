#ifndef __INTERSECTIONBLOCK_H__
#define __INTERSECTIONBLOCK_H__

#include <list>
using namespace std;

#include "BoundingObject.h"
#include "BoundingRectangle.h"
#include "BoundingSphere.h"

class IntersectionSystem;

typedef list< BoundingControllerPtr > BoundingList;
typedef list< BoundingControllerPtr >::iterator BoundingListNode;

class IntersectionBlock
{
	//��Ԫ��
	friend class IntersectionSystem; 

public:
	IntersectionBlock()
	{
		//����
	}

	~IntersectionBlock()
	{
		//����
	}

	//�ѿ��ƶ��İ�Χʵ�������ײ�ֿ���
	void AddMovableBoundingEntity( BoundingControllerPtr entity )
	{
		movableList_.push_back( entity );
	}

	//�Ѳ����ƶ��İ�Χʵ�������ײ�ֿ���
	void AddUnmovableBoundingEntity( BoundingControllerPtr entity )
	{
		unmovableList_.push_back( entity );
	}

private:
	//���ƶ�entity������
	static BoundingList movableList_;

	//�����ƶ�entity������
	BoundingList unmovableList_;
};

#endif	//end of  IntersectionBlock.h