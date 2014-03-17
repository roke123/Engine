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
	void AddMovableBoundingEntity( BoundingControllerPtr entity )
	{
		movableList_.push_back( entity );
	}

	//把不可移动的包围实体加入碰撞分块中
	void AddUnmovableBoundingEntity( BoundingControllerPtr entity )
	{
		unmovableList_.push_back( entity );
	}

private:
	//可移动entity的链表
	static BoundingList movableList_;

	//不可移动entity的链表
	BoundingList unmovableList_;
};

#endif	//end of  IntersectionBlock.h