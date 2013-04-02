#ifndef __BOUNDINGENTITY_H__
#define __BOUNDINGENTITY_H__

#include "GraphType.h"
#include "RefObject.h"

enum BOUNDINGTYPE
{
	BOUNDINGSPHERE = 0,
	BOUNDINGRECTANGLE = 1
};

enum UPDATESTATE
{
	NOUPDATE = 0,
	UPDATEED = 1
};

class IntersectionSystem;

class BoundingEntity : public RefObject
{
	//友元类
	friend class IntersectionSystem; 

public:
	BoundingEntity() : RefObject(), graph_(0), updateState_(NOUPDATE)
	{

	}

	~BoundingEntity()
	{

	}

	void Update()
	{
		if( graph_->GetGraphType() == RECTANGLETYPE )
			UpdateWithRectangle();
		else 
			UpdateWithPolygon();

		updateState_ = UPDATEED;
	}

private:
	//使用rectangle更新
	virtual void UpdateWithRectangle() = 0;

	//使用sphere更新
	virtual void UpdateWithPolygon() = 0;

protected:
	int updateState_;
	const GraphType * graph_;
	int type_;
};

#endif	//end of BoundingEntity.h