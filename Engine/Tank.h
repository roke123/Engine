#ifndef __TANK_H__
#define __TANK_H__

#include <DrawTool.h>
#include <InputSystem.h>
#include <BoundingObject.h>
#include <GraphType.h>
#include <Default.h>
#include <IntersectionSystem.h>

#include "Bullet.h"

class Map;

class Tank
{
	REGISTER_CONTROLLER( TankInputControl );
	REGISTER_CONTROLLER( TankBoundingObject );

	friend class Bullet;
public:
	Tank() : inputController_(0), boundingController_(0),
		bullet_( new Bullet ), rect_(0)
	{
		IsBounding_ = false;
		memset( imageSet_, 0, sizeof(imageSet_) );
	}

	~Tank()
	{
		ShutDown();
	}

	void Fire();
	
	bool Init( DrawTool * drawTool, int x, int y, Map * map );

	void Draw( DrawTool * drawTool );

	void ShutDown();

	bool IsAlive() { return iHp_ > 0; }
	
	void SetHurt( int hurt ) { iHurt = hurt; }

	void AddHp() { ++ iHp_; }

//////////////////////////////////////////////����//////////////////////////////////////////////

private:
// ��������
	// �˺�ֵ
	int iHurt;

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
	// ���������
	InputControllerPtr inputController_;
	// ��ײ������
	BoundingControllerPtr boundingController_;
};

#endif	// end of tank.h