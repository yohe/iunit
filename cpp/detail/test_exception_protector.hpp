#ifndef IUNIT_CPP_DETAIL_TEST_EXCEPTION_PROTECTOR_HPP
#define IUNIT_CPP_DETAIL_TEST_EXCEPTION_PROTECTOR_HPP

#include "detail/test_exception.hpp"
#include "detail/test_runnable.hpp"
#include "detail/test_fixture_env.hpp"

namespace iunit {
    namespace detail {
        class ExceptionProtector {
        public:
            virtual void protectedRun(TestRunnable* owner, 
                                      TestResult* parent,
                                      TestRunnable* test) {
                FixtureConstructor env(owner);
                TestResult* testResult = new TestResult(test->getName());
                Util::PrintTestState printer(testResult);
                try {
                    test->run(testResult);
                    parent->add(testResult);
                } catch (...) {
                    parent->add(testResult);
                }
                Util::printEndTest(test->getName(), testResult->isSuccess());
            }
        };
        
        class NonProtector : public ExceptionProtector {
        public:
            virtual void protectedRun(TestRunnable* owner, 
                                      TestResult* parent,
                                      TestRunnable* test) {
                FixtureConstructor env(owner);
                TestResult* testResult = new TestResult(test->getName());
                Util::PrintTestState printer(testResult);
                try {
                    test->run(testResult);
                    parent->add(testResult);
                } catch (...) {
                    //testResult->set(test->getName(), 0, 1);
                    parent->add(testResult);
                    throw;
                }
            }
        };

        class ErrorProtector : public ExceptionProtector {
        public:
            virtual void protectedRun(TestRunnable* owner, 
                                      TestResult* parent,
                                      TestRunnable* test) {
                FixtureConstructor env(owner);
                TestResult* testResult = new TestResult(test->getName());
                Util::PrintTestState printer(testResult);
                try {
                    test->run(testResult);
                    parent->add(testResult);
                } catch (ErrorException& e) {
                    parent->add(testResult);
                } catch (...) {
                    //testResult->set(test->getName(), 0, 1);
                    parent->add(testResult);
                    throw;
                }
            }
        };

        class AssertProtector : public ExceptionProtector {
        public:
            virtual void protectedRun(TestRunnable* owner, 
                                      TestResult* parent,
                                      TestRunnable* test) {
                FixtureConstructor env(owner);
                TestResult* testResult = new TestResult(test->getName());
                Util::PrintTestState printer(testResult);
                try {
                    test->run(testResult);
                    parent->add(testResult);
                } catch (AssertException& e) {
                    parent->add(testResult);
                } catch (...) {
                    //testResult->set(test->getName(), 0, 1);
                    parent->add(testResult);
                    throw;
                }
            }
        };

    };
};

#endif /* end of include guard */
