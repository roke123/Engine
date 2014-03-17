#include "Item.h"
#include "ItemBoundingController.h"

bool Item::Init( DrawTool * drawTool, Rect_F& rect, int type, ImageType * image )
{
	isInit_ = true;
	image_ = image;
	type_ = type;
	iHp_ = 1;

	boundingObject_.reset( new ItemBoundingController() );
	drawTool->CreateRectangle2D( rect.v0, rect.v1, &rectangle_ );
	RegisterBoundingControl( boundingObject_, *rectangle_, UNMOVABLE );

	return true;
}

void Item::Draw( DrawTool * drawTool )
{
	if( iHp_ > 0 )
		drawTool->DrawImage( *image_, rectangle_->worldRect );
}

void Item::ShutDown()
{
	isInit_ = false;

	if( boundingObject_ != NULL )
		UnregisterBoundingControl( boundingObject_ );

	if( rectangle_ != NULL )
		delete rectangle_;

	rectangle_ = NULL;
	boundingObject_ = NULL;
}