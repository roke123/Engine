#include "D2DDrawTool.h"
#include "GlobalFunction.h"

#include <fstream>
using namespace std;

D2DDrawTool::D2DDrawTool( SwapChain2D * swapChain )
	: DrawTool(), swapChain_( swapChain )
{

}

D2DDrawTool::~D2DDrawTool()
{
	ShutDown();
}


bool D2DDrawTool::Init() 
{
	//Rectangle2D * rc = 0;
	//Vertex2D_F begin = { 0.0f, 0.0f };
	//CreateRectangle2D( begin, swapChain_->width_,
	//	swapChain_->height_, &rc );

	//CreateRectangleClipFilter( *rc, screenClipFilter_ );

	HRESULT result = DWriteCreateFactory (
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&pDWriteFactory_)
    );

	if( FAILED(result) )
	{
		MessageBox( 0, "Can't create IDWriteFactory", 0, 0 );
		return false;
	}

	result = pDWriteFactory_->CreateTextFormat(
        L"Chinese",                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        20.0f,
        L"zh-cn",
        &pTextFormat_
    );

	if( SUCCEEDED( result ) )
	{
		result = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	if( SUCCEEDED( result ) )
	{
		result = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	//delete rc;

	return DrawTool::Init();
}

void D2DDrawTool::ShutDown()
{
	DrawTool::ShutDown();
}

/////////////////////////////////////////////////////////override//////////////////////////////////////////////////////////////

int D2DDrawTool::DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1, const Color_F& c ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	Vertex2D_F start = p0, end = p1;

	//为保证速度把create bruh的错误检测关闭
	ID2D1SolidColorBrush * brush;
	renderTarget->CreateSolidColorBrush( c, &brush );

	//基于图像空间裁剪直线
	screenClipFilter_->ClipLine( start, end );

	renderTarget->DrawLine( start, end, brush );

	brush->Release();

	return 1;
}

void D2DDrawTool::DrawLine( const Vertex2D_F& p0, const Vertex2D_F& p1,
			  ID2D1SolidColorBrush * brush ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	Vertex2D_F start = p0, end = p1;

	//基于图像空间裁剪直线
	screenClipFilter_->ClipLine( start, end );

	renderTarget->DrawLine( start, end, brush );

}

int D2DDrawTool::DrawPolygon( const Polygon2D& polygon, const Color_F& c ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	//为保证速度把create bruh的错误检测关闭
	ID2D1SolidColorBrush * brush;
	renderTarget->CreateSolidColorBrush( c, &brush );

	Vertex2D_F prevVertex = polygon.worldVertexFirst;
	for( int i = 1; i < polygon.numVertex_; ++ i )
	{
		renderTarget->DrawLine( prevVertex, polygon.worldVertexArray_[i], brush );
		prevVertex = polygon.worldVertexArray_[i];
	}//end for

	renderTarget->DrawLine( prevVertex, polygon.worldVertexArray_[0], brush );

	return 1;
}


void D2DDrawTool::Clear( const Color_F& color ) const
{
	swapChain_->GetCurRenderTarget()->Clear( color );
}

void D2DDrawTool::DrawSolidTopTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, ID2D1SolidColorBrush * brush ) const
{
	float dl = (p1.x - p3.x) / (p1.y - p3.y) * 0.5f,
		dr = (p2.x - p3.x) / (p2.y - p3.y) * 0.5f;

	Vertex2D_F start = p1, end = p2;
	
	int dir = (int) (p3.y + 0.5f) * 2, i = (int) (p1.y + 0.5f) * 2;
	for( ; i < dir; ++ i )
	{
		DrawLine( start, end, brush );
		start.x += dl, start.y += 0.5f;
		end.x += dr, end.y += 0.5f;
	}
}

void D2DDrawTool::DrawSolidButtonTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, ID2D1SolidColorBrush * brush ) const
{
	float dl = (p1.x - p2.x) / (p1.y - p2.y) * 0.5f,
		dr = (p1.x - p3.x) / (p1.y - p3.y) * 0.5f;

	Vertex2D_F start = p1, end = p1;
	
	int dir = (int) (p3.y + 0.5f) * 2, i = (int) (p1.y + 0.5f) * 2;
	for( ; i < dir; ++ i )
	{
		DrawLine( start, end, brush );
		start.x += dl, start.y += 0.5f;
		end.x += dr, end.y += 0.5f;
	}
}

