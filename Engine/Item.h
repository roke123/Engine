#ifndef __ITEM_H__
#define __ITEM_H__

#include <Default.h>
#include <DrawTool.h>
#include <IntersectionSystem.h>

enum EITME_TYPE
{
	EIT_SHOVEL,
	EIT_LIFE,
};

class Item
{
	REGISTER_CONTROLLER( ItemBoundingController );
public:
	Item() : boundingObject_(0), rectangle_(0), image_(0),
		iHp_(0), isInit_(false)
	{
		//留空
	}

	bool IsInit() { return isInit_; }

	bool IsAlive() { return iHp_ > 0; }

	bool Init( DrawTool * drawTool, Rect_F& rect, int type, ImageType * image );

	void Draw( DrawTool * drawTool );

	void ShutDown();

////////////////////////////////////////////////属性/////////////////////////////////////////
private:
// 基本属性
	// Hp
	int iHp_;

	int type_;

	bool isInit_;

// 绘图属性
	Rectangle2D * rectangle_;
	ImageType * image_;

// 控制器属性
	BoundingControllerPtr boundingObject_;
};

#endif	// end of Item.h