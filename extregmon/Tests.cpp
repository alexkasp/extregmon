#define BOOST_TEST_MODULE My Test 

#include "Server.h"
#include <fstream>
#include <boost/test/included/unit_test.hpp> 


BOOST_AUTO_TEST_CASE(getCommandType_test)
{
	Server srv;
	//srv.startListen(7542);
	std::ofstream testParam("testParamOne.php",std::ofstream::trunc);
	testParam << "public static $pbxtype='aster';";
	testParam.close();
	int rettype = srv.getCommandType("testParamOne.php", "pbxtype");
	BOOST_TEST(rettype == 1);

	testParam.open("testParamOne.php", std::ofstream::trunc);
	testParam << "public static $pbxtype='extreg';";
	testParam.close();
	rettype = srv.getCommandType("testParamOne.php", "pbxtype");
	BOOST_TEST(rettype == 2);

}

BOOST_AUTO_TEST_CASE(pause)
{
	int a = 0;
	std::cin >> a;

}