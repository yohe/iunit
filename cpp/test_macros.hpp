#ifndef IUNIT_CPP_TEST_MACROS_HPP
#define IUNIT_CPP_TEST_MACROS_HPP

#include <iostream>
#include <sstream>
#include <detail/test_macros.hpp>
#include "detail/test_exception.hpp"

using namespace iunit::detail;


#define IUNIT_ADD_TEST(method) \
    addTest(this, &method, #method)

#define IUNIT_MESSAGE( method )   \
    std::cout << method << std::endl;
    //std::cout << method << "[" << __FILE__ << "(" << __LINE__ << ")]" << std::endl;
    
// ( expected, actual )
#define IUNIT_ASSERT_EQUAL(expected, actual) \
    IUNIT_DETAIL_ASSERT_EQUAL(expected, actual, __FILE__, __LINE__)

#define IUNIT_ERROR_EQUAL \
    IUNIT_DETAIL_ERROR_EQUAL(expected, actual, __FILE__, __LINE__)

#define IUNIT_WARN_EQUAL \
    IUNIT_DETAIL_WARN_EQUAL(expected, actual, __FILE__, __LINE__)

#define IUNIT_ASSERT_COND   1          // ( condition )
#define IUNIT_ERROR_COND    1
#define IUNIT_WARN_COND     1

#define IUNIT_CHECK_THROW    1          // ( Exception )
#define IUNIT_CHECK_NO_THROW 1

#endif /* end of include guard */

