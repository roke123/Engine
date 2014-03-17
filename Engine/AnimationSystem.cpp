#include "AnimationSystem.h"
#include "AnimationBase.h"
#include <fstream>

AnimationSystem::AnimationSystem() : drawTool_( 0 )
{

}

AnimationSystem::~AnimationSystem()
{
	animationGroupList.clear();
}

bool AnimationSystem::CreateAnimationGroupWithFile( const wstring& filename,
		const Rect_F& rc, AnimationGroupPtr * group )
{
	using namespace std;

	HRESULT result;
	group->reset( new AnimationGroup() );
	(*group)->rect_ = rc;

	fstream in;
	in.open( filename, ios::in );

	string buffer;
	
	//¶ÁÈëÍ¼Æ¬
	getline( in, buffer, '\n' );
	ImageType * temp;
	wstring a = StringToWString( buffer );
	result = drawTool_->CreateImageFromFile( a, &temp );
	if( FAILED( result ) )
	{
		return false;
	}

	int frameNum = 0;
	in >> frameNum;
	(*group)->frameGroup_= new ImageType * [frameNum];
	if( (*group)->frameGroup_ == 0 )
	{
		return false;
	}

	D2D1_SIZE_U size = { 0 };
	D2D1_POINT_2U point = { 0 };
	D2D1_POINT_2U zeroPoint = { 0 };
	Rect_U rect = { 0 };

	for( int i = 0; i < frameNum; ++ i )
	{
		in >> point.x >> point.y >> size.width >> size.height;
		rect.y0 = point.y; rect.x0 = point.x;
		rect.y1 = point.y + size.height;
		rect.x1 = point.x + size.width;

		result = drawTool_->CreateImageFormImage( rect, temp, &(*group)->frameGroup_[i] );

		if( FAILED( result ) )
		{
			temp->Release();
			delete group;
			group = 0;
			return false;
		}
	}

	int animationNum = 0;
	in >> animationNum;
	for( int i = 0; i < animationNum; ++ i )
	{
		in.get();
		string animationName;
		getline( in, animationName, ' ');

		int frameNum = 0;
		in >> frameNum;

		int * frameIndex = new int [ frameNum ];
		for( int j = 0; j < frameNum; ++ j )
		{
			in >> frameIndex[j];
		}

		Animation * temp = new Animation( frameIndex, frameNum ); 

		int overAnimationNum = 0;
		in >> overAnimationNum;

		for( int j = 0; j < overAnimationNum; ++ j )
		{
			int overAnimation = -1;
			float startAlpha = 0.0f, alphaStep = 0.0f;
			in >> overAnimation;
			switch ( overAnimation )
			{
			case 0:
				in >> startAlpha >> alphaStep;
				temp = new AlphaAnimation( temp, startAlpha, alphaStep );
			default:
				break;
			}
		}

		(*group)->SetAnimation( animationName, temp );
		(*group)->pAnimationSystem_ = this;
	}

	return true;
}

void AnimationSystem::AddAnimationList( AnimationGroupPtr animationGroup )
{
	animationGroupList.push_back( animationGroup );
}

void AnimationSystem::Run()
{
	typedef list< AnimationGroupPtr >::iterator ite;

	ite cur = animationGroupList.begin();
	while( cur != animationGroupList.end() )
	{
		if( (*cur)->nLoopCount_ > 0 )
		{
			if( (*cur)->animationState_ != ANIMATION_STATE_PAUSED )
			{
				(*cur)->Run( drawTool_ );

				if( (*cur)->animationState_ == ANIMATION_STATE_STOPPED
					|| (*cur)->animationState_ == ANIMATION_STATE_INITIAL )
					-- (*cur)->nLoopCount_;			
			}
			++ cur;
		}	
		else 
		{
			ite temp = cur ++;
			animationGroupList.erase( temp );
		}
	}
}

bool AnimationSystem::Init( DrawTool * drawTool )
{
	drawTool_ = drawTool;
	return true;
}

void AnimationSystem::ShutDown()
{

}