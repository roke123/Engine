#ifndef __HOMEBOUNDINGCONTROLLER_H__
#define __HOMEBOUNDINGCONTROLLER_H__

#include <BoundingObject.h>
#include <Default.h>

#include "Home.h"

class HomeBoundingController : public BoundingController
{
	REGISTER_TARGET(Home);
public:
	HomeBoundingController() : BoundingController( "Home" )
	{
		// Áô¿Õ
	}

	void BoungdingHandler(  const string& name, void * other )
	{
		if( name == "Bullet" )
			target_->isAlive_ = false;
	}
};

#endif	