void D2DDrawTool::DrawSolidTriangle( const Vertex2D_F& p1, const Vertex2D_F& p2,
		const Vertex2D_F& p3, const Color_F& color ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	//为保证速度把create bruh的错误检测关闭
	ID2D1SolidColorBrush * brush;
	renderTarget->CreateSolidColorBrush( color, &brush );

	if( p1.y == p2.y && p2.y == p3.y )
	{
		Vertex2D_F start = p1, end = p1;

		if( p2.x > p1.x )
		{
			start.x = p2.x;
		} else {
			end.x = p2.x;
		}

		if( p3.x > start.x )
		{
			start.x = p3.x;
		} else if( p3.x < end.x ) {
			end.x = p3.x;
		}
		
		DrawLine( start, end, color );
		return;
	}

	if( p1.y == p2.y )
	{
		if( p3.y < p1.y )
			DrawSolidButtonTriangle( p3, p1, p2, brush );
		else
			DrawSolidTopTriangle( p1, p2, p3, brush );
	} else if ( p2.y == p3.y ) {
		if( p1.y < p3.y )
			DrawSolidButtonTriangle( p1, p2, p3, brush );
		else
			DrawSolidTopTriangle( p3, p2, p1, brush );
	} else {
		Vertex2D_F temp1 = p1, temp2 = p2,
			temp3 = p3, temp4 = p1;
		
		if( temp2.y < temp1.y )
			swap( temp1, temp2 );

		if( temp3.y < temp1.y )
			swap( temp1, temp3 );

		if( temp3.y < temp2.y )
			swap( temp3, temp2 );

		//计算中断点
		float dx = (temp1.x - temp3.x) / (temp1.y - temp3.y);
		temp4.x += (temp2.y - temp1.y) * dx;
		temp4.y = temp2.y;

		DrawSolidButtonTriangle(temp1, temp2, temp4, brush);
		DrawSolidTopTriangle(temp2, temp4, temp3, brush);
	}
}

void D2DDrawTool::DrawSolidPolygon( const Polygon2D& polygon, const Color_F& color ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	//为保证速度把create bruh的错误检测关闭
	ID2D1SolidColorBrush * brush;
	renderTarget->CreateSolidColorBrush( color, &brush );

	int numVertex = polygon.numVertex_;
	Vertex2D_F * * vertics = new Vertex2D_F * [ numVertex ];
	vertics[0] = polygon.worldVertexArray_;

	int max = 0;
	for( int i = 0; i < numVertex; ++ i )
	{
		if( polygon.worldVertexArray_[i].y < polygon.worldVertexArray_[max].y )
			max = i;
	}

	for( int i = 0; i < numVertex - max; ++ i )
	{
		vertics[i] = polygon.worldVertexArray_ + max + i;
	}

	int offsize = numVertex - max;
	for( int i = 0; i < max; ++ i )
	{
		vertics[i + offsize] = polygon.worldVertexArray_ + i;
	}

	Vertex2D_F temp = *vertics[0], start = *vertics[0],
		end = *vertics[0];

	int prev = 1, back = numVertex - 1;

	while( prev <= back )
	{
		float dl = (start.x - vertics[prev]->x) / (start.y - vertics[prev]->y) * 0.5f,
			dr = (end.x - vertics[back]->x) / (end.y - vertics[back]->y) * 0.5f;

		//特殊情况1：最后两点平底，即最后一次不需再画
		if( fabs(end.y - vertics[back]->y) < 0.00000001f )
			break;

		//特殊情况2：最初两点平顶，会漏画一个三角形
		if( fabs(start.y - vertics[prev]->y) < 0.0000001f ) {
			DrawSolidTopTriangle( start, *vertics[prev], *vertics[prev + 1], brush );
			++ prev;
			continue;
		}

		int j = (int)(start.y + 0.5) * 2, dir = 0; 
		if( vertics[prev]->y > vertics[back]->y )
		{
			dir = (int)(vertics[back]->y + 0.5f) * 2;
			-- back;
		}
		else
		{
			dir = (int)(vertics[prev]->y + 0.5f) * 2;
			++ prev;
		}
	
		for( ; j < dir; ++ j )
		{
			DrawLine( start, end, brush );
			start.x += dl, start.y += 0.5f;
			end.x += dr, end.y += 0.5f;
		}
	}
}

void D2DDrawTool::DrawSolidRectangle( const Rectangle2D& rectangle, const Color_F& color ) const
{
	Vertex2D_F temp1 = rectangle.worldVertex0, temp2 = rectangle.worldVertex1;
	temp2.y = rectangle.worldVertex0.y;

	int start = (int)(rectangle.worldVertex0.y + 0.5f) * 2, end = (int)(rectangle.worldVertex1.y + 0.5f) * 2;

	for( ; start < end; ++ start )
	{
		DrawLine( temp1, temp2, color );
		temp1.y += 0.5f;
		temp2.y += 0.5f;
	}
}

