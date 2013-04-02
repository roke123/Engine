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
	//��Ԫ��
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
	//ʹ��rectangle����
	virtual void UpdateWithRectangle() = 0;

	//ʹ��sphere����
	virtual void UpdateWithPolygon() = 0;

protected:
	int updateState_;
	const GraphType * graph_;
	int type_;
};

#endif	//end of BoundingEntity.h