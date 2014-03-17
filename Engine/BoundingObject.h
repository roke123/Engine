#ifndef __BOUNDINGOBJECT_H__
#define __BOUNDINGOBJECT_H__

#include <memory>
using namespace std::tr1;

#include "Controller.h"
#include "GraphType.h"
#include "BoundingEntity.h"

enum BOUNDINGSTATE
{
	ZERO = 0x00,
	TESTED = 0x01,
	UPDATED = 0x10,
};

class BoundingController : public Controller
{
	friend class IntersectionSystem;
public:
	BoundingController( string name ) : Controller(), entity_(0), name_(name)
	{
		updateState_ = ZERO;
	}
	
	virtual void BoungdingHandler(  const string& otherName, void * other ) = 0;

	// 碰撞实体
	BoundingEntity * entity_;

private:
	// 更新状态
	int updateState_;

	string name_;
};

typedef tr1::shared_ptr<BoundingController> BoundingControllerPtr;

#endif	// end of BoundingObject.h