HRESULT D2DDrawTool::CreateImageFromFile( const wstring filename, ImageType ** image ) const
{
	HRESULT result = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC,
		IID_IWICImagingFactory,
		(void **)(&wicFactory_)
	);

	if( FAILED(result) )
	{
		MessageBox( 0, "Can't create wicfactory", 0, 0 );
		return false;
	}

	IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pSource = NULL;
    IWICStream *pStream = NULL;
    IWICFormatConverter *pConverter = NULL;
    IWICBitmapScaler *pScaler = NULL;

	result = wicFactory_->CreateDecoderFromFilename( filename.c_str(),
		NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
	);

	if( SUCCEEDED(result) )
    {
        // Create the initial frame.
        result = pDecoder->GetFrame(0, &pSource);
    }

	if( SUCCEEDED( result ) )
    {

        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        result = wicFactory_->CreateFormatConverter( &pConverter );
    }

	if ( SUCCEEDED( result ) )
    {
        result = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeMedianCut
            );
    }

	ID2D1Bitmap * temp;
	if( SUCCEEDED( result ) )
    {
		ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();
        // Create a Direct2D bitmap from the WIC bitmap.
		result = renderTarget->CreateBitmapFromWicBitmap(
            pConverter,
            NULL,
			&temp
		);
    }

	if( SUCCEEDED( result ) )
    {
		ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();
        // Create a Direct2D bitmap from the WIC bitmap.
		result = renderTarget->CreateSharedBitmap(
			IID_ID2D1Bitmap,
            temp,
            NULL,
			image
		);
    }

	if( pDecoder ) pDecoder->Release();
    if( pSource ) pSource->Release();
    if( pStream ) pStream->Release();
    if( pConverter ) pConverter->Release();
    if( pScaler ) pScaler->Release();
	if( wicFactory_ ) wicFactory_->Release();

    return result;
}

void D2DDrawTool::DrawImage( ImageType& image, const Rect_F& destination, float alpha ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	D2D1_RECT_F temp;
	temp.top = destination.y0;
	temp.left = destination.x0;
	temp.bottom = destination.y1;
	temp.right = destination.x1;

	renderTarget->DrawBitmap( &image, temp, alpha, 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR );
}

void D2DDrawTool::DrawImage( ImageType& image, const Rect_F& destination, const Rect_F& source,
	float alpha ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	D2D1_RECT_F temp;
	temp.top = destination.y0;
	temp.left = destination.x0;
	temp.bottom = destination.y1;
	temp.right = destination.x1;

	renderTarget->DrawBitmap( &image, temp, alpha, 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR );
}

HRESULT  D2DDrawTool::CreateImageFormImage( const Rect_U& rect, ImageType * inImage, ImageType ** outImage ) const
{
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	D2D1_BITMAP_PROPERTIES properties;
	properties.pixelFormat= inImage->GetPixelFormat();
	inImage->GetDpi( &properties.dpiX, &properties.dpiY );

	D2D1_SIZE_U size = { abs(rect.x1 - rect.x0),
		abs(rect.y0 - rect.y1 ), };
	D2D1_POINT_2U zeroPoint = { 0 };
	D2D1_RECT_U rc;
	rc.left = rect.x0, rc.top = rect.y0;
	rc.right =rect.x1, rc.bottom = rect.y1;

	renderTarget->CreateBitmap( size, properties, outImage );

	return (*outImage)->CopyFromBitmap(
			&zeroPoint,
			inImage,
			&rc
			);
}

HRESULT D2DDrawTool::DrawString( const wchar_t * str, Rect_F rc, Color_F color )
{
	HRESULT result = 0;
	ID2D1HwndRenderTarget * renderTarget = swapChain_->GetCurRenderTarget();

	ID2D1SolidColorBrush * pBlackBrush = NULL;
	result = renderTarget->CreateSolidColorBrush(
		color,
		&pBlackBrush
	);

	if( FAILED( result ) )
		return result;

	D2D1_RECT_F layoutRect = D2D1::RectF(
		rc.x0, rc.y0, rc.x1, rc.y1
    );

	renderTarget->DrawText(
		str,
		wcslen( str ),
		pTextFormat_,
		layoutRect,
		pBlackBrush 
	);

	return S_OK;
}

HRESULT D2DDrawTool::SetTextFormat( const wchar_t * familyName, float fontSize,
								   const wchar_t * localName )
{
	pTextFormat_->Release();

	HRESULT result = pDWriteFactory_->CreateTextFormat(
        familyName,                // Font family name.
        NULL,                       // Font collection (NULL sets it to use the system font collection).
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        fontSize,
        localName,
        &pTextFormat_
    );

	return result;
}


/////////////////////////////////////////////////////end of override//////////////////////////////////////////////////////////
