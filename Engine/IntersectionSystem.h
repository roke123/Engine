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

	//��ʼ����ײϵͳ
	bool Init( float width, float height );

	//������ײϵͳ
	void Run();

	//ж����ײϵͳ
	void ShutDown();

	//Ϊ���δ���һ����Χ��
	bool CreateBoundingSphere( const Rectangle2DType& rect, int type );

	//Ϊ����δ���һ����Χ��
	bool CreateBoundingSphere( const Polygon2DType& polygon, int type );

	//Ϊ���δ���һ����Χ��
	bool CreateBoundingRectangle( const Rectangle2DType& rect, int type );

	//Ϊ����δ���һ����Χ��
	bool CreateBoundingRectangle( const Polygon2DType& polygon, int type );

private:
	//������ײϵͳ����ײʵ��
	void Update();

	//��һ����Χ����뵽��ײϵͳ��
	void AddBoundingSphere( BoundingSphere * boundingSphere, int type );

	//��һ����Χ����뵽��ײϵͳ��
	void AddBoundingRectangle( BoundingRectangle * boundingRectangle, int type );

	//�򵥵İ�Χʵ�����
	bool TestWithBoundingEntity( BoundingEntity * entity1, BoundingEntity * entity2 );

	//�򵥵İ�Χ��������
	bool TestBoundingSphereWithRectangle( BoundingSphere * sphere, BoundingRectangle * rectangle );

	//�򵥵İ�Χ�����
	bool TestBoundingSphereWithSphere( BoundingSphere * sphere1, BoundingSphere * sphere2 );

	//�򵥵İ�Χ�����
	bool TestBoundingRectangleWithRectangle( BoundingRectangle * rect1, BoundingRectangle * rect2 );

	//���Ķ������������ײ����
	bool TestPolygonWithPolygon( const Polygon2DType * polygon1, const Polygon2DType * polygon2 );
	
	//���Ķ�����������ײ����
	bool TestPolygonWithRectangle( const Polygon2DType * polygon, const Rectangle2DType * rect );

	//���ľ����������ײ����
	bool TestRectangleWithRectangle( const Rectangle2DType * rect1, const Rectangle2DType * rect2 );

	//������ͼ�β���
	bool TestWithGraph( const GraphType * graph1, const GraphType * graph2 );

	//������ƶ�ʵ����������б�
	void ComputeTestList( BoundingSphere * sphere, deque< BoundingEntityList >& testList );

	//������ƶ�ʵ����������б�
	void ComputeTestList( BoundingRectangle * rectangle, deque< BoundingEntityList >& testList );

	void LimitBoundingRange( int& min_x, int& max_x, int& min_y, int& max_y );

private:
	IntersectionBlock cells_[BLOCKMAX][BLOCKMAX];

	float perCellWidth_, perCellHeight_;
};

#endif	//end of IntersectionSystem.h