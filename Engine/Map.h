#ifndef __MAP_H__
#define __MAP_H__

#include <Image.h>
#include <DrawTool.h>
#include <fstream>
#include <time.h>

#include "Block.h"
#include "Tank.h"
#include "Bullet.h"
#include "Home.h"
#include "Enemy.h"
#include "Item.h"

class Map
{
public:
	Map()
	{
		memset( imageSet_, 0, sizeof(imageSet_) );
	}

	~Map()
	{
		ShutDown();
	}

	bool Init( DrawTool * drawTool, float width, float height )
	{
		memset( map_, 0, sizeof(char) * 1600 );
		drawTool->CreateImageFromFile( L"res/brick.bmp", &imageSet_[0] );
		drawTool->CreateImageFromFile( L"res/grass.bmp", &imageSet_[1] );
		drawTool->CreateImageFromFile( L"res/sea.bmp", &imageSet_[2] );
		drawTool->CreateImageFromFile( L"res/ice.bmp", &imageSet_[3] );
		drawTool->CreateImageFromFile( L"res/stone.bmp", &imageSet_[4] );
		drawTool->CreateImageFromFile( L"res/home.bmp", &imageSet_[5] );
		drawTool->CreateImageFromFile( L"res/shovel.bmp", &imageSet_[6] );
		drawTool->CreateImageFromFile( L"res/life.bmp", &imageSet_[7] );

		blockWidth_ = width / 20.0f;
		blockHeight_ = height / 20.0f;

		float x0 = 0.0f, y0 = 0.0f, x1 = blockWidth_, y1 = blockHeight_;

		for( int i = 0; i < 20; ++ i )
		{
			for( int j = 0; j < 20; ++ j )
			{
				blockRect_[i][j].x0 = x0;
				blockRect_[i][j].y0 = y0;
				blockRect_[i][j].x1 = x1;
				blockRect_[i][j].y1 = y1;

				x0 += blockWidth_;
				x1 += blockWidth_;
			}

			x0 = 0;
			x1 = blockWidth_;
			y0 += blockHeight_;
			y1 += blockHeight_;
		}

		return true;
	}

	bool LoadMap( const char * filename, DrawTool * drawTool )
	{
		using namespace std;

		brokenEnemy_ = 0;

		fstream file;
		file.open( filename, ios::in );

		if( !file.is_open() )
		{
			MessageBox( 0, "lose map file.", "Error", 0 );
			file.close();
			return false;
		}

		for( int i = 0; i < 20; ++i )
		{
			//读出一行信息
			file.read( map_[i], sizeof( char ) * 20 );
			//取出换行符
			file.get();
		}

		int x = 0, y = 0;
		homeRect_.x0 = homeRect_.y0 = 10000;
		homeRect_.x1 = homeRect_.y1 = 0;
		int itemCount_ = 0;
		lastItem_ = 0;

		for( int i = 0; i < 20; ++ i )
		{
			for( int j = 0; j < 20; ++ j )
			{
				// 转换字符为数值
				map_[i][j] -= 48;

				switch( map_[i][j] )
				{
					case MB_BRICK :
						blockSet_[i][j].Init( drawTool, blockRect_[i][j], MB_BRICK,
							imageSet_[0] );

						break;

					case MB_GRASS :
						blockSet_[i][j].Init( drawTool, blockRect_[i][j], MB_GRASS,
							imageSet_[1] );

						break;

					case MB_SEA :
						blockSet_[i][j].Init( drawTool, blockRect_[i][j], MB_SEA,
							imageSet_[2] );

						break;

					case MB_ICE :
						blockSet_[i][j].Init( drawTool, blockRect_[i][j], MB_ICE,
							imageSet_[3] );

						break;

					case MB_STONE :
						blockSet_[i][j].Init( drawTool, blockRect_[i][j], MB_STONE,
							imageSet_[4] );

						break;

					case MB_HERO :
						x = i, y = j;
						break;

					case MB_ENEMY :
					{
						EnemyPtr newEnemy( new Enemy );
						newEnemy->Init( drawTool, blockRect_[i][j], this );
						enemys_.push_back(newEnemy);
						break;
					}

					case MB_HOME :
						if( homeRect_.x0 >  blockRect_[i][j].x0 )
							homeRect_.x0 =  blockRect_[i][j].x0;
						if( homeRect_.y0 >  blockRect_[i][j].y0 )
							homeRect_.y0 =  blockRect_[i][j].y0;
						if( homeRect_.x1 <  blockRect_[i][j].x1 )
							homeRect_.x1 =  blockRect_[i][j].x1;
						if( homeRect_.y1 <  blockRect_[i][j].y1 )
							homeRect_.y1 =  blockRect_[i][j].y1;
						break;

					case MB_ITEM :
						itemRect_[itemCount_ ++] = blockRect_[i][j];
						break;
				}
			}
		}

		hero_.Init( drawTool, x, y, this );

		home_.Init( drawTool, homeRect_, imageSet_[5] );
		file.close();
		return true;
	}

