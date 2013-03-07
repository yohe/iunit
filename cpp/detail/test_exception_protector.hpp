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
                                      TestRunnable* test) {
                FixtureConstructor env(owner);
                TestResult* testResult = new TestResult(test->getName());
                Util::PrintTestState printer(testResult);
                CountUpTimer watch;
                watch.set();
                try {
                    test->run(testResult);
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                } catch (...) {
                    testResult->setRunTime(watch.elapsed());
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
                CountUpTimer watch;
                watch.set();
                try {
                    test->run(testResult);
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                } catch (...) {
                    testResult->setRunTime(watch.elapsed());
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
                CountUpTimer watch;
                watch.set();
                try {
                    test->run(testResult);
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                } catch (ErrorException& e) {
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                } catch (...) {
                    testResult->setRunTime(watch.elapsed());
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
                CountUpTimer watch;
                watch.set();
                try {
                    test->run(testResult);
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                } catch (AssertException& e) {
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                } catch (...) {
                    testResult->setRunTime(watch.elapsed());
                    parent->add(testResult);
                    throw;
                }
            }
        };

    };
};

#endif /* end of include guard */
