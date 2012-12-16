#ifndef IUNIT_CPP_DETAIL_TEST_OUTPUTTER_HPP
#define IUNIT_CPP_DETAIL_TEST_OUTPUTTER_HPP

#include "detail/test_result.hpp"

namespace iunit {
    namespace detail {

        class TestOutputter {
        public:
            TestOutputter() {}
            virtual ~TestOutputter() {}

            virtual void start(TestResult* result = NULL) = 0;
            virtual void end(TestResult* result = NULL) = 0;
            virtual void write(TestResult* result) = 0;
        };
    };
};

#endif /* end of include guard */
