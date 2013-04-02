#ifndef __INTERSECTIONBLOCK_H__
#define __INTERSECTIONBLOCK_H__

#include "BoundingEntity.h"
#include "BoundingRectangle.h"
#include "BoundingSphere.h"
#include "PtrList.h"

class IntersectionSystem;

class IntersectionBlock
{
	//友元类
	friend class IntersectionSystem; 

public:
	IntersectionBlock()
	{
		//留空
	}

	~IntersectionBlock()
	{
		//留空
	}

	//把可移动的包围实体加入碰撞分块中
	void AddMovableBoundingEntity( BoundingEntity * entity )
	{
		entity->AddRef();
		(*movableList_).push_back(entity);
	}

	//把不可移动的包围实体加入碰撞分块中
	void AddUnmovableBoundingEntity( BoundingEntity * entity )
	{
		entity->AddRef();
		(*unmovableList_).push_back( entity  );
	}

private:
	//可移动entity的链表
	static PtrList< BoundingEntity > movableList_;

	//不可移动entity的链表
	PtrList< BoundingEntity > unmovableList_;
};

typedef list<BoundingEntity *> BoundingEntityList;

#endif	//end of  IntersectionBlock.h