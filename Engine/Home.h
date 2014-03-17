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
		//����
	}

	bool IsAlive() { return isAlive_; }

	bool Init( DrawTool * drawTool, Rect_F& rect, ImageType * image );

	void Draw( DrawTool * drawTool );

	void ShutDown();

////////////////////////////////////////////////����/////////////////////////////////////////
private:
// ��������
	bool isAlive_;

// ��ͼ����
	Rectangle2D * rectangle_;
	ImageType * image_;

// ����������
	BoundingControllerPtr boundingController_;
};

#endif	// end of Home.h