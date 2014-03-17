#include "Enemy.h"
#include "EnemyBoundingControl.h"
#include "EnemyTimeController.h"
#include "Map.h"

bool Enemy::Init( DrawTool * drawTool, Rect_F rect, Map * map )
{
	map_ = map;
	drawTool_ = drawTool;

	iHurt = 1;
	iHp_ = 1;

	speedX_ = map->blockWidth_ / 20;
	speedY_ = map->blockHeight_ / 20;

	drawTool->CreateImageFromFile( L"res/enemyup3.bmp", &imageSet_[0] );
	drawTool->CreateImageFromFile( L"res/enemyleft3.bmp", &imageSet_[1] );
	drawTool->CreateImageFromFile( L"res/enemydown3.bmp", &imageSet_[2] );
	drawTool->CreateImageFromFile( L"res/enemyright3.bmp", &imageSet_[3] );

	curImage_ = imageSet_[2];
	direction_ = 2;

	Vertex2D_F r = { rect.v0.x + 2, 
		rect.v0.y + 2 };
	drawTool->CreateRectangle2D( r, rect.v1, &rect_ );

	timeController_.reset( new EnemyTimeController );
	RegisterTimeControl( timeController_ );

	boundingController_.reset( new EnemyBoundingController );
	RegisterBoundingControl( boundingController_, *rect_, MOVABLE );

	return true;
}

void Enemy::Fire()
{
	if( bullet_.unique() )
	{
		bullet_->Init( this, drawTool_ );
		map_->AddBullet(bullet_);
	}
}

void Enemy::Draw( DrawTool * drawTool )
{
	drawTool->DrawImage( *curImage_, rect_->worldRect );
}

void Enemy::ShutDown()
{
	if( timeController_ != NULL )
		UnregisterTimeControl( timeController_ );

	if( boundingController_ != NULL )
		UnregisterBoundingControl( boundingController_ );

	for( int i = 0; i < 4; ++ i )
		if( imageSet_[i] != NULL )
		{
			imageSet_[i]->Release();
			imageSet_[i] = NULL;
		}
	
	if( rect_ != NULL ) delete rect_;

	timeController_ = NULL;
	boundingController_ = NULL;
	rect_ = NULL;
}

void Enemy::Reset()
{
	if( timeController_ != NULL )
		UnregisterTimeControl( timeController_ );

	isReset_ = true;
	IsBounding_ = false;
	iHp_ = 1;
	iHurt = 1;
	curImage_ = imageSet_[2];
	direction_ = 2;
	resetBounding_ = false;

	timeController_.reset( new EnemyTimeController );
	RegisterTimeControl( timeController_ );
}

