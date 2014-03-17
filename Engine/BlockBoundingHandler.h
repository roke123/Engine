#ifndef __BLOCKBOUNDINGHANDLER_H__
#define __BLOCKBOUNDINGHANDLER_H__

#include <BoundingObject.h>

#include "Block.h"
#include "Bullet.h"

class BlockBoundingHandler : public BoundingController
{
	REGISTER_TARGET( Block );
public:
	BlockBoundingHandler() : BoundingController( "Block" )
	{
		//Áô¿Õ
	}

	void BoungdingHandler( const string& name, void * other )
	{
		if( name == "Bullet" )
		{
			Bullet * bullet = (Bullet*)other;
			if( target_->iHp_ <= ((Bullet*)other)->GetHurt() )
				target_->iHp_ = 0;
		}
	}


};


#endif	// end of BlockBoundingHandler.h