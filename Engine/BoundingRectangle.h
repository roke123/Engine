#ifndef __BOUNDINGRECTANGLE_H__
#define __BOUNDINGRECTANGLE_H__

#include "BoundingEntity.h"

class BoundingRectangle : public BoundingEntity
{
	//��Ԫ��
	friend class IntersectionSystem; 

public:
	BoundingRectangle()
	{
		type_ = BOUNDINGRECTANGLE;
	}

private:
	//ʹ��rectangle����
	void UpdateWithRectangle();

	//ʹ��sphere����
	void UpdateWithPolygon();

public:
	float min_x, max_x, min_y, max_y;

};	//end of class BoundingRectangle

#endif	//end of BoundingRectangle.h