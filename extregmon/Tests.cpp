#define BOOST_TEST_MODULE My Test 

#include "Server.h"
#include <fstream>
#include "testCommand.h"
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

BOOST_AUTO_TEST_CASE(lineBackLog)
{
	char buf[1024];
	char tmpbuf[1024];
	ofstream test("lineBackLogTest", fstream::trunc);
	BOOST_ASSERT(test);

	string check1 = "line1 - should be last";
	string check2 = "line2 - middle";
	string check3 = "line3 - first";

	test.write(check1.c_str(),check1.length());
	test.write(check2.c_str(),check2.length());
	test.write(check3.c_str(),check3.length());
	test.close();

	ifstream testi("lineBackLogTest");
	for (auto i = 0; i < 3; ++i)
		testi.getline(tmpbuf, 1024);

	testCommand tc;

	tc.LineBackLog(testi);
	testi.getline(buf, 1024);
	std::string tmp = std::string(buf);
	BOOST_TEST(check3.compare(tmp) == 0);

	tc.LineBackLog(testi);
	tc.LineBackLog(testi);
	testi.getline(buf, 1024);
	std::string tmp1 = std::string(buf);
	BOOST_TEST(check2.compare(tmp1) == 0);

	tc.LineBackLog(testi);
	tc.LineBackLog(testi);
	testi.getline(buf, 1024);
	std::string tmp2 = std::string(buf);
	BOOST_TEST(check3.compare(tmp2) == 0);

}

BOOST_AUTO_TEST_CASE(pause)
{
	int a = 0;
	std::cin >> a;

}