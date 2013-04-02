#include <boost/test/unit_test.hpp>
using namespace boost;

#include "../Engine/MyFactory.h"
#include "../Engine/Matrix3x3.h"

struct TestMatrix3x3
{
	TestMatrix3x3()
	{
		MyFactory * myFactory = MyFactory::GetMyFactory();

		matrix0 = myFactory->CreateRotationMatrix3x3( 3.14f );
		matrix1 = myFactory->CreateTransformMatrix3x3( 3.3f, 5.5f );
		vertex.x = 1.0f;
		vertex.y = 1.0f;
	}

	~TestMatrix3x3()
	{
	}

	Matrix3x3_F matrix0, matrix1;
	Vertex2D_F vertex;
};


BOOST_FIXTURE_TEST_SUITE( s_TestMatrix3x3, TestMatrix3x3 )
	BOOST_FIXTURE_TEST_CASE( c_TestVertex2DxMatrix3x3, TestMatrix3x3 )
	{
		vertex = vertex * matrix1;

		BOOST_CHECK_CLOSE_FRACTION( vertex.x, 3.3f, 0.0001f );
		BOOST_CHECK_CLOSE_FRACTION( vertex.y, 5.5f, 0.0001f );
	} //end case

	BOOST_FIXTURE_TEST_CASE( c_TestMatrix3x3xMatrix3x3, TestMatrix3x3 )
	{
		matrix0 = matrix0 * matrix1;

		BOOST_CHECK_CLOSE_FRACTION( vertex.x, 3.3f, 0.0001f );
		BOOST_CHECK_CLOSE_FRACTION( vertex.y, 5.5f, 0.0001f );
	} //end case
}//end suite