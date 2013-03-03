#ifndef IUNIT_CPP_DETAIL_TEST_FIXTURE_HPP
#define IUNIT_CPP_DETAIL_TEST_FIXTURE_HPP

#include "test_fixture.hpp"
#include "detail/test_runnable.hpp"

namespace iunit {
    namespace detail {
        class FixtureWrapperTest : public TestRunnable {
            TestFixture* _fixture;
        public:
            FixtureWrapperTest() : TestRunnable(""), _fixture(NULL) {}
            FixtureWrapperTest(TestFixture* fixture) :
                TestRunnable(""), _fixture(fixture) {
            }
            ~FixtureWrapperTest() {
                if(_fixture) {
                    _fixture->teardown();
                }
            }
        protected:
            virtual void init() {}
            virtual void runImpl(TestResult* result) {}
        };

        class FixtureConstructor {
            TestRunnable* _test;
            FixtureWrapperTest _fixture;
        public:
            FixtureConstructor(TestRunnable* test) :
                _test(test),
                _fixture(NULL)
            {
                _test->setup();
            }
            FixtureConstructor(TestFixture* fixture) :
                _test(NULL),
                _fixture(fixture)
            {
            }
            ~FixtureConstructor() {
                if(_test) {
                    _test->teardown();
                }
            }
        };
    };
};

#endif
