#ifndef __VERTEX2D_F_H__
#define __VERTEX2D_F_H__

#ifdef D2DDRAW

#include <D2D1.h>
	typedef D2D1_POINT_2F Vertex2D_F; 

#else
	
	struct Vertex2D_F
	{
		float x, y;
	};

#endif	//end of D2DDRAW

Vertex2D_F operator + ( const Vertex2D_F& v0, const Vertex2D_F& v1 );
Vertex2D_F operator += ( Vertex2D_F& v0, const Vertex2D_F& v1 );

#endif	// end of Vertex2D_F.h