#include "DrawTool.h"

//创建一个矩形
bool DrawTool::CreateRectangle2D( const Vertex2D_F& p0, const Vertex2D_F& p1, Rectangle2D ** pRectangle ) const
{
	*pRectangle = new Rectangle2D;

	//p0为左上角，p1为右下角
	if( p0.x > p1.x )
	{
		(*pRectangle)->p0.x = p1.x;
		(*pRectangle)->p1.x = p0.x;
	} else {
		(*pRectangle)->p0.x = p0.x;
		(*pRectangle)->p1.x = p1.x;
	}

	if( p0.y > p1.y )
	{
		(*pRectangle)->p0.y = p1.y;
		(*pRectangle)->p1.y = p0.y;
	} else {
		(*pRectangle)->p0.y = p0.y;
		(*pRectangle)->p1.y = p1.y;
	}

	(*pRectangle)->worldVertex0 = (*pRectangle)->p0;
	(*pRectangle)->worldVertex1 = (*pRectangle)->p1;
	(*pRectangle)->worldVertexCenter.x = ( p0.x + p1.x ) / 2;
	(*pRectangle)->worldVertexCenter.y = ( p0.y + p1.y ) / 2;

	return true;
}

bool DrawTool::CreateRectangle2D( const Vertex2D_F& p0, int width, int height, Rectangle2D ** pRectangle ) const
{
	(*pRectangle) = new Rectangle2D;
	if( pRectangle == NULL )
	{
		return false;
	}

	(*pRectangle)->worldVertex0 = (*pRectangle)->p0 = p0;
	(*pRectangle)->worldVertex1.x = (*pRectangle)->p1.x = p0.x + width;
	(*pRectangle)->worldVertex1.y = (*pRectangle)->p1.y = p0.y + height;
	(*pRectangle)->worldVertexCenter.x = p0.x + width / 2;
	(*pRectangle)->worldVertexCenter.y = p0.y + height / 2;

	return true;
}


bool DrawTool::CreatePolygon2D( Vertex2D_F * pVertexList, int numVertex, Polygon2D ** pPolygon ) const
{
	*pPolygon = new Polygon2D;
	if( pPolygon == NULL )
	{
		return false;
	}

	(*pPolygon)->numVertex_ = numVertex;
	(*pPolygon)->pVertexArray_ = new Vertex2D_F[numVertex];
	(*pPolygon)->worldVertexArray_ = new Vertex2D_F[numVertex];
	memcpy( (*pPolygon)->pVertexArray_, pVertexList, sizeof( Vertex2D_F ) * numVertex );
	memcpy( (*pPolygon)->worldVertexArray_, pVertexList, sizeof( Vertex2D_F ) * numVertex );
	(*pPolygon)->worldVertexFirst = pVertexList[0];

	float sum_x = 0, sum_y = 0;
	for( int i = 0; i < numVertex; ++ i )
	{
		sum_x += pVertexList[i].x;
		sum_y += pVertexList[i].y;
	}

	(*pPolygon)->worldVertexCenter.x = sum_x / numVertex;
	(*pPolygon)->worldVertexCenter.y = sum_y / numVertex;

	return true;
}