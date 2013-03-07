
#ifndef IUNIT_CPP_DETAIL_TEST_RUNNER_HPP
#define IUNIT_CPP_DETAIL_TEST_RUNNER_HPP

#include <vector>
#include <algorithm>
#include "detail/test_result.hpp"
#include "detail/test_runnable.hpp"
#include "detail/test_util.hpp"
#include "detail/test_exception_protector.hpp"

namespace iunit {
    class TestConfig;

    namespace detail {
        class TestRunner {
        protected:
            TestConfig* _config;
        public:
            TestRunner(TestConfig* config) : _config(config) {}
            virtual ~TestRunner() {}

            void run(TestRunnable* owner,
                     TestResult* result,
                     std::vector<TestRunnable*>& tests,
                     ExceptionProtector* protector) {
                runImpl(owner, result, tests, protector);
            }

        protected:
            virtual void runImpl(TestRunnable* owner,
                                 TestResult* result,
                                 std::vector<TestRunnable*> tests,
                                 ExceptionProtector* protector) = 0;

        };
        
        class RepeatableRunner : public TestRunner {
            int _repeatCount;
        public:
            RepeatableRunner(TestConfig* config, int count) :
                TestRunner(config),
                _repeatCount(count)
            {
            }
            virtual ~RepeatableRunner() {
            }

        protected:
            virtual void runImpl(TestRunnable* owner,
                                 TestResult* result,
                                 std::vector<TestRunnable*> tests,
                                 ExceptionProtector* protector) {
                for(int i=0; i < _repeatCount; ++i) {
                    std::vector<TestRunnable*> tmp = tests;
                    std::vector<TestRunnable*>::iterator test = tmp.begin();

                    // 登録されている全てのテストを実行
                    // テストケース毎にテスト結果を登録
                    for(; test != tmp.end(); test++) {
                        (*test)->config(*_config);
                        protector->protectedRun(owner, result, *test);
                    }
                }
            }
        };
        class ShuffleRunner : public TestRunner {
        public:
            ShuffleRunner(TestConfig* config) :
                TestRunner(config)
            {
            }
            virtual ~ShuffleRunner() {
            }

        protected:
            virtual void runImpl(TestRunnable* owner,
                                 TestResult* result,
                                 std::vector<TestRunnable*> tests,
                                 ExceptionProtector* protector) {
                std::vector<TestRunnable*> tmp(tests);
                std::random_shuffle(tmp.begin(), tmp.end());
                for(std::vector<TestRunnable*>::iterator test = tmp.begin();
                    test != tmp.end();
                    ++test) {
                    (*test)->config(*_config);
                    protector->protectedRun(owner, result, *test);
                }
            }
        };

        class RepeatableShuffleRunner : public ShuffleRunner {
            int _repeatCount;
        public:
            RepeatableShuffleRunner(TestConfig* config, int count) :
                ShuffleRunner(config),
                _repeatCount(count)
            {
            }
            virtual ~RepeatableShuffleRunner() {
            }

        protected:
            virtual void runImpl(TestRunnable* owner,
                                 TestResult* result,
                                 std::vector<TestRunnable*> tests,
                                 ExceptionProtector* protector) {
                for(int i=0; i < _repeatCount; ++i) {
                    ShuffleRunner::runImpl(owner, result, tests, protector);
                }
            }
        };
        
    };
};

#endif /* end of include guard */
