#include "SwapChain2D.h"
#include "GlobalFunction.h"
#include <assert.h>

SwapChain2D::SwapChain2D() : d2dFactory_(0), drawState(SC_DRAWEND),
	drawTool_(0)
{
	
}

SwapChain2D::~SwapChain2D()
{
	ShutDown();
}

bool SwapChain2D::Init( int num, HWND hWnd, RECT rc, int frameNum )
{
	assert( num > 0 );
	assert( frameNum > 0 );

	HRESULT result = 0;

	result = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&d2dFactory_ );

	if( FAILED( result ) )
	{
		MessageBox( 0, "failed to create D2DFactory", 0, 0 );
		return false;
	}
	
	frameRate_ = 1000 / frameNum;
	lastFrameTime_ = GetTickClock();

	//Direct2D����ĳ��ID2DHwndRenderTarget������ͼ��ֻ�������Լ�����
	//��˲��ܴ������ID2DHwndRenderTarget�����л�
	num = 1;

	//����num���л�����
	ID2D1HwndRenderTarget * tempTarget = 0;
	for( int i = 0; i < num; ++ i )
	{
		width_ = rc.right - rc.left;
		height_ = rc.bottom - rc.top;

		D2D1_SIZE_U pixelSize = D2D1::Size( width_, height_ );

		result = d2dFactory_->CreateHwndRenderTarget( D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties( hWnd,  pixelSize),
			&tempTarget );

		if( FAILED( result ) )
		{
			MessageBox( 0, "Can't create a 2d swapchain", 0, 0 );
			ShutDown();
			return false;
		}

		renderTargetList_.push_back( tempTarget );
	}

	curPoint_ = renderTargetList_.begin();

	drawTool_ = new D2DDrawTool( this );
	if( drawTool_ == NULL )
	{
		MessageBox( 0, "can't create draw tool", 0, 0 );
		return false;
	}

	drawTool_->Init();

	return true;
}

void SwapChain2D::BeginDraw()
{
	if( drawState == SC_DRAWEND )
	{
		(*curPoint_)->BeginDraw();
		drawState = SC_DRAWBEGIN;
	}
}

DrawTool * SwapChain2D::GetDrawTool()
{
	return drawTool_;
}

void SwapChain2D::WaitFrame()
{
	while( GetTickClock() - lastFrameTime_ < frameRate_ )
	{
		//����;
	}
}

HRESULT SwapChain2D::Flip()
{
	HRESULT result = 0;

	//WaitFrame();
	
	result = (*curPoint_)->EndDraw();
	if( FAILED( result ) )
	{
		return result;
	}

	if( ++ curPoint_ == renderTargetList_.end() )
	{
		curPoint_ = renderTargetList_.begin();
	}

	drawState = SC_DRAWEND;

	lastFrameTime_ = GetTickClock();

	return result;
}

void SwapChain2D::ShutDown()
{
	if( drawTool_ != 0 ) drawTool_->ShutDown();
	if( d2dFactory_ != 0 ) d2dFactory_->Release();

	drawTool_ = 0;
	d2dFactory_ = 0;

	SwapPoint tempSwapPoint = renderTargetList_.begin();
	for( ; tempSwapPoint != renderTargetList_.end(); ++ tempSwapPoint )
	{
		(*tempSwapPoint)->Release();
	}
	renderTargetList_.clear();

	drawState = SC_DRAWEND;
}
