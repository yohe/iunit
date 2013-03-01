
#ifndef IUNIT_CPP_TEST_SUITE_HPP
#define IUNIT_CPP_TEST_SUITE_HPP

#include "test_case.hpp"
#include "test_config.hpp"
#include "test_result_collector.hpp"
#include "test_fixture.hpp"

#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"
#include "detail/test_util.hpp"
#include "detail/test_runner.hpp"


namespace iunit {

    using namespace detail;

    class CppTestSuite : public TestRunnable {
    protected:
        std::string _name;                          // Suite Name
        CppTestResultCollector* _collector;         
        std::vector<TestRunnable*> _testCases;       // TestCase in Suite
        TestConfig _config;

    public:
        CppTestSuite(const std::string& name, CppTestResultCollector* collector = NULL) 
            : TestRunnable(name),
              _collector(collector)
        { }
        
        virtual ~CppTestSuite() {

            std::vector<TestRunnable*>::iterator ite = _testCases.begin();
            std::vector<TestRunnable*>::iterator end = _testCases.end();

            for(; ite != end; ite++) {
                delete *ite;
            }
            _testCases.clear();
        }
        void start(TestFixture* fixture = NULL) {
            // 全体のテスト結果を登録用変数を用意して
            // テストの実行
            // コレクタにテスト結果を渡して終了
            init();
            TestResult* suiteResult = new TestResult(getName());
            Util::printStartTest(getName());

            if( fixture ) {
                fixture->setup();
                run(suiteResult);
                fixture->teardown();
            } else {
                run(suiteResult);
            }

            Util::printEndTest(getName(), suiteResult->isSuccess());
            _collector->addResult(suiteResult);
        }

        virtual void addTest(CppTestCase* test) {
            _testCases.push_back(test);
        }

        virtual void config(TestConfig& config){
            _config = config;
        }

    protected:
        virtual void init() {
        }

        virtual void runImpl(TestResult* suiteResult) {
            
            int repeat = 1;
            bool shuffle = false;
            repeat = _config.repeateCount();
            if(_config.isShuffling()) {
                shuffle = true;
            }

            TestRunner* runner = 0;
            if(shuffle) {
                runner = new RepeatableShuffleRunner(&_config, repeat);
            } else {
                runner = new RepeatableRunner(&_config, repeat);
            }

            runner->run(suiteResult, _testCases);
            ////TestRunnler* runner = _config.getTestRunner();
            //std::vector<TestRunnable*>::iterator test = _testCases.begin();

            //// 登録されている全てのテストを実行
            //// テストケース毎にテスト結果を登録
            //for(; test != _testCases.end(); test++) {
            //    Util::printStartTest((*test)->getName());
            //    TestResult* result = new TestResult((*test)->getName());
            //    try {
            //        (*test)->run(result);
            //    } catch (AssertException& e) {
            //        suiteResult->add(result);
            //        Util::printEndTest((*test)->getName(), false);
            //        break;
            //    }
            //    suiteResult->add(result);
            //    Util::printEndTest((*test)->getName(), result->isSuccess());
            //}
        }
    };

};
#endif /* end of include guard */
