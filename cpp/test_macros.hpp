#ifndef IUNIT_CPP_TEST_MACROS_HPP
#define IUNIT_CPP_TEST_MACROS_HPP

#include <iostream>
#include <sstream>
#include <detail/test_macros.hpp>

#define IUNIT_ADD_TEST( className, methodName ) \
    addTest(this, &className::methodName, #className, #methodName)

#define IUNIT_MESSAGE( message )   \
    std::cout << message << std::endl; \
    currentResult()->addMessage(message);
    
//------------------------------------------------------------------------
// Normal Check
#define IUNIT_EQ(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, ==, Error)

#define IUNIT_NE(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, !=, Error)

#define IUNIT_LE(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, >=, Error)

#define IUNIT_LT(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, > , Error)

#define IUNIT_GE(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, <=, Error)

#define IUNIT_GT(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, < , Error)

#define IUNIT_NULL( actual ) \
    IUNIT_DETAIL_CHECK_IMPL(NULL, actual, __FILE__, __LINE__, ==, Error)

#define IUNIT_NOT_NULL( actual ) \
    IUNIT_DETAIL_CHECK_IMPL(NULL, actual, __FILE__, __LINE__, !=, Error)

#define IUNIT_TRUE( condition ) \
    IUNIT_DETAIL_CHECK_IMPL(true, (condition), __FILE__, __LINE__, ==, Error)

#define IUNIT_FALSE( condition ) \
    IUNIT_DETAIL_CHECK_IMPL(false, (condition), __FILE__, __LINE__, ==, Error)

#define IUNIT_THROW( expression, exception ) \
    IUNIT_DETAIL_CHECK_THROW_IMPL( expression, exception, __FILE__, __LINE__, Error)

#define IUNIT_NO_THROW( expression ) \
    IUNIT_DETAIL_CHECK_NO_THROW_IMPL( expression, __FILE__, __LINE__, Error)

//------------------------------------------------------------------------
// Assertionl Check
#define IUNIT_ASSERT_EQ(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, ==, Assert)

#define IUNIT_ASSERT_NE(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, !=, Assert)

#define IUNIT_ASSERT_LE(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, >=, Assert)

#define IUNIT_ASSERT_LT(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, > , Assert)

#define IUNIT_ASSERT_GE(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, <=, Assert)

#define IUNIT_ASSERT_GT(expected, actual) \
    IUNIT_DETAIL_CHECK_IMPL(expected, actual, __FILE__, __LINE__, < , Assert)

#define IUNIT_ASSERT_NULL( actual ) \
    IUNIT_DETAIL_CHECK_IMPL(NULL, actual, __FILE__, __LINE__, ==, Assert)

#define IUNIT_ASSERT_NOT_NULL( actual ) \
    IUNIT_DETAIL_CHECK_IMPL(NULL, actual, __FILE__, __LINE__, !=, Assert)

#define IUNIT_ASSERT_TRUE( condition ) \
    IUNIT_DETAIL_CHECK_IMPL(true, (condition), __FILE__, __LINE__, ==, Assert)

#define IUNIT_ASSERT_FALSE( condition ) \
    IUNIT_DETAIL_CHECK_IMPL(false, (condition), __FILE__, __LINE__, ==, Assert)

#define IUNIT_ASSERT_THROW( expression, exception ) \
    IUNIT_DETAIL_CHECK_THROW_IMPL( expression, exception, __FILE__, __LINE__, Assert)

#define IUNIT_ASSERT_NO_THROW( expression ) \
    IUNIT_DETAIL_CHECK_NO_THROW_IMPL( expression, __FILE__, __LINE__, Assert)

#endif /* end of include guard */

