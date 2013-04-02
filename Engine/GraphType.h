#ifndef __GRAPHTYPE_H__
#define __GRAPHTYPE_H__

#define D2DDRAW

#include <d2d1.h>
#include "Vertex2D_F.h"

#ifdef D2DDRAW

	typedef D2D1_COLOR_F Color_F;

	struct Rect_F
	{
		union
		{
			struct {
				float x0;
				float y0;
				float x1;
				float y1;
			};
			struct 
			{
				Vertex2D_F v0;
				Vertex2D_F v1;
			};	
		};
	};

	const Rect_F RectNull = { 0 };

	const Color_F BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
#else

#endif	//end #ifdef D2DDRAW

class GraphType
{
public:
	int GetGraphType() const { return type_; }
protected:
	int type_;
};

enum GRAPHTYPE
{
	POLYGONTYPE = 0,
	RECTANGLETYPE = 1
};

class Polygon2DType : public GraphType
{
public:
	Polygon2DType() : GraphType()
	{
		type_ = POLYGONTYPE;
	}

	~Polygon2DType() { delete [] pVertexArray_; }

public:
	int state_;		
	int numVertex_;
	
	Vertex2D_F * pVertexArray_;	//存储局部坐标的动态数组

	Vertex2D_F worldVertexCenter;		//世界坐标的中心点坐标
	Vertex2D_F worldVertexFirst;		//最初的世界坐标
	Vertex2D_F * worldVertexArray_;	//存储世界坐标的动态数组
};	//end of struct Polygon2DType

class Rectangle2DType : public GraphType
{
public:
	Rectangle2DType() : GraphType()
	{
		type_ = RECTANGLETYPE;
	}

public:
	int state_;		
	Vertex2D_F p0, p1;

	Vertex2D_F worldVertexCenter;
	union 
	{
		struct {
			Vertex2D_F worldVertex0;
			Vertex2D_F worldVertex1;
		};
		Rect_F worldRect;
	};
};

#endif	//end of GraphType.h