#ifndef IUNIT_CPP_DETAIL_TEST_EXCEPTION_PROTECTOR_HPP
#define IUNIT_CPP_DETAIL_TEST_EXCEPTION_PROTECTOR_HPP

#include "detail/test_exception.hpp"
#include "detail/test_runnable.hpp"
#include "detail/test_fixture_env.hpp"
#include "detail/test_timer.hpp"

namespace iunit {
    namespace detail {
        class ExceptionProtector {
        public:
            virtual void protectedRun(TestRunnable* owner, 
                                      TestResult* parent,
                                      TestRunnable* test) = 0;
        };

        template <class T>
        class GeneralExceptionProtector : public ExceptionProtector {
            typedef T exception_type;
        public:
            virtual void protectedRun(TestRunnable* owner, 
                                      TestResult* parent,
                                      TestRunnable* test) {
                FixtureConstructor env(owner);
                TestResult* testResult = new TestResult(test->getName());
                try {
                    test->run(testResult);
                    parent->add(testResult);
                } catch (exception_type& e) {
                    test->failed();
                    parent->add(testResult);
                } catch (...) {
                    test->failed();
                    parent->add(testResult);
                    throw;
                }
            }
        };
        
        struct DummyException {
        };

        typedef GeneralExceptionProtector<ErrorException> ErrorProtector;
        typedef GeneralExceptionProtector<DummyException> NonProtector;
        typedef GeneralExceptionProtector<AssertException> AssertProtector;
    };
};

#endif /* end of include guard */
