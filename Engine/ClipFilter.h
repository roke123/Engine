#ifndef __CULLFILTER_H__
#define __CULLFILTER_H__

#include <memory>
using namespace std::tr1;

#include "GraphType.h"

class ClipFilter
{
public:
	ClipFilter()
	{
	}

	virtual ~ClipFilter() {};

	virtual int ClipLine( Vertex2D_F& p0, Vertex2D_F& p1 ) const = 0;
};

typedef shared_ptr<ClipFilter> ClipFilterPtr;

#endif	//end of CullFilter