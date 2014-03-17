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
	//��Ԫ��
	friend class IntersectionSystem; 

protected:
	BoundingEntity()
	{
		// ����
	}

	void Update()
	{
		if( graph_->GetGraphType() == RECTANGLETYPE )
			UpdateWithRectangle();
		else 
			UpdateWithPolygon();
	}

protected:
	//ʹ��rectangle����
	virtual void UpdateWithRectangle() = 0;

	//ʹ��sphere����
	virtual void UpdateWithPolygon() = 0;

protected:
	const Graph * graph_;

	int type_;
};

#endif	//end of BoundingEntity.h