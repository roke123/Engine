#ifndef __ITEMBOUNDINGHANDLER_H__
#define __ITEMBOUNDINGHANDLER_H__

#include <BoundingObject.h>

#include "Item.h"
#include "Bullet.h"
#include "Tank.h"
#include "Enemy.h"

class ItemBoundingController: public BoundingController
{
	REGISTER_TARGET( Item );
public:
	ItemBoundingController() : BoundingController( "Item" )
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

			switch ( target_->type_ )
			{
			case EIT_SHOVEL :
				if( bullet->tank_ != NULL )
					bullet->tank_->SetHurt(3);

				if( bullet->enemy_ != NULL )
					bullet->enemy_->SetHurt(3);
				break;

			case EIT_LIFE:
				if( bullet->tank_ != NULL )
					bullet->tank_->AddHp();

				if( bullet->enemy_ != NULL )
					bullet->enemy_->AddHp();
				break;
			}

		}
	}


};


#endif	// end of BlockBoundingHandler.h