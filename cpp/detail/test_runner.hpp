
#ifndef IUNIT_CPP_DETAIL_TEST_RUNNER_HPP
#define IUNIT_CPP_DETAIL_TEST_RUNNER_HPP

#include <vector>
#include <algorithm>
#include "detail/test_result.hpp"

namespace iunit {
    class TestConfig;

    namespace detail {
        class TestRunner {
            TestConfig* _config;
        public:
            TestRunner(TestConfig* config) : _config(config) {}
            virtual ~TestRunner() {}

            void run(TestResult* result, std::vector<TestRunnable*>& tests) {
                runImpl(result, tests);
            }

        private:
            virtual void runImpl(TestResult* result, std::vector<TestRunnable*> tests)=0;

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

            virtual void runImpl(TestResult* result, std::vector<TestRunnable*> tests) {
                for(int i=0; i < _repeatCount; ++i) {
                    std::vector<TestRunnable*> tmp = tests;
                    //TestRunnler* runner = _config.getTestRunner();
                    std::vector<TestRunnable*>::iterator test = tmp.begin();

                    // 登録されている全てのテストを実行
                    // テストケース毎にテスト結果を登録
                    for(; test != tmp.end(); test++) {
                        Util::printStartTest((*test)->getName());
                        TestResult* testResult = new TestResult((*test)->getName());
                        try {
                            (*test)->run(testResult);
                        } catch (AssertException& e) {
                            result->add(testResult);
                            Util::printEndTest((*test)->getName(), false);
                            break;
                        }
                        result->add(testResult);
                        Util::printEndTest((*test)->getName(), testResult->isSuccess());
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

            virtual void runImpl(TestResult* result, std::vector<TestRunnable*> tests) {
                std::vector<TestRunnable*> tmp(tests);
                std::random_shuffle(tmp.begin(), tmp.end());
                for(std::vector<TestRunnable*>::iterator test = tmp.begin();
                    test != tmp.end();
                    ++test) {
                    Util::printStartTest((*test)->getName());
                    TestResult* testResult = new TestResult((*test)->getName());
                    try {
                        (*test)->run(testResult);
                    } catch (AssertException& e) {
                        result->add(testResult);
                        Util::printEndTest((*test)->getName(), false);
                        break;
                    }
                    result->add(testResult);
                    Util::printEndTest((*test)->getName(), testResult->isSuccess());
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

            virtual void runImpl(TestResult* result, std::vector<TestRunnable*> tests) {
                for(int i=0; i < _repeatCount; ++i) {
                    ShuffleRunner::runImpl(result, tests);
                }
            }
        };
        
    }
}

#endif /* end of include guard */
