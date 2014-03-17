#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "BoundingEntity.h"

class BoundingSphere : public BoundingEntity
{
	//友元类
	friend class IntersectionSystem; 

public:
	BoundingSphere()
	{
		type_ = BOUNDINGSPHERE;
	}

private:
	//使用rectangle更新
	void UpdateWithRectangle();

	//使用sphere更新
	void UpdateWithPolygon();

public:
	//包围圆圆心坐标
	float x_, y_;

	//包围圆半径
	float r_;
};

#endif	//end of BoundingSpere.h