#ifndef IUNIT_CPP_DETAIL_TEST_MACROS_HPP
#define IUNIT_CPP_DETAIL_TEST_MACROS_HPP

#define IUNIT_DETAIL_ASSERT_EQUAL(expected, actual, File, Line) \
    { \
        if( iunit::detail::EqualChecker::equal(expected, actual) == false ) { \
            this->countFailed(); \
            std::stringstream ss; \
            ss << "excepted = " << #expected << std::endl \
               << "actual   = " << #actual; \
            throw AssertException(ss.str(), File, Line); \
        } else { \
            this->countSuccess(); \
        } \
    }

#define IUNIT_DETAIL_ERROR_EQUAL(expected, actual, File, Line) \
    { \
        if( iunit::detail::EqualChecker::equal(expected, actual) == false ) { \
            this->countFailed(); \
            std::stringstream ss; \
            ss << "excepted = " << #expected << std::endl \
               << "actual   = " << #actual; \
            throw ErrorException(ss.str(), File, Line); \
        } else { \
            this->countSuccess(); \
        } \
    }

#define IUNIT_DETAIL_WARN_EQUAL(expected, actual, File, Line) \
    { \
        if( iunit::detail::EqualChecker::equal(expected, actual) == false ) { \
            this->countFailed(); \
            std::stringstream ss; \
            ss << "excepted = " << #expected << std::endl \
               << "actual   = " << #actual; \
            throw WarnException(ss.str(), File, Line); \
        } else { \
            this->countSuccess(); \
        } \
    }


#endif /* end of include guard */
