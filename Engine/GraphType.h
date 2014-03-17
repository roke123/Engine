#ifndef __GRAPHTYPE_H__
#define __GRAPHTYPE_H__

#define D2DDRAW

#include "Vertex2D.h"

#include <memory>
#include <d2d1.h>
using namespace std::tr1;


#ifdef D2DDRAW

	typedef D2D1_COLOR_F Color_F;

	struct Rect_U
	{
		union
		{
			struct {
				int x0;
				int y0;
				int x1;
				int y1;
			};
			struct 
			{
				Vertex2D_U v0;
				Vertex2D_U v1;
			};	
		};
	}; 

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

class Graph
{
public:
	int GetGraphType() const { return type_; }
protected:
	int type_;
};

typedef shared_ptr< Graph > GraphPtr;

enum GRAPHTYPE
{
	POLYGONTYPE = 0,
	RECTANGLETYPE = 1
};

class Polygon2D : public Graph
{
public:
	Polygon2D() : Graph()
	{
		//����
		type_ = POLYGONTYPE;
	}

	~Polygon2D() { delete [] pVertexArray_; }

public:
	int numVertex_;
	
	Vertex2D_F * pVertexArray_;	//�洢�ֲ�����Ķ�̬����

	Vertex2D_F worldVertexCenter;		//������������ĵ�����
	Vertex2D_F worldVertexFirst;		//�������������
	Vertex2D_F * worldVertexArray_;	//�洢��������Ķ�̬����
};	//end of struct Polygon2DType

typedef shared_ptr< Polygon2D > PolygonPtr;

class Rectangle2D : public Graph
{
public:
	Rectangle2D() : Graph()
	{
		type_ = RECTANGLETYPE;
	}

public:
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

typedef shared_ptr< Rectangle2D > RectanglePtr;

#endif	//end of GraphType.h