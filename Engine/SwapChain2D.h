#ifndef __SWAPCHAIN2D_H__
#define __SWAPCHAIN2D_H__

#include <d2d1.h>
#include <deque>
using namespace std;
#include "D2DDrawTool.h"

enum SWAP_CHAIN_DRAW_STATE
{
	SC_DRAWBEGIN = 0,
	SC_DRAWEND = 1
};

class D2DDrawTool;

class SwapChain2D : public RefObject
{
//声明友元类
friend class D2DDrawTool;

public:
	SwapChain2D();
	~SwapChain2D();

	//初始化2D交换链
	bool Init( ID2D1Factory * d2dFactory, int num, HWND hWnd, RECT rc, int frameNum );

	//取得绘图工具
	DrawTool * GetDrawTool();

	//渲染并切换到下一缓存
	HRESULT Flip();

	void ShutDown();

private:
	//等待下一帧的到来
	void WaitFrame();

private:
	ID2D1Factory * d2dFactory_;

	DrawTool * drawTool_;

	UINT width_, height_;

	//每秒帧率
	int frameRate_;

	//最后一帧的时间
	long lastFrameTime_;

	//是否已BeginDraw的标志
	UINT drawState; 

	deque< ID2D1HwndRenderTarget * > renderTargetList_;

	typedef deque< ID2D1HwndRenderTarget * >::iterator SwapPoint;
	SwapPoint curPoint_;
	
};

#endif	//end of SwapChain2D.h