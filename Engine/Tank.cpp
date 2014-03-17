#include "Tank.h"
#include "TankInputControl.h"
#include "TankBoundingObject.h"
#include "Map.h"

bool Tank::Init( DrawTool * drawTool, int x_, int y_, Map * map )
{
	map_ = map;
	drawTool_ = drawTool;

	iHurt = 1;
	iHp_ = 1;

	speedX_ = map->blockWidth_ / 20;
	speedY_ = map->blockHeight_ / 20;

	drawTool->CreateImageFromFile( L"res/heroup1.bmp", &imageSet_[0] );
	drawTool->CreateImageFromFile( L"res/heroleft1.bmp", &imageSet_[1] );
	drawTool->CreateImageFromFile( L"res/herodown1.bmp", &imageSet_[2] );
	drawTool->CreateImageFromFile( L"res/heroright1.bmp", &imageSet_[3] );

	curImage_ = imageSet_[0];
	direction_ = DIK_UP;

	Vertex2D_F r = { map->blockRect_[x_][y_].v0.x + 2, 
		map->blockRect_[x_][y_].v0.y + 2 };
	drawTool->CreateRectangle2D( r, map->blockRect_[x_][y_].v1, &rect_ );

	inputController_.reset( new TankInputControl );
	RegisterInputControl( inputController_ );

	boundingController_.reset( new TankBoundingObject );
	RegisterBoundingControl( boundingController_, *rect_, MOVABLE );

	return true;
}

void Tank::Fire()
{
	if( bullet_.unique() )
	{
		bullet_->Init( this, drawTool_ );
		map_->AddBullet(bullet_);
	}
}

void Tank::Draw( DrawTool * drawTool )
{
	drawTool->DrawImage( *curImage_, rect_->worldRect );
}

void Tank::ShutDown()
{
	if( inputController_ != NULL )
		UnregisterInputControl( inputController_ );

	if( boundingController_ != NULL )
		UnregisterBoundingControl( boundingController_ );

	for( int i = 0; i < 4; ++ i )
		if( imageSet_[i] != NULL )
		{
			imageSet_[i]->Release();
			imageSet_[i] = NULL;
		}
	
	if( rect_ != NULL ) delete rect_;

	inputController_ = NULL;
	boundingController_ = NULL;
	rect_ = NULL;
}

