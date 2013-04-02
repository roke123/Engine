#include "TestWin.h"
#include "GlobalFunction.h"

TestWin::TestWin( ) : hInstance_(0), hWnd_(0), d2dFactory_(0),
	isOpenClipFilter(true), polygon(0), rectangle(0)
{
	MyFactory * myFactory = MyFactory::GetMyFactory();

	transform = myFactory->CreateIdentityMatrix3x3();
	rotation = myFactory->CreateIdentityMatrix3x3();
	scale = myFactory->CreateIdentityMatrix3x3();
}

TestWin::~TestWin()
{
	WinShutDown();
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
	case WM_DESTROY :
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}

bool TestWin::WinInit( HINSTANCE hInstance, int width, int height, bool isWindow )
{
	WNDCLASSEX wndClass = { 0 };
    wndClass.cbSize = sizeof( WNDCLASSEX ) ;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
    wndClass.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = "TestWin";

	HRESULT result = 0;

	if( !RegisterClassEx( &wndClass ) )
	{
		MessageBox( 0, "Can't register a window", 0, 0 );
		return false;
	}

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

	HWND hWnd_ = CreateWindow( "TestWin", 0, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT
		, rc.right - rc.left,rc.bottom - rc.top, 0, 0, hInstance, 0 );

	if( !hWnd_ )
	{
		MessageBox( 0, "Can't Create a window", 0, 0 );
		return false;
	}

	ShowWindow( hWnd_, SW_SHOW );

	hInstance_ = hInstance;

	result = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&d2dFactory_ );

	if( FAILED( result ) )
	{
		MessageBox( 0, "Can't create 2d factory", 0, 0 );
		return false;
	}

	if( !swapChain2d_.Init( d2dFactory_, 1, hWnd_, rc, 60 ) )
	{
		MessageBox( 0, "Can't create a swap chain", 0, 0 );
		return false;
	}

	inputSystem_.Init( hInstance, hWnd_ );
	intersectionSystem_.Init( (float)width, (float)height );

    return LoadContent( );
}

void TestWin::UnloadContent( )
{
	if( polygon ) delete polygon;
	if( rectangle ) delete rectangle;
	if( image ) delete image;
	if( image1 ) delete image1;
	if( animationGroup_ ) delete animationGroup_;
}

bool TestWin::LoadContent( )
{
	Vertex2D_F p1, p2;
	p1.x = 0.0f, p1.y = 0.0f;
	p2.x = 600.0f, p2.y = 600.0f;
	
	DrawTool * drawTool = swapChain2d_.GetDrawTool();
	/*if( isOpenClipFilter )
	{		
		Vertex2D_F clip_p0, clip_p1;
		clip_p0.x = 100.0f, clip_p0.y = 100.f;
		clip_p1.x = 500.0f, clip_p1.y = 500.f;

		Rectangle2DType * rect = NULL;
		myFactory->CreateRectangle2D( clip_p0, clip_p1, rect );

		ClipFilter * clipFilter = 0;
		if( !myFactory->CreateRectangleClipFilter( *rect, clipFilter ) )
		{
			MessageBox( 0, "Can't create a rectangle clip filter", 0, 0 );
			return;
		}

		clipFilter->ClipLine( p1, p2 );

		delete clipFilter;
		delete rect;
	}*/

	/*drawTool->DrawLine( p1, p2, color ); */
	Vertex2D_F rect1[] =
	{
		{ 300.0f, 300.0f },
		{ 500.0f, 500.0f }
	};

	image1 = new MovableBoundingImage;
	image1->imageName_ = L"1.jpg";
	drawTool->CreateRectangle2D( rect1[0], rect1[1], &image1->rect_ );
	image1->Init( &intersectionSystem_, &swapChain2d_ );

	/*Vertex2D_F vertice[] = 
	{
		{200.0f, 400.0f},
		{68.5f, 166.3f},
		{150.0f, 150.0f},
		{620.0f, 473.0f},
		
	};

	int numVertex = ARRAYSIZE( vertice );

	if( !drawTool->CreatePolygon2D( vertice, numVertex, &polygon ) )
	{
		MessageBox( 0, "Can't create rectangle", 0, 0 );
		return false;
	}

	intersectionSystem_.CreateBoundingSphere( *polygon, MOVABLE );*/

	Vertex2D_F rect[] =
	{
		{ 50.0f, 50.0f },
		{ 100.0f, 100.0f }
	};

	int numVertex = ARRAYSIZE( rect );

	if( !drawTool->CreateRectangle2D( rect[0], rect[1], &rectangle ) )
	{
		MessageBox( 0, "Can't create polygon", 0, 0 );
		return false;
	}

	intersectionSystem_.CreateBoundingRectangle( *rectangle, UNMOVABLE );

	if( FAILED( drawTool->CreateImageFromFile( L"1.jpg", &image ) ) )
	{
		MessageBox( 0, "Can't create image", 0, 0 );
		return false;

	}

	Rect_F rect2;
	rect2.x0 = 200.0f, rect2.y0 = 200.0f;
	rect2.x1 = 300.0f, rect2.y1 = 300.0f;
	
	drawTool->CreateAnimationGroupWithFile( L"a.txt", rect2, animationGroup_ );
	animationGroup_->SetAnimation( "MOVE", 1 );
	
	return true;
}

