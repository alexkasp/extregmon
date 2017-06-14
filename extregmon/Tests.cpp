
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost\test\unit_test.hpp>
#include "MainListen.h"


BOOST_AUTO_TEST_SUITE(TestFuzzyCompare)

BOOST_AUTO_TEST_CASE(Equal) {
	MainListen ml;

	BOOST_REQUIRE(ml.run(500));
}
BOOST_AUTO_TEST_SUITE_END()