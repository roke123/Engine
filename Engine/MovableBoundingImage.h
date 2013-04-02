#ifndef __MOVABLEBOUNDINGIMAGE_H__
#define __MOVABLEBOUNDINGIMAGE_H__

#include "GraphType.h"
#include "IntersectionSystem.h"
#include "SwapChain2D.h"
#include "GlobalFunction.h"

#include <string>
using namespace std;

class MovableBoundingImage
{
public:
	void Init( IntersectionSystem * system, SwapChain2D * swap )
	{
		drawTool_ = swap->GetDrawTool();
		drawTool_->CreateImageFromFile( imageName_, &image_ );
		system->CreateBoundingRectangle( *rect_, MOVABLE );
	}

	void SetWorldMatrix( const Matrix3x3_F& worldMatrix )
	{
		worldMatrix_ = worldMatrix;
	}

	void Draw()
	{
		SetMatrix( rect_, worldMatrix_ );
		drawTool_->DrawImage( *image_, rect_->worldRect, 1.0f );
	}

	~MovableBoundingImage()
	{
		image_->Release();
		delete rect_;
	}

public:
	DrawTool * drawTool_;

	wstring imageName_;
	ImageType * image_;
	Rectangle2DType * rect_;
	Matrix3x3_F worldMatrix_;
};

#endif	//end of MovableBoundingImage.h