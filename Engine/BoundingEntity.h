#ifndef __BOUNDINGENTITY_H__
#define __BOUNDINGENTITY_H__

#include "GraphType.h"

enum BOUNDINGTYPE
{
	BOUNDINGSPHERE = 0,
	BOUNDINGRECTANGLE = 1
};

class IntersectionSystem;

class BoundingEntity
{
	//友元类
	friend class IntersectionSystem; 

protected:
	BoundingEntity()
	{
		// 留空
	}

	void Update()
	{
		if( graph_->GetGraphType() == RECTANGLETYPE )
			UpdateWithRectangle();
		else 
			UpdateWithPolygon();
	}

protected:
	//使用rectangle更新
	virtual void UpdateWithRectangle() = 0;

	//使用sphere更新
	virtual void UpdateWithPolygon() = 0;

protected:
	const Graph * graph_;

	int type_;
};

#endif	//end of BoundingEntity.h