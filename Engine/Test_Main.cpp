#define BOOST_TEST_MAIN

#include <boost\test\unit_test.hpp>
using namespace boost;

BOOST_AUTO_TEST_CASE( t_Main )
{
	BOOST_CHECK_MESSAGE( true, "unit test success" );
}



