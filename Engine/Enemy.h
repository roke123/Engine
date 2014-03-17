#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <DrawTool.h>
#include <GraphType.h>
#include <Default.h>
#include <TimeSystem.h>
#include <IntersectionSystem.h>

#include "Bullet.h"

class Map;

class Enemy
{
	REGISTER_CONTROLLER( EnemyTimeControl );
	REGISTER_CONTROLLER( EnemyBoundingController );
public:
	Enemy() : timeController_(0), boundingController_(0),
		bullet_( new Bullet ), rect_(0), isReset_(false)
	{
		IsBounding_ = false;
		resetBounding_ = false;
		memset( imageSet_, 0, sizeof(imageSet_) );
	}

	~Enemy()
	{
		ShutDown();
	}

	void Fire();
	
	bool Init( DrawTool * drawTool, Rect_F rect, Map * map );

	void Draw( DrawTool * drawTool );

	void ShutDown();

	bool IsAlive() { return iHp_ > 0; }

	void Reset();

	void SetHurt( int hurt ) { iHurt = hurt; }

	void AddHp() { ++ iHp_; }

//////////////////////////////////////////////����//////////////////////////////////////////////

// ��������

	// �˺�ֵ
	int iHurt;

	bool isReset_;

	bool resetBounding_;

	// Hp
	int iHp_;

	// ��ǰǰ������
	int direction_;

	BulletPtr bullet_;

	// �ٶ�ֵ
	float speedX_;
	float speedY_;

	// �Ƿ���ײ���
	bool IsBounding_;

	Map * map_;
	DrawTool * drawTool_;

// ��ͼ����
	// ��ǰʹ��ͼƬ
	ImageType * curImage_;

	// Ԥ����ͼƬ��
	ImageType * imageSet_[4];
	
	// ��ʾTank�ľ���
	Rectangle2D * rect_;

//������
	// ʱ�������
	TimeControllerPtr timeController_;
	BoundingControllerPtr boundingController_;
};

typedef shared_ptr<Enemy> EnemyPtr;

#endif	// end of tank.h