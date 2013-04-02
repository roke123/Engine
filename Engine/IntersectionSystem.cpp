#include "IntersectionSystem.h"
#include "GlobalFunction.h"
#include <math.h>

IntersectionSystem::IntersectionSystem()
{

}

void IntersectionSystem::AddBoundingSphere( BoundingSphere * boundingSphere, int type )
{
	if( type == MOVABLE )
	{
		cells_[0][0].AddMovableBoundingEntity(boundingSphere);
		return;
	}

	int min_x = (int)( fabs(boundingSphere->x_ - boundingSphere->r_) / perCellWidth_ ),
		max_x = (int)( fabs(boundingSphere->x_ + boundingSphere->r_) / perCellWidth_ ),
		min_y = (int)( fabs(boundingSphere->y_ - boundingSphere->r_) / perCellHeight_ ),
		max_y = (int)( fabs(boundingSphere->y_ + boundingSphere->r_) / perCellHeight_ );

	LimitBoundingRange( min_x, max_x, min_y, max_y );

	while( max_x >= min_x )
	{
		int temp = min_y;

		while( max_y >= min_y )
		{
			cells_[min_x][min_y].AddUnmovableBoundingEntity(boundingSphere);
			++ min_y;
		}

		min_y = temp;
		++ min_x;
	}
}

void IntersectionSystem::AddBoundingRectangle( BoundingRectangle * boundingRectangle, int type )
{
	if( type == MOVABLE )
	{
		cells_[0][0].AddMovableBoundingEntity(boundingRectangle);
		return;
	}

	int min_x = (int)( boundingRectangle->min_x / perCellWidth_ ),
		max_x = (int)( boundingRectangle->max_x / perCellWidth_ ),
		min_y = (int)( boundingRectangle->min_y / perCellHeight_ ),
		max_y = (int)( boundingRectangle->max_y / perCellHeight_ );

	LimitBoundingRange( min_x, max_x, min_y, max_y );

	while( max_x >= min_x )
	{
		int temp = min_y;

		while( max_y >= min_y )
		{
			cells_[min_x][min_y].AddUnmovableBoundingEntity(boundingRectangle);
			++ min_y;
		}

		min_y = temp;
		++ min_x;
	}
}

bool IntersectionSystem::CreateBoundingRectangle( const Polygon2DType& polygon, int type )
{
	float min_x = polygon.worldVertexArray_[0].x, 
		  max_x = polygon.worldVertexArray_[0].x,
		  min_y = polygon.worldVertexArray_[0].y,
		  max_y = polygon.worldVertexArray_[0].y;

	for( int i = 1; i < polygon.numVertex_; ++ i )
	{
		if( polygon.worldVertexArray_[i].x < min_x )
			min_x = polygon.worldVertexArray_[i].x;
		else if ( polygon.worldVertexArray_[i].x > max_x )
			max_x = polygon.worldVertexArray_[i].x;

		if( polygon.worldVertexArray_[i].y < min_y )
			min_y = polygon.worldVertexArray_[i].y;	
		else if ( polygon.worldVertexArray_[i].y > max_y )
			max_y = polygon.worldVertexArray_[i].y;
	}

	BoundingRectangle * boundingRectangle = new BoundingRectangle;
	if( boundingRectangle == 0 )
	{
		return false;
	}

	boundingRectangle->min_x = min_x;
	boundingRectangle->max_x = max_x;
	boundingRectangle->min_y = min_y;
	boundingRectangle->max_y = max_y;
	boundingRectangle->graph_ = &polygon;

	AddBoundingRectangle( boundingRectangle, type );

	return true;
}

bool IntersectionSystem::Init( float width, float height )
{
	perCellHeight_ = height / 20;
	perCellWidth_ = width / 20;

	return true;
}

void IntersectionSystem::Run()
{
	Update();

	//需检测的实体链
	BoundingEntityList movableTest;

	//被检测的实体链
	deque< BoundingEntityList > boundingList;

	//链节点类型定义
	typedef deque< BoundingEntityList >::iterator BoundingEntityListList;
	typedef BoundingEntityList::iterator BoundingEntityListIte;

	//取得视图中所有可移动的碰撞实体
	movableTest =(*cells_[0][0].movableList_);

	BoundingEntityListIte entityList = movableTest.begin();
	for( ; entityList != movableTest.end(); ++ entityList)
	{
		BoundingEntity * entity = *entityList;

		//检测该实体对应的碰撞快，生成碰撞检测链
		if( entity->type_ == BOUNDINGRECTANGLE )
			ComputeTestList( (BoundingRectangle *)entity, boundingList );
		else 
			ComputeTestList( (BoundingSphere *) entity, boundingList );

		//进行碰撞检测
		BoundingEntityListList testListList =  boundingList.begin();
		for( ; testListList !=  boundingList.end(); ++ testListList )
		{		
			BoundingEntityList testList = *testListList;
			
			BoundingEntityListIte testIte = testList.begin();
			while( testIte != testList.end() )
			{
				BoundingEntity * test = *testIte;

				//检测两实体是否同一实体
				if( test == entity )
				{
					++ testIte;
					continue;
				}
					
				//碰撞检测
				bool result = TestWithBoundingEntity( entity, test );

				//碰撞处理
				if( result )
				{
					MessageBox( 0, "发生碰撞", 0, 0 );
					TestWithBoundingEntity( entity, test );
					return;
				}

				++ testIte;
			}
		}

		//清空被碰撞实体链
		boundingList.clear();
	}
}

