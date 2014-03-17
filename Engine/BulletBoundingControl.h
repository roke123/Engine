#ifndef BULLETBOUNDINGCONTROL_H__
#define BULLETBOUNDINGCONTROL_H__

#include <BoundingObject.h>
#include <Default.h>

#include "Bullet.h"
#include "Block.h"

class BulletBoundingControl : public BoundingController
{
	REGISTER_TARGET( Bullet );

public:
	BulletBoundingControl() : BoundingController( "Bullet" )
	{
		// Áô¿Õ
	}

	void BoungdingHandler( const string& name, void * other )
	{	
		if( name == "Tank" && other == target_->tank_ )
			return;

		if( name == "Enemy" && other == target_->enemy_ )
			return;

		if( name == "Block" && ((Block*)other)->GetType() == MB_SEA )
			return;

		target_->isBounding_ = true;
	}	
};

#endif	// end of BulletBoundingController.h