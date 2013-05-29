#ifndef IUNIT_CPP_DETAIL_TEST_MACROS_HPP
#define IUNIT_CPP_DETAIL_TEST_MACROS_HPP

#include "detail/test_equal_checker.hpp"

#define IUNIT_MESSAGE_DETAIL(test, message ) \
    std::cout << message << std::endl; \
    test->currentResult()->addMessage(message);

#define IUNIT_DETAIL_CHECK_NULL_IMPL(expected, actual, file, line, TYPE) \
    { \
        if(iunit::detail::EqualChecker::equalNull(actual) == expected) { \
        } \
    }

#define IUNIT_DETAIL_CHECK_IMPL(expected, actual, file, line, OP, TYPE) \
    { \
        if( expected OP actual ) { \
            \
        } else { \
            this->failed(); \
            std::stringstream ss; \
            ss << #TYPE << " :            " << #expected << " " << #OP << " " << #actual \
               << " condition equation did not pass." << std::endl; \
            ss << "        expected : " << expected << " "#OP" "#actual << std::endl;\
            ss << "          actual : "#actual" = " << actual; \
            throw detail::TYPE ## Exception(ss.str(), file, line); \
        } \
    }

#define IUNIT_DETAIL_CHECK_THROW_IMPL(expression, EXCEPTION, file, line, TYPE) \
    { \
        try { \
            expression; \
            this->failed(); \
            std::stringstream ss; \
            ss << #TYPE << " :            " << #expression << " did not throw " << #EXCEPTION"." << std::endl; \
            ss << "        expected : " << #expression << " should throw " << #EXCEPTION"." << std::endl;\
            throw detail::TYPE ## Exception(ss.str(), file, line); \
        } catch ( EXCEPTION& e ) { \
            \
        } \
    }

#define IUNIT_DETAIL_CHECK_NO_THROW_IMPL(expression, file, line, TYPE) \
    { \
        try { \
            expression; \
            \
        } catch ( ... ) { \
            this->failed(); \
            std::stringstream ss; \
            ss << #TYPE << " :            " << #expression << " threw exception." << std::endl; \
            ss << "        expected : " << #expression << " don't throw exception." << std::endl;\
            throw detail::TYPE ## Exception(ss.str(), file, line); \
        } \
    }

//#define IUNIT_DETAIL_CHECK_IMPL_TEST(actual, file, line) \
//    { \
//        iunit::detail::CheckFunctor obj(#actual, file, line);IUNIT_DETAIL_EXPECTED_2(actual)
//    
//#define IUNIT_DETAIL_EXPECTED_2(actual) \
//    if( obj(actual, 
//
//#define _Should_(expected) \
//    expected) ) { \
//    } else { \
//        this->failed(); \
//        std::stringstream ss; \
//        throw detail::ErrorException(ss.str(), file, line); \
//    }
//
//#define _Should_Throw_(expected) \
//    expected); \
//    }

//#define IUNIT_DETAIL_EXPECTED( expected ) \
//    obj(actual, expected);

#endif /* end of include guard */
