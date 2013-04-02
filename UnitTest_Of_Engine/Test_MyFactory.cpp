#include <boost\test\unit_test.hpp>
using namespace boost;

#include "../Engine/MyFactory.h"

BOOST_AUTO_TEST_SUITE( s_TestMyFactory )
	BOOST_AUTO_TEST_CASE( c_TestCreatePolygon2D )
	{
		MyFactory * myFactory = MyFactory::GetMyFactory();

		Vertex2D_F vertice[] = 
		{
			{100.0f, 100.0f},
			{200.0f, 400.0f},
			{620.0f, 473.0f},
			{18.5f, 66.3f}
		};
		int numVertex = ARRAYSIZE(vertice);

		Polygon2DType * polygon = 0;
		myFactory->CreatePolygon2D( vertice, numVertex, polygon );

		BOOST_CHECK( polygon->numVertex_== 4 );
		BOOST_CHECK_CLOSE_FRACTION( polygon->pc.x, 234.625f, 0.0001f );
		BOOST_CHECK_CLOSE_FRACTION( polygon->pc.y, 259.825f, 0.0001f );

	}
BOOST_AUTO_TEST_SUITE_END()