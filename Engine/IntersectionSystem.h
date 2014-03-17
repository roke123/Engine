#ifndef __INTERSECTIONSYSTEM_H__
#define __INTERSECTIONSYSTEM_H__

#include <deque>
using namespace std;

#include "IntersectionBlock.h"
#include "GraphType.h"
#include "BoundingObject.h"

enum MOVETYPE
{
	MOVABLE = 0,
	UNMOVABLE = 1
};

const int BLOCKMAX = 10;
const int BLOCKMIN = 0;

class IntersectionSystem;
typedef shared_ptr<IntersectionSystem> IntersectionSystemPtr;

class IntersectionSystem
{
	friend class BoundingObject;
public:
	IntersectionSystem();

	//初始化碰撞系统
	bool Init( float width, float height );

	//运行碰撞系统
	void Run();

	//卸载碰撞系统
	void ShutDown();

	static IntersectionSystemPtr GetIntersectionSystem();

	//为矩形创建一个包围球
	BoundingEntity * CreateBoundingSphere( const Rectangle2D& rect, int type );

	//为多边形创建一个包围球
	BoundingEntity * CreateBoundingSphere( const Polygon2D& polygon, int type );

	//为矩形创建一个包围框
	BoundingEntity * CreateBoundingRectangle( const Rectangle2D& rect, int type );

	//为多边形创建一个包围框
	BoundingEntity * CreateBoundingRectangle( const Polygon2D& polygon, int type );

	void AddBoundingObject( BoundingControllerPtr object , int type );

private:
	//更新碰撞系统中碰撞实体
	void Update();

	//把一个包围球加入到碰撞系统中
	void AddBoundingSphere( BoundingSphere * boundingSphere, int type, BoundingControllerPtr object );

	//把一个包围球加入到碰撞系统中
	void AddBoundingRectangle( BoundingRectangle * boundingRectangle, int type, BoundingControllerPtr object  );

	//简单的包围实体测试
	bool TestWithBoundingEntity( BoundingEntity * entity1, BoundingEntity * entity2 );

	//简单的包围球与框测试
	bool TestBoundingSphereWithRectangle( BoundingSphere * sphere, BoundingRectangle * rectangle );

	//简单的包围球测试
	bool TestBoundingSphereWithSphere( BoundingSphere * sphere1, BoundingSphere * sphere2 );

	//简单的包围框测试
	bool TestBoundingRectangleWithRectangle( BoundingRectangle * rect1, BoundingRectangle * rect2 );
  
	//深层的多边形与多边形碰撞测试
	bool TestPolygonWithPolygon( const Polygon2D * polygon1, const Polygon2D * polygon2 );
	
	//深层的多边形与矩形碰撞测试
	bool TestPolygonWithRectangle( const Polygon2D * polygon, const Rectangle2D * rect );

	//深层的矩形与矩形碰撞测试
	bool TestRectangleWithRectangle( const Rectangle2D * rect1, const Rectangle2D * rect2 );

	//对深层的图形测试
	bool TestWithGraph( const Graph * graph1, const Graph * graph2 );

	//计算可移动实体需检测测试列表
	void ComputeTestList( BoundingSphere * sphere, deque< BoundingList >& testList );

	//计算可移动实体需检测测试列表
	void ComputeTestList( BoundingRectangle * rectangle, deque< BoundingList >& testList );

	void LimitBoundingRange( int& min_x, int& max_x, int& min_y, int& max_y );

	//简单的包围球与边碰撞测试
	bool TestWithBoundingSide( BoundingEntity * pEntity );

	//简单的包围球与边碰撞测试
	bool TestBoundingSphereWithBoundingSide( BoundingSphere * pEntity );

	//简单的包围框与边碰撞测试
	bool TestBoundingRectangleWithBoundingSide( BoundingRectangle * pEntity );

	//深层的多边形与边碰撞测试
	bool TestPolygonWithBoundingSide( const Polygon2D * polygon );
	
	//深层的多边形与边碰撞测试
	bool TestRectangleWithBoundingSide( const Rectangle2D * rect );

	//对深层的图形测试
	bool TestGraphWithBoundingSide( const Graph * graph );

private:
	IntersectionBlock cells_[BLOCKMAX][BLOCKMAX];

	float perCellWidth_, perCellHeight_;

	float width_, height_; 
};

#endif	//end of IntersectionSystem.h