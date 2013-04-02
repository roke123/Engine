#ifndef __CULLFILTER_H__
#define __CULLFILTER_H__

#include "GraphType.h"
#include "RefObject.h"

class ClipFilter : public RefObject
{
public:
	ClipFilter() : RefObject()
	{
	}

	virtual ~ClipFilter() {};

	virtual int ClipLine( Vertex2D_F& p0, Vertex2D_F& p1 ) const = 0;
};

#endif	//end of CullFilter