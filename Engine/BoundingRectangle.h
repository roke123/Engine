#ifndef __BOUNDINGRECTANGLE_H__
#define __BOUNDINGRECTANGLE_H__

#include "BoundingEntity.h"

class BoundingRectangle : public BoundingEntity
{
	//友元类
	friend class IntersectionSystem; 

public:
	BoundingRectangle()
	{
		type_ = BOUNDINGRECTANGLE;
	}

private:
	//使用rectangle更新
	void UpdateWithRectangle();

	//使用sphere更新
	void UpdateWithPolygon();

public:
	float min_x, max_x, min_y, max_y;

};	//end of class BoundingRectangle

#endif	//end of BoundingRectangle.h