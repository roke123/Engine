#ifndef __RECTANGLECLIPFILTER_H__
#define __RECTANGLECLIPFILTER_H__

#include "ClipFilter.h"

class RectangleClipFilter : public ClipFilter
{
public:
	RectangleClipFilter( const Rectangle2DType& rc );
	~RectangleClipFilter();

	//override
	int ClipLine( Vertex2D_F& p0, Vertex2D_F& p1 ) const;

private:
	Rectangle2DType rc_;
};

#endif	//end of RectangleClipFilter.h