#ifndef __INTERSECTIONSYSTEM_H__
#define __INTERSECTIONSYSTEM_H__

#include <deque>
using namespace std;

#include "IntersectionBlock.h"
#include "GraphType.h"
#include "RefObject.h"

enum MOVETYPE
{
	MOVABLE = 0,
	UNMOVABLE = 1
};

const int BLOCKMAX = 10;
const int BLOCKMIN = 0;

class IntersectionSystem : public RefObject
{
public:
	IntersectionSystem();

	//初始化碰撞系统
	bool Init( float width, float height );

	//运行碰撞系统
	void Run();

	//卸载碰撞系统
	void ShutDown();

	//为矩形创建一个包围球
	bool CreateBoundingSphere( const Rectangle2DType& rect, int type );

	//为多边形创建一个包围球
	bool CreateBoundingSphere( const Polygon2DType& polygon, int type );

	//为矩形创建一个包围框
	bool CreateBoundingRectangle( const Rectangle2DType& rect, int type );

	//为多边形创建一个包围框
	bool CreateBoundingRectangle( const Polygon2DType& polygon, int type );

private:
	//更新碰撞系统中碰撞实体
	void Update();

	//把一个包围球加入到碰撞系统中
	void AddBoundingSphere( BoundingSphere * boundingSphere, int type );

	//把一个包围球加入到碰撞系统中
	void AddBoundingRectangle( BoundingRectangle * boundingRectangle, int type );

	//简单的包围实体测试
	bool TestWithBoundingEntity( BoundingEntity * entity1, BoundingEntity * entity2 );

	//简单的包围球与框测试
	bool TestBoundingSphereWithRectangle( BoundingSphere * sphere, BoundingRectangle * rectangle );

	//简单的包围球测试
	bool TestBoundingSphereWithSphere( BoundingSphere * sphere1, BoundingSphere * sphere2 );

	//简单的包围框测试
	bool TestBoundingRectangleWithRectangle( BoundingRectangle * rect1, BoundingRectangle * rect2 );

	//深层的多边形与多边形碰撞测试
	bool TestPolygonWithPolygon( const Polygon2DType * polygon1, const Polygon2DType * polygon2 );
	
	//深层的多边形与矩形碰撞测试
	bool TestPolygonWithRectangle( const Polygon2DType * polygon, const Rectangle2DType * rect );

	//深层的矩形与矩形碰撞测试
	bool TestRectangleWithRectangle( const Rectangle2DType * rect1, const Rectangle2DType * rect2 );

	//对深层的图形测试
	bool TestWithGraph( const GraphType * graph1, const GraphType * graph2 );

	//计算可移动实体需检测测试列表
	void ComputeTestList( BoundingSphere * sphere, deque< BoundingEntityList >& testList );

	//计算可移动实体需检测测试列表
	void ComputeTestList( BoundingRectangle * rectangle, deque< BoundingEntityList >& testList );

	void LimitBoundingRange( int& min_x, int& max_x, int& min_y, int& max_y );

private:
	IntersectionBlock cells_[BLOCKMAX][BLOCKMAX];

	float perCellWidth_, perCellHeight_;
};

#endif	//end of IntersectionSystem.h