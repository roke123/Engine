#ifndef __BULLET_H__
#define __BULLET_H__

#include <TimeSystem.h>
#include <GraphType.h>
#include <Default.h>
#include <DrawTool.h>
#include <IntersectionSystem.h>


class BulletTimeControl;
class Tank;
class Enemy;

class Bullet
{
	REGISTER_CONTROLLER( BulletTimeControl );
	REGISTER_CONTROLLER( BulletBoundingControl );
public:
	Bullet() : tank_(0), rect_(0), timeController_(0),
		boundingController_(0), image_(0)
	{
	}

	~Bullet()
	{
		ShutDown();
	}

	bool Init( Tank * tank, DrawTool * drawTool );

	bool Init( Enemy * enemy, DrawTool * drawTool );

	void Draw( DrawTool * drawTool );

	void ShutDown();

	bool IsBounding()
	{
		return isBounding_;
	}

	int GetHurt() { return hurt_; }

	Tank * GetTank() { return tank_; }
	Enemy * GetEnemy() { return enemy_; }

public:
	
// ��������
	// �󶨵�̹��
	Tank * tank_;

	Enemy * enemy_;

	// �ٶ�
	float speedX_, speedY_;

	// �˺�ֵ
	int hurt_;

	// �Ƿ��Ѿ���ײ�ı��
	bool isBounding_;

// ��ͼ����
	Rectangle2D * rect_;
	ImageType * image_;

// ����������
	TimeControllerPtr timeController_;

	BoundingControllerPtr boundingController_;
};

typedef shared_ptr<Bullet> BulletPtr;

#endif	// end of Bullet.h