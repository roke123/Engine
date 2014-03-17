#include "Home.h"
#include "HomeBoundingControl.h"

bool Home::Init( DrawTool * drawTool, Rect_F& rect, ImageType * image )
{
	isAlive_ = true;
	image_ = image;

	boundingController_.reset( new HomeBoundingController() );
	drawTool->CreateRectangle2D( rect.v0, rect.v1, &rectangle_ );
	RegisterBoundingControl( boundingController_, *rectangle_, UNMOVABLE );

	return true;
}

void Home::Draw( DrawTool * drawTool )
{
	drawTool->DrawImage( *image_, rectangle_->worldRect );
}

void Home::ShutDown()
{
	if( rectangle_ != NULL ) { delete rectangle_; rectangle_ = NULL; }
}
