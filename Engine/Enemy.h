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

//////////////////////////////////////////////属性//////////////////////////////////////////////

// 基本属性

	// 伤害值
	int iHurt;

	bool isReset_;

	bool resetBounding_;

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
	// 时间控制器
	TimeControllerPtr timeController_;
	BoundingControllerPtr boundingController_;
};

typedef shared_ptr<Enemy> EnemyPtr;

#endif	// end of tank.h