void TestWin::WinRender()
{
	DrawTool * drawTool = swapChain2d_.GetDrawTool();
	drawTool->Clear();  

	Matrix3x3_F worldMatrix = scale * rotation * transform;

	image1->SetWorldMatrix( worldMatrix );
	image1->Draw();
	/*SetMatrix( polygon, worldMatrix );*/

	Color_F color = { 255.0f, 255.0f, 255.0f, 1.0f };

	//drawTool->DrawSolidPolygon( *polygon, color );

	drawTool->DrawSolidRectangle( *rectangle, color );

	animationGroup_->Run();

	/*Rect_F rect;
	rect.x0 = 50.0f, rect.y0 = 50.0f;
	image->GetDpi( &rect.x1, &rect.y1 );
	rect.x1 = rect.x1 + 50.0f, rect.y1 = rect.y1 + 50.0f;

	drawTool->DrawImage( *image, rect, 1.0f );*/

	//Vertex2D_F tri1 = { 50.0f, 50.0f },
	//	tri2 = { 100.0f, 50.0f },
	//	tri3 = { 150.0f, 100.0f };

	////drawTool->DrawSolidTriangle( tri1, tri2, tri3, color );

	//tri2.y = 100.0f;
	////drawTool->DrawSolidTriangle( tri1, tri2, tri3, color );

	//tri2.y = 200.0f;
	////drawTool->DrawSolidTriangle( tri1, tri2, tri3, color );

	//delete polygon;
	//delete rectangle;
	swapChain2d_.Flip();
}

void TestWin::WinShutDown()
{
	if( d2dFactory_ ) d2dFactory_->Release();

	d2dFactory_ = 0;
}

void TestWin::WinUpdate()
{
	if( GetAsyncKeyState( VK_ESCAPE ) )
	{
		PostQuitMessage(0);
	}

	if( inputSystem_.QueryKeyboard( DIK_A, KB_KEYDOWN ) )
	{
		if( isOpenClipFilter )
			isOpenClipFilter = false;
		else
			isOpenClipFilter = true;
	}

	static float rat = 0.0f,
		move_x = 0.0f, move_y = 0.0f,
		scale_x = 1.0f, scale_y = 1.0f;

	if( inputSystem_.QueryKeyboard( DIK_UP, KB_KEYPRESS ) )
	{
		move_y -= 2.0f;
	}

	if( inputSystem_.QueryKeyboard( DIK_DOWN, KB_KEYPRESS ) )
	{
		move_y += 2.0f;
	}

	if( inputSystem_.QueryKeyboard( DIK_LEFT, KB_KEYPRESS ) )
	{
		move_x -= 2.0f;
	}

	if( inputSystem_.QueryKeyboard( DIK_RIGHT, KB_KEYPRESS ) )
	{
		move_x += 2.0f;
	}

	if( inputSystem_.QueryKeyboard( DIK_ADD, KB_KEYPRESS ) )
	{
		scale_x += 0.5f;
		scale_y += 0.5f;
	}

	if( inputSystem_.QueryKeyboard( DIK_SUBTRACT, KB_KEYPRESS ) )
	{
		scale_x -= 0.5f;
		scale_y -= 0.5f;
	}

	if( inputSystem_.QueryKeyboard( DIK_R, KB_KEYPRESS ) )
	{
		rat += 0.5f;
	}

	if( inputSystem_.QueryKeyboard( DIK_B, KB_KEYPRESS ) )
	{
		rat -= 0.5f;
	}

	MyFactory * myFactory = MyFactory::GetMyFactory();

	transform = myFactory->CreateTransformMatrix3x3( move_x, move_y );
	rotation = myFactory->CreateRotationMatrix3x3( rat );
	scale = myFactory->CreateScaleMatrix3x3( scale_x, scale_y );

	/*if( keyboardKeys_[DIK_A] & 0x80 )
	{
		if( isOpenClipFilter )
			isOpenClipFilter = false;
		else
			isOpenClipFilter = true;
	}*/

	intersectionSystem_.Run();
	inputSystem_.Run();
}