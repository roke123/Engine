#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <Default.h>
#include <DrawTool.h>
#include <IntersectionSystem.h>

const int MAXHP = 99999999;

enum MAPBLOCK
{
	MB_BRICK,
	MB_GRASS,
	MB_SEA,
	MB_ICE,
	MB_STONE,
	MB_HERO,
	MB_ENEMY,
	MB_HOME,
	MB_ITEM,
	MB_BLACK,
};

class Block
{
	REGISTER_CONTROLLER( BlockBoundingHandler );
public:
	Block() : boundingObject_(0), rectangle_(0), image_(0),
		iHp_(0)
	{
		//����
	}

	bool IsAlive() { return iHp_ > 0; }

	bool Init( DrawTool * drawTool, Rect_F& rect, MAPBLOCK type, ImageType * image );

	void Draw( DrawTool * drawTool );

	void ShutDown();

	MAPBLOCK GetType() { return type_; }

////////////////////////////////////////////////����/////////////////////////////////////////
private:
// ��������
	// Hp
	int iHp_;

	MAPBLOCK type_;

// ��ͼ����
	Rectangle2D * rectangle_;
	ImageType * image_;

// ����������
	BoundingControllerPtr boundingObject_;
};

#endif	// end of Block.h