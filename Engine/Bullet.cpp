#include "Bullet.h"
#include "BulletTimeControl.h"
#include "BulletBoundingControl.h"
#include "Tank.h"
#include "Enemy.h"

bool Bullet::Init( Enemy * enemy, DrawTool * drawTool )
{
	tank_ = NULL;
	enemy_ = enemy;
	isBounding_ = false;

	hurt_ = enemy_->iHurt;

	Vertex2D_F r = enemy_->rect_->worldVertexCenter;
	r.x -= 4;
	r.y -= 4;

	switch( enemy_->direction_ )
	{
		case 0: speedX_ = 0.0f, speedY_ = -enemy_->speedY_ * 2.0f; break;
		case 1: speedX_ = 0.0f, speedY_ = enemy_->speedY_ * 2.0f; break;
		case 2: speedX_ = -enemy_->speedX_ * 2.0f, speedY_ = 0.0f; break;
		case 3: speedX_ = enemy_->speedX_ * 2.0f, speedY_ = 0.0f; break;
	}

	drawTool->CreateRectangle2D( r, 8, 8,
		&rect_ );

	drawTool->CreateImageFromFile( L"res/hb.bmp", &image_ );

	timeController_.reset( new BulletTimeControl );
	RegisterTimeControl( timeController_ );

	boundingController_.reset( new BulletBoundingControl );
	RegisterBoundingControl( boundingController_, *rect_, MOVABLE );

	return true;
}

bool Bullet::Init( Tank * tank, DrawTool * drawTool )
{
	tank_ = tank;
	enemy_ = NULL;
	isBounding_ = false;

	hurt_ = tank_->iHurt;

	Vertex2D_F r = tank->rect_->worldVertexCenter;
	r.x -= 4;
	r.y -= 4;

	switch( tank_->direction_ )
	{
		case DIK_UP: speedX_ = 0.0f, speedY_ = -tank_->speedY_ * 2.0f; break;
		case DIK_DOWN: speedX_ = 0.0f, speedY_ = tank_->speedY_ * 2.0f; break;
		case DIK_LEFT: speedX_ = -tank_->speedX_ * 2.0f, speedY_ = 0.0f; break;
		case DIK_RIGHT: speedX_ = tank_->speedX_ * 2.0f, speedY_ = 0.0f; break;
	}

	drawTool->CreateRectangle2D( r, 8, 8,
		&rect_ );

	drawTool->CreateImageFromFile( L"res/hb.bmp", &image_ );

	timeController_.reset( new BulletTimeControl );
	RegisterTimeControl( timeController_ );

	boundingController_.reset( new BulletBoundingControl );
	RegisterBoundingControl( boundingController_, *rect_, MOVABLE );

	return true;
}

void Bullet::Draw( DrawTool * drawTool )
{
	drawTool->DrawImage( *image_, rect_->worldRect );
}

void Bullet::ShutDown()
{
	if( rect_ != NULL ) delete rect_;
	if( image_ != NULL ) image_->Release();
	if( timeController_ != NULL ) UnregisterTimeControl( timeController_ );
	if( boundingController_ != NULL ) UnregisterBoundingControl( boundingController_ );

	rect_ = NULL;
	image_ = NULL;
	timeController_ = NULL;
	boundingController_ = NULL;
}