#ifndef __SWAPCHAIN2D_H__
#define __SWAPCHAIN2D_H__

#include <d2d1.h>
#include <DWrite.h>
#include <deque>
using namespace std;
#include "D2DDrawTool.h"

enum SWAP_CHAIN_DRAW_STATE
{
	SC_DRAWBEGIN = 0,
	SC_DRAWEND = 1
};

class SwapChain2D
{
public:
	SwapChain2D();
	~SwapChain2D();

	//��ʼ��2D������
	bool Init( int num, HWND hWnd, RECT rc, int frameNum );

	void BeginDraw();

	//ȡ�û�ͼ����
	DrawTool * GetDrawTool();

	//��Ⱦ���л�����һ����
	HRESULT Flip();

	ID2D1HwndRenderTarget * GetCurRenderTarget() 
	{
		return * curPoint_;
	}

	void ShutDown();

private:
	//�ȴ���һ֡�ĵ���
	void WaitFrame();

private:
	ID2D1Factory * d2dFactory_;

	DrawTool * drawTool_;

	UINT width_, height_;

	//ÿ��֡��
	int frameRate_;

	//���һ֡��ʱ��
	long lastFrameTime_;

	//�Ƿ���BeginDraw�ı�־
	UINT drawState; 

	deque< ID2D1HwndRenderTarget * > renderTargetList_;

	typedef deque< ID2D1HwndRenderTarget * >::iterator SwapPoint;
	SwapPoint curPoint_;
	
};

#endif	//end of SwapChain2D.h