void IntersectionSystem::ShutDown()
{
}

bool IntersectionSystem::CreateBoundingSphere( const Rectangle2DType& rect, int type )
{
	float r = 0.0f;

	r = ComputeDistance( rect.worldVertex0, rect.worldVertexCenter );

	BoundingSphere * boundingSphere = new BoundingSphere;
	if( boundingSphere == 0 )
	{
		return false;
	}

	boundingSphere->x_ = rect.worldVertexCenter.x;
	boundingSphere->y_ = rect.worldVertexCenter.y;
	boundingSphere->r_ = r;
	boundingSphere->graph_ = &rect;

	AddBoundingSphere( boundingSphere, type );

	return true;
}

bool IntersectionSystem::CreateBoundingSphere( const Polygon2DType& polygon, int type )
{
	float r = 0.0f;

	for( int i = 0; i < polygon.numVertex_; ++ i )
	{
		float temp = ComputeDistance( polygon.worldVertexCenter, polygon.worldVertexArray_[i] );
		if( temp > r )
			r = temp;
	}

	BoundingSphere * boundingSphere = new BoundingSphere;
	if( boundingSphere == 0 )
	{
		return false;
	}

	boundingSphere->x_ = polygon.worldVertexCenter.x;
	boundingSphere->y_ = polygon.worldVertexCenter.y;
	boundingSphere->r_ = r;
	boundingSphere->graph_ = &polygon;

	AddBoundingSphere( boundingSphere, type );

	return true;
}

bool IntersectionSystem::CreateBoundingRectangle( const Rectangle2DType& rect, int type )
{
	float min_x = rect.worldVertex0.x, 
		  max_x = rect.worldVertex1.x,
		  min_y = rect.worldVertex0.y,
		  max_y = rect.worldVertex1.y,
		  temp = 0.0f;

	if( max_x < min_x )
	{
		temp = max_x;
		max_x = min_x;
		min_x = temp;
	}
	
	if( max_y < min_y )
	{
		temp = max_y;
		max_y = min_y;
		min_y = temp;
	}

	BoundingRectangle * boundingRectangle = new BoundingRectangle;
	if( boundingRectangle == 0 )
	{
		return false;
	}

	boundingRectangle->min_x = min_x;
	boundingRectangle->max_x = max_x;
	boundingRectangle->min_y = min_y;
	boundingRectangle->max_y = max_y;
	boundingRectangle->graph_ = &rect;

	AddBoundingRectangle( boundingRectangle, type );

	return true;
}

