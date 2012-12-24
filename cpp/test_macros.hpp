#ifndef IUNIT_CPP_TEST_MACROS_HPP
#define IUNIT_CPP_TEST_MACROS_HPP

#include <iostream>
#include <sstream>
#include <detail/test_macros.hpp>
#include "detail/test_exception.hpp"

using namespace iunit::detail;


#define IUNIT_ADD_TEST(method) \
    addTest(this, &method, #method)

#define IUNIT_MESSAGE( message )   \
    //this->getResult().getOstream() << message << std::endl;
    //std::cout << method << "[" << __FILE__ << "(" << __LINE__ << ")]" << std::endl;
    
//------------------------------------------------------------------------
// Normal Check
#define IUNIT_EQ(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, EQ, ERROR)

#define IUNIT_NE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, NE,ERROR)

#define IUNIT_LE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, LE, ERROR)

#define IUNIT_LT(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, LT,ERROR)

#define IUNIT_GE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, GE, ERROR)

#define IUNIT_GT(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, GT,ERROR)

#define IUNIT_NULL( actual ) \
    IUNIT_DETAIL_TEST(NULL, actual, __FILE__, __LINE__, NULL, ERROR)

#define IUNIT_NOT_NULL( actual ) \
    IUNIT_DETAIL_TEST(NULL, actual, __FILE__, __LINE__, NOT_NULL, ERROR)

#define IUNIT_TRUE( condition ) \
    IUNIT_DETAIL_TEST_COND( condition, __FILE__, __LINE__, TRUE, ERROR)

#define IUNIT_FALSE( condition ) \
    IUNIT_DETAIL_TEST_COND( condition, __FILE__, __LINE__, FALSE, ERROR)

#define IUNIT_THROW( exception ) \
    IUNIT_DETAIL_TEST_THROW( exception, __FILE__, __LINE__, THROW, ERROR)

#define IUNIT_NO_THROW( exception ) \
    IUNIT_DETAIL_TEST_THROW( exception, __FILE__, __LINE__, NO_THROW, ERROR)

//------------------------------------------------------------------------
// Assertionl Check
#define IUNIT_ASSERT_EQ(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, EQ, ASSERT)

#define IUNIT_ASSERT_NE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, NE, ASSERT)

#define IUNIT_ASSERT_LE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, LE, ASSERT)

#define IUNIT_ASSERT_LT(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, LT,ASSERT)

#define IUNIT_ASSERT_GE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, GE, ASSERT)

#define IUNIT_ASSERT_GT(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, GT,ASSERT)

#define IUNIT_ASSERT_NULL( actual ) \
    IUNIT_DETAIL_TEST(NULL, actual, __FILE__, __LINE__, NULL, ASSERT)

#define IUNIT_ASSERT_NOT_NULL( actual ) \
    IUNIT_DETAIL_TEST(NULL, actual, __FILE__, __LINE__, NOT_NULL, ASSERT)

#define IUNIT_ASSERT_TRUE( condition ) \
    IUNIT_DETAIL_TEST_COND(condition, __FILE__, __LINE__, TRUE, ASSERT)

#define IUNIT_ASSERT_FALSE( condition ) \
    IUNIT_DETAIL_TEST_COND(condition, __FILE__, __LINE__, FALSE, ASSERT)

#define IUNIT_ASSERT_THROW( exception ) \
    IUNIT_DETAIL_TEST_THROW( exception, __FILE__, __LINE__, THROW, ASSERT)

#define IUNIT_ASSERT_NO_THROW( exception ) \
    IUNIT_DETAIL_TEST_THROW( exception, __FILE__, __LINE__, NO_THROW, ASSERT)

//------------------------------------------------------------------------
// Warning Check
#define IUNIT_WARN_EQ(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, EQ, WARN)

#define IUNIT_WARN_NE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, NE, WARN)

#define IUNIT_WARN_LE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, LE, WARN)

#define IUNIT_WARN_LT(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, LT,WARN)

#define IUNIT_WARN_GE(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, GE, WARN)

#define IUNIT_WARN_GT(expected, actual) \
    IUNIT_DETAIL_TEST(expected, actual, __FILE__, __LINE__, GT,WARN)

#define IUNIT_WARN_NULL( actual ) \
    IUNIT_DETAIL_TEST(NULL, actual, __FILE__, __LINE__, NULL, WARN)

#define IUNIT_WARN_NOT_NULL( actual ) \
    IUNIT_DETAIL_TEST(NULL, actual, __FILE__, __LINE__, NOT_NULL, WARN)

#define IUNIT_WARN_TRUE( condition ) \
    IUNIT_DETAIL_TEST_COND(condition, __FILE__, __LINE__, TRUE, WARN)

#define IUNIT_WARN_FALSE( condition ) \
    IUNIT_DETAIL_TEST_COND(condition, __FILE__, __LINE__, FALSE, WARN)

#define IUNIT_WARN_THROW( exception ) \
    IUNIT_DETAIL_TEST_THROW( exception, __FILE__, __LINE__, THROW, WARN)

#define IUNIT_WARN_NO_THROW( exception ) \
    IUNIT_DETAIL_TEST_THROW( exception, __FILE__, __LINE__, NO_THROW, WARN)

#endif /* end of include guard */

