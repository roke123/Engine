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

//////////////////////////////////////////////属性//////////////////////////////////////////////

private:
// 基本属性
	// 伤害值
	int iHurt;

	// Hp
	int iHp_;

	// 当前前进方向
	int direction_;

	BulletPtr bullet_;

	// 速度值
	float speedX_;
	float speedY_;

	// 是否碰撞标记
	bool IsBounding_;

	Map * map_;
	DrawTool * drawTool_;

// 绘图属性
	// 当前使用图片
	ImageType * curImage_;

	// 预加载图片集
	ImageType * imageSet_[4];
	
	// 表示Tank的矩形
	Rectangle2D * rect_;

//控制器
	// 输入控制器
	InputControllerPtr inputController_;
	// 碰撞控制器
	BoundingControllerPtr boundingController_;
};

#endif	// end of tank.h