bool IntersectionSystem::TestBoundingSphereWithRectangle( BoundingSphere * sphere, BoundingRectangle * rectangle )
{
#define BOUNDING_CODE_C 0x0000
#define BOUNDING_CODE_N 0x0001
#define BOUNDING_CODE_S 0x0002
#define BOUNDING_CODE_E 0x0004
#define BOUNDING_CODE_W 0x0008

#define BOUNDING_CODE_NE 0x0005		//BOUNDING_CODE_N | BOUNDING_CODE_E
#define BOUNDING_CODE_SE 0x0006		//BOUNDING_CODE_S | BOUNDING_CODE_E
#define BOUNDING_CODE_NW 0x0009		//BOUNDING_CODE_N | BOUNDING_CODE_W
#define BOUNDING_CODE_SW 0x000a		//BOUNDING_CODE_S | BOUNDING_CODE_W

	int code = BOUNDING_CODE_C;

	if( sphere->y_ < rectangle->min_y )
		code |= BOUNDING_CODE_N;
	else if ( sphere->y_ > rectangle->max_y  )
		code |= BOUNDING_CODE_S;

	if( sphere->x_ < rectangle->min_x )
		code |= BOUNDING_CODE_W;
	else if ( sphere->x_ > rectangle->max_x )
		code |= BOUNDING_CODE_E;

	float dir = 0.0f;
	bool result = true; 

	switch ( code )
	{
	case BOUNDING_CODE_C:
		break;

	case BOUNDING_CODE_N:
		if( sphere->y_ - rectangle->min_y > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_S:
		if( rectangle->max_y - sphere->y_ > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_E:
		if( rectangle->max_x - sphere->x_ > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_W:
		if( sphere->x_ - rectangle->min_x > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_NE:
		dir = ComputeDistance( sphere->x_, sphere->y_,
			rectangle->max_x, rectangle->min_y );

		if( dir > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_NW:
		dir = ComputeDistance( sphere->x_, sphere->y_,
			rectangle->min_x, rectangle->min_y );

		if( dir > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_SE:
		dir = ComputeDistance( sphere->x_, sphere->y_,
			rectangle->max_x, rectangle->max_y );

		if( dir > sphere->r_ )
			result = false;
		break;

	case BOUNDING_CODE_SW:
		dir = ComputeDistance( sphere->x_, sphere->y_,
			rectangle->min_x, rectangle->max_y );

		if( dir > sphere->r_ )
			result = false;
		break;
	}

	if( result )
		return TestWithGraph( rectangle->graph_, sphere->graph_ );
	
	return result;
}

bool IntersectionSystem::TestBoundingSphereWithSphere( BoundingSphere * sphere1, BoundingSphere * sphere2 )
{
	float dir = ComputeDistance( sphere1->x_, sphere1->y_,
		sphere2->x_, sphere2->y_ );

	if( dir > sphere1->r_ + sphere2->r_ )
		return false;
	else
		return TestWithGraph( sphere1->graph_, sphere2->graph_ );
}

bool IntersectionSystem::TestBoundingRectangleWithRectangle( BoundingRectangle * rect1, BoundingRectangle * rect2 )
{
	if( rect2->max_x < rect1->min_x || rect1->max_x < rect2->min_x )
		return false;

	if( rect2->max_y < rect1->min_y || rect1->max_y < rect2->min_y )
		return false;

	return TestWithGraph( rect1->graph_, rect2->graph_ );
}

bool IntersectionSystem::TestWithBoundingEntity( BoundingEntity * entity1, BoundingEntity * entity2 )
{
	bool result = false;

	if( entity1->type_ == BOUNDINGSPHERE )
	{
		if( entity2->type_ == BOUNDINGSPHERE )
			result = TestBoundingSphereWithSphere( (BoundingSphere *)entity1, (BoundingSphere *)entity2 );
		else
			result = TestBoundingSphereWithRectangle( (BoundingSphere *)entity1, (BoundingRectangle *)entity2 );
	} else {
		if( entity2->type_ == BOUNDINGSPHERE )
			result = TestBoundingSphereWithRectangle( (BoundingSphere *)entity2, (BoundingRectangle *)entity1 );
		else
			result = TestBoundingRectangleWithRectangle( (BoundingRectangle *)entity2, (BoundingRectangle *)entity1 );
	}

	return result;
}

bool IntersectionSystem::TestPolygonWithPolygon( const Polygon2DType * polygon1, const Polygon2DType * polygon2 )
{
	////p1是测试多边形，p2是被测试多边形
	//const Polygon2DType * p1, * p2;

	//if( polygon1->numVertex_ < polygon2->numVertex_ )
	//	p1 = polygon1, p2 = polygon2;
	//else
	//	p1 = polygon2, p2 = polygon1;

	////建立测试向量
	//int numTest = p1->numVertex_ - 1;
	//Vertex2D_F * test = new Vertex2D_F [numTest];
	//for( int i = 0; i < numTest; ++ i )
	//{
	//	test[i].x = p1->worldVertexArray_[i].x - p1->worldVertexArray_[i + 1].x;
	//	test[i].y = p1->worldVertexArray_[i].y - p1->worldVertexArray_[i + 1].y;
	//}

	//bool result = true;
	//for( int i = 0; i < p2->numVertex_; ++ i )
	//{
	//	result = true;
	//	for( int j = 0; j < numTest; ++ j )
	//	{
	//		if( Dot( test[j], p2->worldVertexArray_[i] )  )
	//	}
	//}

	return true;
}
	
bool IntersectionSystem::TestPolygonWithRectangle( const Polygon2DType * polygon, const Rectangle2DType * rect )
{
	for( int i = 0; i < polygon->numVertex_; ++ i )
	{
		Vertex2D_F curVertex = polygon->worldVertexArray_[i];
		
		if( curVertex.x > rect->worldVertex0.x && curVertex.x < rect->worldVertex1.x )
		{
			if( curVertex.y > rect->worldVertex0.y && curVertex.y < rect->worldVertex1.y )
				return true;

			if( curVertex.y > rect->worldVertex1.y && curVertex.y < rect->worldVertex0.y )
				return true;
		}

		if( curVertex.x > rect->worldVertex1.x && curVertex.x < rect->worldVertex0.x )
		{
			if( curVertex.y > rect->worldVertex0.y && curVertex.y < rect->worldVertex1.y )
				return true;

			if( curVertex.y > rect->worldVertex1.y && curVertex.y < rect->worldVertex0.y )
				return true;
		}
	}

	return false;
}

bool IntersectionSystem::TestRectangleWithRectangle( const Rectangle2DType * rect1, const Rectangle2DType * rect2 )
{
	//检查X轴距离
	float dir = fabsf(rect1->worldVertexCenter.x + rect2->worldVertexCenter.x) * 2,
		  boundingdir = fabsf(rect1->worldVertex1.x - rect1->worldVertex0.x) + 
			fabsf(rect2->worldVertex1.x - rect2->worldVertex0.x);

	if( dir > boundingdir )
		return false;

	//检查Y轴距离
	dir = (rect1->worldVertexCenter.y + rect2->worldVertexCenter.y) * 2;
	boundingdir = fabsf(rect1->worldVertex0.y - rect1->worldVertex1.y) + 
		fabsf(rect2->worldVertex0.y - rect2->worldVertex1.y);

	if( dir > boundingdir )
		return false;

	return true;
}

bool IntersectionSystem::TestWithGraph( const GraphType * graph1, const GraphType * graph2 )
{
	if( graph1->GetGraphType() == POLYGONTYPE )
	{
		if( graph2->GetGraphType() == POLYGONTYPE )
			return TestPolygonWithPolygon( (Polygon2DType *) graph1, (Polygon2DType *) graph2 );
		else 
			return TestPolygonWithRectangle( (Polygon2DType *) graph1, (Rectangle2DType *) graph2 );
	} else {
		if( graph2->GetGraphType() == POLYGONTYPE )
			return TestPolygonWithRectangle( (Polygon2DType *) graph2, (Rectangle2DType *) graph1 );
		else 
			return TestRectangleWithRectangle( (Rectangle2DType *) graph1, (Rectangle2DType *) graph2 );
	}
}

void IntersectionSystem::ComputeTestList( BoundingSphere * sphere, deque< BoundingEntityList >& testList )
{
	int min_x = (int)( (sphere->x_ - sphere->r_) / perCellWidth_ ),
		max_x = (int)( (sphere->x_ + sphere->r_) / perCellWidth_ ),
		min_y = (int)( (sphere->y_ - sphere->r_) / perCellHeight_ ),
		max_y = (int)( (sphere->y_ + sphere->r_) / perCellHeight_ );

	LimitBoundingRange( min_x, max_x, min_y, max_y );

	testList.push_back( *cells_[0][0].movableList_ );
	while( max_x > min_x )
	{
		int temp = min_x;

		while( max_y > min_y )
		{	
			testList.push_back( *cells_[min_x][min_y].unmovableList_ );
			++ min_y;
		}

		min_y = temp;
		++ min_x;
	}
}

void IntersectionSystem::ComputeTestList( BoundingRectangle * rectangle, deque< BoundingEntityList >& testList )
{
	int min_x = (int)( rectangle->min_x / perCellWidth_ ),
		max_x = (int)( rectangle->max_x / perCellWidth_ ),
		min_y = (int)( rectangle->min_y / perCellHeight_ ),
		max_y = (int)( rectangle->max_y / perCellHeight_ );

	LimitBoundingRange( min_x, max_x, min_y, max_y );

	testList.push_back( *cells_[0][0].movableList_ );
	while( max_x > min_x )
	{
		int temp = min_y;

		while( max_y > min_y )
		{
			testList.push_back( *cells_[min_x][min_y].unmovableList_ );
			++ min_y;
		}

		min_y = temp;
		++ min_x;
	}
}

void IntersectionSystem::Update()
{
	//需更新的实体链
	list<BoundingEntity *> movableTest;

	//链节点类型定义
	typedef list<BoundingEntity *>::iterator ite;

	//取得视图中所有可移动的碰撞实体
	movableTest = (*cells_[0][0].movableList_);

	ite entityList = movableTest.begin();
	BoundingEntity * entity = 0;
	for( ; entityList != movableTest.end(); ++ entityList)
	{
		(*entityList)->Update();
	}
}

void IntersectionSystem::LimitBoundingRange( int& min_x, int& max_x, int& min_y, int& max_y )
{
	if( min_x < BLOCKMIN )
		min_x = BLOCKMIN;

	if( min_x >= BLOCKMAX )
		min_x = BLOCKMAX;
	
	if( max_x < BLOCKMIN )
		max_x = BLOCKMIN - 1;

	if( max_x >= BLOCKMAX )
		max_x = BLOCKMAX - 1;

	if( min_y < BLOCKMIN )
		min_y = BLOCKMIN;

	if( min_y >= BLOCKMAX )
		min_y = BLOCKMAX;
	
	if( max_y < BLOCKMIN )
		max_y = BLOCKMIN - 1;

	if( max_y >= BLOCKMAX )
		max_y = BLOCKMAX - 1;
}