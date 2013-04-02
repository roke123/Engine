#include <boost\test\unit_test.hpp>
using namespace boost;

#include "../Engine/RectangleClipFilter.h"

struct TestRectangleclipfilter
{
	TestRectangleclipfilter()
	{
		Rectangle2DType rect;
		rect.p0.x = 100.0f, rect.p0.y = 100.0f;
		rect.p1.x = 500.0f, rect.p1.y = 500.0f;

		testRectangleFilter_ = new RectangleClipFilter( rect );
	}

	~TestRectangleclipfilter()
	{
		delete testRectangleFilter_;
	}

	RectangleClipFilter * testRectangleFilter_;
};

BOOST_FIXTURE_TEST_SUITE( s_TestRectangleclipfilter, TestRectangleclipfilter )
	BOOST_FIXTURE_TEST_CASE( t_ClipFilter, TestRectangleclipfilter )
	{
		Vertex2D_F p0, p1;
		p0.x = 0.0f, p0.y = 0.0f;
		p1.x = 600.0f, p1.y = 600.0f;

		testRectangleFilter_->ClipLine( p0, p1 );

		BOOST_CHECK( p0.x - 100.0f < 1.0f );
		BOOST_CHECK( p1.x - 500.0f < 1.0f );
		BOOST_CHECK( p0.y - 100.0f < 1.0f );
		BOOST_CHECK( p1.y - 500.0f < 1.0f );
	}		
}