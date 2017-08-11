#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE My Test 
#define BOOST_LIB_DIAGNOSTIC

#include <boost/test/unit_test.hpp>


#include "Server.h"
#include <fstream>
#include "testCommand.h"


BOOST_AUTO_TEST_CASE(getTimeFromLine_testCommand)
{
	string badline = "c9ed99a4-78f3-11e7-bde1-0177bd11a386 o=FreeSWITCH 1501826703 1501826704 IN IP4 212.193.100.96";
	string goodline = "c9ed99a4-78f3-11e7-bde1-0177bd11a386 2017-08-04 12:03:31.822602 [DEBUG] switch_core_state_machine.c:40 sofia/external/148695_id40793@212.193.100.168 Standard INIT";

	string parsedLine = "";

	testCommand tc;

	BOOST_REQUIRE(tc.getTimeFromLine(goodline,parsedLine));
	BOOST_CHECK_EQUAL(parsedLine.compare("2017-08-04 12:03:31.822602"),0);
	BOOST_REQUIRE(!tc.getTimeFromLine(badline, parsedLine));
}

BOOST_AUTO_TEST_CASE(getPrevDate_testCommand)
{
	testCommand tc;
	ifstream log("freeswitch.log");
	if (log.is_open())
	{
		log.seekg(0, std::ios_base::end);
	

		std::string time = tc.getPrevTime(log);
		std::cout << time << "\n";
		BOOST_CHECK_EQUAL(time.compare("2017-08-04 10:39:35.422608"), 0);
	}
	else
		BOOST_ERROR("file not open!!!");
	log.close();
}

BOOST_AUTO_TEST_CASE(getNextDate_testCommand)
{
	testCommand tc;
	ifstream log("freeswitch.log");
	if (log.is_open())
	{
		std::string time = tc.getNextTime(log);
		std::cout << time << "\n";
		BOOST_CHECK_EQUAL(time.compare("2017-08-04 09:56:41.502565"), 0);
	}
	else
		BOOST_ERROR("file not open!!!");

	log.close();
}

BOOST_AUTO_TEST_CASE(getPartialLog)
{
	testCommand tc;
	std::vector<string> testout;

	size_t beginposition = tc.getCallLogPartial("14c78b4a-78e2-11e7-8511-0177bd11a386", "2017-08-04 09:56:46",testout, "freeswitch.log");
	BOOST_CHECK_EQUAL(testout.size(), 3);

	tc.getCallLogPartial("14c78b4a-78e2-11e7-8511-0177bd11a386", beginposition, testout, "freeswitch.log");
	
}

BOOST_AUTO_TEST_CASE(pause)
{
	int a = 0;
	std::cin >> a;

}


