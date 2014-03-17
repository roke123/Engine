#ifndef __TANKBOUNDINGOBJECT_H__
#define __TANKBOUNDINGOBJECT_H__

#include <BoundingObject.h>
#include <Default.h>
#include <fstream>

#include "Tank.h"
#include "Bullet.h"

class TankBoundingObject : public BoundingController
{
	REGISTER_TARGET( Tank );
public:
	TankBoundingObject() : BoundingController( "Tank" )
	{
		lastBullet_ = 0;
	}

	void BoungdingHandler( const string& name, void * other )
	{
		if( name != "Bullet" )
			target_->IsBounding_ = true;
		else
			if( ((Bullet*)other)->GetTank() != target_ && other != lastBullet_ )
			{
				lastBullet_ = other;
				fstream file;
				file.open("life.txt", ios::out );
				target_->iHp_ += ((Bullet*)other)->GetHurt();
				file << ' ' << target_->iHp_;
				file.close();
			}
	}

private:
	void * lastBullet_;
};

#endif	// end of TankBoundingObject.h