#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "BoundingEntity.h"

class BoundingSphere : public BoundingEntity
{
	//��Ԫ��
	friend class IntersectionSystem; 

public:
	BoundingSphere()
	{
		type_ = BOUNDINGSPHERE;
	}

private:
	//ʹ��rectangle����
	void UpdateWithRectangle();

	//ʹ��sphere����
	void UpdateWithPolygon();

public:
	//��ΧԲԲ������
	float x_, y_;

	//��ΧԲ�뾶
	float r_;
};

#endif	//end of BoundingSpere.h