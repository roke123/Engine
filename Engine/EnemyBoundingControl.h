#ifndef __TANKBOUNDINGOBJECT_H__
#define __TANKBOUNDINGOBJECT_H__

#include <BoundingObject.h>
#include <Default.h>

#include "Enemy.h"
#include "Bullet.h"

class EnemyBoundingController : public BoundingController
{
	REGISTER_TARGET( Enemy );
public:
	EnemyBoundingController() : BoundingController( "Enemy" )
	{
		//Áô¿Õ
	}

	void BoungdingHandler( const string& name, void * other )
	{
		if( (name == "Enemy" || name == "Tank") && target_->isReset_  )
			target_->resetBounding_ = true;

		if( name != "Bullet" )
			target_->IsBounding_ = true;
		else
			if( ((Bullet*)other)->GetEnemy() == NULL )
				target_->iHp_ -= ((Bullet*)other)->GetHurt();
	}
};

#endif	// end of TankBoundingObject.h