	void Draw( DrawTool * drawTool )
	{
		if( !home_.IsAlive() )
			return;

		for( int i = 0; i < 20; ++ i )
		{
			for( int j = 0; j < 20; ++ j )
			{
				if( map_[i][j] < 5 )
				{
					if( blockSet_[i][j].IsAlive() )
						blockSet_[i][j].Draw( drawTool );
					else
					{
						blockSet_[i][j].ShutDown();
						map_[i][j] = 9;
					}
				}
			}
		}

		hero_.Draw( drawTool );

		list<EnemyPtr>::iterator enemyIte;
		for( enemyIte = enemys_.begin(); enemyIte != enemys_.end();
			++ enemyIte )
		{
			if( !(*enemyIte)->IsAlive() )
			{
				(*enemyIte)->Reset();		
			}
			else if( (*enemyIte)->isReset_ )
			{
				if( (*enemyIte)->resetBounding_ )
					(*enemyIte)->iHp_ = 0;
				else
				{
					srand(time(0));
					int r = rand() % 10;

					itemSet_[lastItem_].ShutDown();
					int type = rand() % 2;
					itemSet_[r].Init( drawTool, itemRect_[r], type, imageSet_[6 + type] );
					lastItem_ = r;
					(*enemyIte)->isReset_ = false;

					++ brokenEnemy_;
				}
			}
			else
				(*enemyIte)->Draw( drawTool );
		}

		home_.Draw( drawTool );

		list<BulletPtr>::iterator bulletIte = bullets_.begin();
		while( bulletIte != bullets_.end() )
		{
			if( !(*bulletIte)->IsBounding() )
				(*bulletIte)->Draw( drawTool );
			else
			{
				(*bulletIte)->ShutDown();
				bullets_.erase( bulletIte ++  );
				continue;
			}

			++ bulletIte;
		}

		for( int i = 0; i < 10; ++ i )
		{
			if( itemSet_[i].IsInit() )
			{
				itemSet_[i].Draw( drawTool );
				if( !itemSet_[i].IsAlive() )
					itemSet_[i].ShutDown();
			}
		}
	}

	void AddBullet( BulletPtr bullet )
	{
		bullets_.push_back(bullet);
	}

	bool IsEnd()
	{
		return !home_.IsAlive() || !hero_.IsAlive();
	}

	bool IsWin()
	{
		return brokenEnemy_ > 20;
	}

	void UnLoadMap()
	{
		for( int i = 0; i < 20; ++ i )
			for( int j = 0; j < 20; ++ j )
				if( map_[i][j] < 5 )
					blockSet_[i][j].ShutDown();

		itemSet_[lastItem_].ShutDown();
		home_.ShutDown();
		hero_.ShutDown();
		enemys_.clear();
		bullets_.clear();
	}

	void ShutDown()
	{
		UnLoadMap();
		for( int i = 0; i < 8; ++ i )
			if(	imageSet_[i] != 0 )
			{
				imageSet_[i]->Release();
				imageSet_[i] = 0;
			}
	}

	//以字符表示的地图数据
	char map_[20][20];
	//地图中每个格子Rect
	Rect_F blockRect_[20][20];
	//地图中的格子
	Block blockSet_[20][20];
	//地图中home的Rect
	Rect_F homeRect_;

	Rect_F itemRect_[10]; 
	Item itemSet_[10];
	int lastItem_;

	list<EnemyPtr> enemys_;

	// 基地
	Home home_;

	// 我方坦克
	Tank hero_;

	// 战场上出现的子弹
	list<BulletPtr> bullets_;
	
	int brokenEnemy_;

	float blockWidth_, blockHeight_;

	ImageType * imageSet_[8];
};

#endif	// end of Map.h