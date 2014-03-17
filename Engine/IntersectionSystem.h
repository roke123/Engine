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

	//��ʼ����ײϵͳ
	bool Init( float width, float height );

	//������ײϵͳ
	void Run();

	//ж����ײϵͳ
	void ShutDown();

	static IntersectionSystemPtr GetIntersectionSystem();

	//Ϊ���δ���һ����Χ��
	BoundingEntity * CreateBoundingSphere( const Rectangle2D& rect, int type );

	//Ϊ����δ���һ����Χ��
	BoundingEntity * CreateBoundingSphere( const Polygon2D& polygon, int type );

	//Ϊ���δ���һ����Χ��
	BoundingEntity * CreateBoundingRectangle( const Rectangle2D& rect, int type );

	//Ϊ����δ���һ����Χ��
	BoundingEntity * CreateBoundingRectangle( const Polygon2D& polygon, int type );

	void AddBoundingObject( BoundingControllerPtr object , int type );

private:
	//������ײϵͳ����ײʵ��
	void Update();

	//��һ����Χ����뵽��ײϵͳ��
	void AddBoundingSphere( BoundingSphere * boundingSphere, int type, BoundingControllerPtr object );

	//��һ����Χ����뵽��ײϵͳ��
	void AddBoundingRectangle( BoundingRectangle * boundingRectangle, int type, BoundingControllerPtr object  );

	//�򵥵İ�Χʵ�����
	bool TestWithBoundingEntity( BoundingEntity * entity1, BoundingEntity * entity2 );

	//�򵥵İ�Χ��������
	bool TestBoundingSphereWithRectangle( BoundingSphere * sphere, BoundingRectangle * rectangle );

	//�򵥵İ�Χ�����
	bool TestBoundingSphereWithSphere( BoundingSphere * sphere1, BoundingSphere * sphere2 );

	//�򵥵İ�Χ�����
	bool TestBoundingRectangleWithRectangle( BoundingRectangle * rect1, BoundingRectangle * rect2 );
  
	//���Ķ������������ײ����
	bool TestPolygonWithPolygon( const Polygon2D * polygon1, const Polygon2D * polygon2 );
	
	//���Ķ�����������ײ����
	bool TestPolygonWithRectangle( const Polygon2D * polygon, const Rectangle2D * rect );

	//���ľ����������ײ����
	bool TestRectangleWithRectangle( const Rectangle2D * rect1, const Rectangle2D * rect2 );

	//������ͼ�β���
	bool TestWithGraph( const Graph * graph1, const Graph * graph2 );

	//������ƶ�ʵ����������б�
	void ComputeTestList( BoundingSphere * sphere, deque< BoundingList >& testList );

	//������ƶ�ʵ����������б�
	void ComputeTestList( BoundingRectangle * rectangle, deque< BoundingList >& testList );

	void LimitBoundingRange( int& min_x, int& max_x, int& min_y, int& max_y );

	//�򵥵İ�Χ�������ײ����
	bool TestWithBoundingSide( BoundingEntity * pEntity );

	//�򵥵İ�Χ�������ײ����
	bool TestBoundingSphereWithBoundingSide( BoundingSphere * pEntity );

	//�򵥵İ�Χ�������ײ����
	bool TestBoundingRectangleWithBoundingSide( BoundingRectangle * pEntity );

	//���Ķ���������ײ����
	bool TestPolygonWithBoundingSide( const Polygon2D * polygon );
	
	//���Ķ���������ײ����
	bool TestRectangleWithBoundingSide( const Rectangle2D * rect );

	//������ͼ�β���
	bool TestGraphWithBoundingSide( const Graph * graph );

private:
	IntersectionBlock cells_[BLOCKMAX][BLOCKMAX];

	float perCellWidth_, perCellHeight_;

	float width_, height_; 
};

#endif	//end of IntersectionSystem.h