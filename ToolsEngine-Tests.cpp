#define BOOST_TEST_DYN_LINK
#include "include/ToolsEngine.h"
#define BOOST_TEST_MODULE ToolsEngineTests
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( configFileLoadTest )
{
    ToolsEngine *te;
    te = new ToolsEngine();
    BOOST_CHECK_EQUAL( te->configFileLoad("engine.conf"), 0);
}

//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE Test
//#include <boost/test/unit_test.hpp>
//
//double square(double x) {
//    return x*x;
//}
//
//double cube(double x) {
//    return x * x*x;
//}
//
//BOOST_AUTO_TEST_SUITE(SquareTest)
//BOOST_AUTO_TEST_CASE(SquareTestPositive) {
//    BOOST_REQUIRE(square(2.0) == 4.0);
//}
//
//BOOST_AUTO_TEST_CASE(SquareTestNegative) {
//    BOOST_REQUIRE_GE(square(-1.0), 0.0);
//}
//
//BOOST_AUTO_TEST_SUITE_END();
//
//
//BOOST_AUTO_TEST_SUITE(CubeTest)
//BOOST_AUTO_TEST_CASE(CubeTestPositive) {
//    BOOST_REQUIRE(cube(2.0) == 8.0);
//}
//
//BOOST_AUTO_TEST_CASE(CubeTestNegative) {
//    BOOST_REQUIRE_LE(cube(-1.0), 0.0);
//}
//BOOST_AUTO_TEST_SUITE_END();
