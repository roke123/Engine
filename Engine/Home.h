#ifndef __HOME_H__
#define __HOME_H__

#include <Default.h>
#include <DrawTool.h>
#include <IntersectionSystem.h>

class Home
{
	REGISTER_CONTROLLER( HomeBoundingController );
public:
	Home() : boundingController_(0), rectangle_(0), image_(0)
	{
		//留空
	}

	bool IsAlive() { return isAlive_; }

	bool Init( DrawTool * drawTool, Rect_F& rect, ImageType * image );

	void Draw( DrawTool * drawTool );

	void ShutDown();

////////////////////////////////////////////////属性/////////////////////////////////////////
private:
// 基本属性
	bool isAlive_;

// 绘图属性
	Rectangle2D * rectangle_;
	ImageType * image_;

// 控制器属性
	BoundingControllerPtr boundingController_;
};

#endif	// end of Home.h