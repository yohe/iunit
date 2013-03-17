#ifndef IUNIT_CPP_DETAIL_TEST_MACROS_HPP
#define IUNIT_CPP_DETAIL_TEST_MACROS_HPP

#include "detail/test_equal_checker.hpp"

#define IUNIT_DETAIL_CHECK_IMPL(expected, actual, file, line, OP, TYPE) \
    { \
        if( expected OP actual ) { \
            this->success(); \
        } else { \
            this->failed(); \
            std::stringstream ss; \
            ss << #TYPE << " :            " << #expected << " " << #OP << " " << #actual << std::endl; \
            ss << "        expected = " << expected << std::endl;\
            ss << "          actual = " << actual; \
            throw detail::TYPE ## Exception(ss.str(), file, line); \
        } \
    }

#define IUNIT_DETAIL_CHECK_THROW_IMPL(expression, EXCEPTION, file, line, TYPE) \
    { \
        try { \
            expression; \
            this->failed(); \
            std::stringstream ss; \
            ss << #TYPE << " :            " << #expression << " did not throw " << #EXCEPTION << std::endl; \
            ss << "        expected = " << #expression << " should throw " << #EXCEPTION << std::endl;\
            throw detail::TYPE ## Exception(ss.str(), file, line); \
        } catch ( EXCEPTION& e ) { \
            this->success(); \
        } \
    }

#define IUNIT_DETAIL_CHECK_NO_THROW_IMPL(expression, file, line, TYPE) \
    { \
        try { \
            expression; \
            this->success(); \
        } catch ( ... ) { \
            this->failed(); \
            std::stringstream ss; \
            ss << #TYPE << " :            " << #expression << " threw exception." << std::endl; \
            ss << "        expected = " << #expression << " don't throw exception." << std::endl;\
            throw detail::TYPE ## Exception(ss.str(), file, line); \
        } \
    }

#endif /* end of include guard */
