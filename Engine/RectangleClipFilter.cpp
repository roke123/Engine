#include "RectangleClipFilter.h"

RectangleClipFilter::RectangleClipFilter( const Rectangle2DType& rc )
	: ClipFilter()
{
	rc_ = rc;

	//调整rc坐标为左上角与右下角
	float temp = 0.0f;
	if( rc_.p0.x > rc_.p1.x )
	{
		temp = rc_.p0.x;
		rc_.p0.x = rc_.p1.x;
		rc_.p1.x = temp;
	}

	if( rc_.p0.y > rc_.p1.y )
	{
		temp = rc_.p0.y;
		rc_.p0.y = rc_.p1.y;
		rc_.p1.y = temp;
	}
}

RectangleClipFilter::~RectangleClipFilter()
{

}

int RectangleClipFilter::ClipLine( Vertex2D_F& p0, Vertex2D_F& p1 ) const
{
	//此函数用于使用一个矩形裁剪器裁剪一条直线

#define CLIP_CODE_C 0x0000
#define CLIP_CODE_N 0x0001
#define CLIP_CODE_S 0x0002
#define CLIP_CODE_E 0x0004
#define CLIP_CODE_W 0x0008

#define CLIP_CODE_NE 0x0005		//CLIP_CODE_N | CLIP_CODE_E
#define CLIP_CODE_SE 0x0006		//CLIP_CODE_S | CLIP_CODE_E
#define CLIP_CODE_NW 0x0009		//CLIP_CODE_N | CLIP_CODE_W
#define CLIP_CODE_SW 0x000a		//CLIP_CODE_S | CLIP_CODE_W

	int p0Code = CLIP_CODE_C, p1Code = CLIP_CODE_C;

	if( p0.y < rc_.p0.y)
		p0Code |= CLIP_CODE_N;
	else if ( p0.y > rc_.p1.y )
		p0Code |= CLIP_CODE_S;

	if( p0.x < rc_.p0.x )
		p0Code |= CLIP_CODE_W;
	else if ( p0.x > rc_.p1.x )
		p0Code |= CLIP_CODE_E;

	if( p1.y < rc_.p0.y)
		p1Code |= CLIP_CODE_N;
	else if ( p1.y > rc_.p1.y )
		p1Code |= CLIP_CODE_S;

	if( p1.x < rc_.p0.x )
		p1Code |= CLIP_CODE_W;
	else if ( p1.x > rc_.p1.x )
		p1Code |= CLIP_CODE_E;

	if( p0Code & p1Code )
		return 0;

	if( p0Code == 0 && p1Code == 0 )
		return 1;

	float dy = (p0.x - p1.x) / (p0.y - p1.y),
		dx = (p0.y - p1.y) / (p0.x - p1.x);

	float temp_x0 = p0.x, temp_y0 = p0.y,
		temp_x1 = p1.x, temp_y1 = p1.y;

	switch ( p0Code )
	{
	case CLIP_CODE_C:
		break;

	case CLIP_CODE_N:
		temp_y0 = rc_.p0.y;
		temp_x0 = p0.x + 0.5f + ( rc_.p0.y - p0.y ) * dy;
		break;

	case CLIP_CODE_S:
		temp_y0 = rc_.p1.y;
		temp_x0 = p0.x + 0.5f + ( rc_.p1.y - p0.y ) * dy;
		break;

	case CLIP_CODE_E:
		temp_x0= rc_.p1.x;
		temp_y0 = p0.y + 0.5f + ( rc_.p1.x - p0.x ) * dx;
		break;

	case CLIP_CODE_W:
		temp_x0 = rc_.p0.x;
		temp_y0 = p0.y + 0.5f + ( rc_.p0.x - p0.x ) * dx;
		break;

	case CLIP_CODE_NE:
		temp_y0 = rc_.p0.y;
		temp_x0 = p0.x + 0.5f + ( rc_.p0.y - p0.y ) * dy;

		if( temp_x0 < rc_.p0.x || temp_x0 > rc_.p1.x )
		{
			temp_x0 = rc_.p1.x;
			temp_y0 = p0.y + 0.5f + ( rc_.p1.x - p0.x ) * dx;		
		}
		break;

	case CLIP_CODE_NW:
		temp_y0 = rc_.p0.y;
		temp_x0 = p0.x + 0.5f + ( rc_.p0.y - p0.y ) * dy;

		if( temp_x0 < rc_.p0.x || temp_x0 > rc_.p1.x )
		{
			temp_x0 = rc_.p0.x;
			temp_y0 = p0.y + 0.5f + ( rc_.p0.x - p0.x ) * dx;		
		}
		break;

	case CLIP_CODE_SE:
		temp_y0 = rc_.p1.y;
		temp_x0 = p0.x + 0.5f + ( rc_.p1.y - p0.y ) * dy;

		if( temp_x0 < rc_.p0.x || temp_x0 > rc_.p1.x )
		{
			temp_x0 = rc_.p1.x;
			temp_y0 = p0.y + 0.5f + ( rc_.p1.x - p0.x ) * dx;
		}
		break;

	case CLIP_CODE_SW:
		temp_y0 = rc_.p1.y;
		temp_x0 = p0.x + 0.5f + ( rc_.p1.y - p0.y ) * dy;

		if( temp_x0 < rc_.p0.x || temp_x0 > rc_.p1.x )
		{
			temp_x0 = rc_.p0.x;
			temp_y0 = p0.y + 0.5f + ( rc_.p0.x - p0.x ) * dx;
		}
		break;
	}

	switch( p1Code )
	{
	case CLIP_CODE_C:
		break;

	case CLIP_CODE_N:
		temp_y1 = rc_.p0.y;
		temp_x1 = p1.x + 0.5f + (rc_.p0.y - p1.y) * dy;
		break;
		
	case CLIP_CODE_S:
		temp_y1 = rc_.p1.y;
		temp_x1 = p1.x + 0.5f + (rc_.p1.y - p1.y) *  dy;
		break;

	case CLIP_CODE_W:
		temp_x1 = rc_.p0.x;
		temp_y1 = p1.y + 0.5f + (rc_.p0.x - p1.x) * dx;
		break;
		
	case CLIP_CODE_E:
		temp_x1 = rc_.p1.x;
		temp_y1 = p1.y + 0.5f + (rc_.p1.x - p1.x) * dx;
		break;

	case CLIP_CODE_NE:
		temp_y1 = rc_.p0.y;
		temp_x1 = p1.x + 0.5f + (rc_.p0.y - p1.y) * dy;

		if( temp_x1 < rc_.p0.x || temp_x1 > rc_.p1.x )
		{
			temp_x1 = rc_.p1.x;
			temp_y1 = p1.y + 0.5f + (rc_.p1.x - p1.x) * dx;
		}
		break;

	case CLIP_CODE_NW:
		temp_y1 = rc_.p0.y;
		temp_x1 = p1.x + 0.5f + (rc_.p0.y - p1.y) * dy;

		if( temp_x1 < rc_.p0.x || temp_x1 > rc_.p1.x )
		{
			temp_x1 = rc_.p0.x;
			temp_y1 = p1.y + 0.5f + (rc_.p0.x - p1.x) * dx;
		}
		break;

	case CLIP_CODE_SE:
		temp_y1 = rc_.p1.y;
		temp_x1 = p1.x + 0.5f + (rc_.p1.y - p1.y) * dy;

		if( temp_x1 < rc_.p0.x || temp_x1 > rc_.p1.x )
		{
			temp_x1 = rc_.p1.x;
			temp_y1 = p1.y + 0.5f + (rc_.p1.x - p1.x) * dx;
		}
		break;

	case CLIP_CODE_SW:
		temp_y1 = rc_.p1.y;
		temp_x1 = p1.x + 0.5f + (rc_.p1.y - p1.y) * dy;

		if( temp_x1 < rc_.p0.x || temp_x1 > rc_.p1.x )
		{
			temp_x1 = rc_.p0.x;
			temp_y1 = p1.y + 0.5f + (rc_.p0.x - p1.x) * dx;
		}
		break;
	}

	p0.x = temp_x0, p0.y = temp_y0;
	p1.x = temp_x1, p1.y = temp_y1;

	return 1;
}