#include "Block.h"
#include "BlockBoundingHandler.h"

bool Block::Init( DrawTool * drawTool, Rect_F& rect, MAPBLOCK type, ImageType * image )
{
	image_ = image;
	type_ = type;

	switch( type )
	{
		case MB_BRICK :
			iHp_ = 1; break;

		case MB_GRASS :
			iHp_ = MAXHP; break;

		case MB_SEA :
			iHp_ = MAXHP; break;

		case MB_ICE :
			iHp_ = 3; break;

		case MB_STONE :
			iHp_ = 3; break;

		case MB_BLACK :
			iHp_ = 0; break;
	}

	boundingObject_.reset( new BlockBoundingHandler() );
	drawTool->CreateRectangle2D( rect.v0, rect.v1, &rectangle_ );
	RegisterBoundingControl( boundingObject_, *rectangle_, UNMOVABLE );

	return true;
}

void Block::Draw( DrawTool * drawTool )
{
	if( iHp_ > 0 )
		drawTool->DrawImage( *image_, rectangle_->worldRect );
}

void Block::ShutDown()
{
	if( boundingObject_ != NULL )
		UnregisterBoundingControl( boundingObject_ );

	if( rectangle_ != NULL )
		delete rectangle_;

	rectangle_ = NULL;
	boundingObject_ = NULL;
}