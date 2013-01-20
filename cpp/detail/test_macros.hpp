#ifndef IUNIT_CPP_DETAIL_TEST_MACROS_HPP
#define IUNIT_CPP_DETAIL_TEST_MACROS_HPP

#include "detail/test_equal_checker.hpp"

#define IUNIT_DETAIL_TEST(expected, actual, file, line, CHECK, TYPE) \
    IUNIT_DETAIL_##TYPE##_##CHECK(expected, actual, file, line)

#define IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, OP) \
    { \
        if( expected OP actual ) { \
            this->success(); \
        } else { \
            this->failed(); \
            std::stringstream ss; \
            ss << "Error :            " << #expected << " " << #OP << " " << #actual << std::endl; \
            ss << "        expected = " << expected << std::endl;\
            ss << "          actual = " << actual; \
            throw ErrorException(ss.str(), file, line); \
        } \
    }
#define IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, OP) \
    { \
        if( expected OP actual ) { \
            this->success(); \
        } else { \
            this->failed(); \
            std::stringstream ss; \
            ss << "Assert :            " << #expected << " " << #OP << " " << #actual << std::endl; \
            ss << "         expected = " << expected << std::endl;\
            ss << "           actual = " << actual; \
            throw AssertException(ss.str(), file, line); \
        } \
    }

// Check Equal
#define IUNIT_DETAIL_ASSERT_EQ(expected, actual, file, line) \
    IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, == ) \

// Check Not Equal
#define IUNIT_DETAIL_ASSERT_NE(expected, actual, file, line) \
    IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, != ) \

// Check Less Equal
#define IUNIT_DETAIL_ASSERT_LE(expected, actual, file, line) \
    IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, >= ) \

// Check Less Than
#define IUNIT_DETAIL_ASSERT_LT(expected, actual, file, line) \
    IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, > ) \

// Check Greater Equal
#define IUNIT_DETAIL_ASSERT_GE(expected, actual, file, line) \
    IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, <= ) \

// Check Greater Than 
#define IUNIT_DETAIL_ASSERT_GT(expected, actual, file, line) \
    IUNIT_DETAIL_ASSERT_CHECK_IMPL(expected, actual, file, line, < ) \

// Check Equal NULL
#define IUNIT_DETAIL_ASSERT_NULL(expected, actual, file, line) \
    { \
        if( iunit::detail::EqualChecker::equal((void*)expected, (void*)actual) == false ) { \
            this->failed(); \
            std::stringstream ss; \
            ss << "Assert :         " << #actual << " == NULL" << std::endl; \
            ss << "         but was " << #actual << "  = " << actual << std::endl;\
            throw ErrorException(ss.str(), file, line); \
        } else { \
            this->success(); \
        } \
    }

// Check Not Equal NULL
#define IUNIT_DETAIL_ASSERT_NOT_NULL(expected, actual, file, line) \
    { \
        if( iunit::detail::EqualChecker::equal((void*)expected, (void*)actual) != false ) { \
            this->failed(); \
            std::stringstream ss; \
            ss << "Assert :         " << #actual << " != NULL" << std::endl; \
            ss << "         but was " << #actual << "  = " << actual; \
            throw ErrorException(ss.str(), file, line); \
        } else { \
            this->success(); \
        } \
    }

// Check Equal
#define IUNIT_DETAIL_ERROR_EQ(expected, actual, file, line) \
    IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, == ) \

// Check Not Equal
#define IUNIT_DETAIL_ERROR_NE(expected, actual, file, line) \
    IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, != ) \

// Check Less Equal
#define IUNIT_DETAIL_ERROR_LE(expected, actual, file, line) \
    IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, >= ) \

// Check Less Than
#define IUNIT_DETAIL_ERROR_LT(expected, actual, file, line) \
    IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, > ) \

// Check Greater Equal
#define IUNIT_DETAIL_ERROR_GE(expected, actual, file, line) \
    IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, <= ) \

// Check Greater Than 
#define IUNIT_DETAIL_ERROR_GT(expected, actual, file, line) \
    IUNIT_DETAIL_ERROR_CHECK_IMPL(expected, actual, file, line, < ) \

// Check Equal NULL
#define IUNIT_DETAIL_ERROR_NULL(expected, actual, file, line) \
    { \
        if( iunit::detail::EqualChecker::equal((void*)expected, (void*)actual) == false ) { \
            this->failed(); \
            std::stringstream ss; \
            ss << "Error :         " << #actual << " == NULL" << std::endl; \
            ss << "        but was " << #actual << "  = " << actual; \
            throw ErrorException(ss.str(), file, line); \
        } else { \
            this->success(); \
        } \
    }

// Check Not Equal NULL
#define IUNIT_DETAIL_ERROR_NOT_NULL(expected, actual, file, line) \
    { \
        if( iunit::detail::EqualChecker::equal((void*)expected, (void*)actual) != false ) { \
            this->failed(); \
            std::stringstream ss; \
            ss << "Error :         " << #actual << " != NULL" << std::endl; \
            ss << "        but was " << #actual << "  = " << actual;\
            throw ErrorException(ss.str(), file, line); \
        } else { \
            this->success(); \
        } \
    }

#endif /* end of include guard */
