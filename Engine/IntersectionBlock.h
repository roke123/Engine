#ifndef __INTERSECTIONBLOCK_H__
#define __INTERSECTIONBLOCK_H__

#include "BoundingEntity.h"
#include "BoundingRectangle.h"
#include "BoundingSphere.h"
#include "PtrList.h"

class IntersectionSystem;

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
	void AddMovableBoundingEntity( BoundingEntity * entity )
	{
		entity->AddRef();
		(*movableList_).push_back(entity);
	}

	//�Ѳ����ƶ��İ�Χʵ�������ײ�ֿ���
	void AddUnmovableBoundingEntity( BoundingEntity * entity )
	{
		entity->AddRef();
		(*unmovableList_).push_back( entity  );
	}

private:
	//���ƶ�entity������
	static PtrList< BoundingEntity > movableList_;

	//�����ƶ�entity������
	PtrList< BoundingEntity > unmovableList_;
};

typedef list<BoundingEntity *> BoundingEntityList;

#endif	//end of  IntersectionBlock.h