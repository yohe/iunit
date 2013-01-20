
#ifndef IUNIT_CPP_TEST_SUITE_HPP
#define IUNIT_CPP_TEST_SUITE_HPP

#include "test_case.hpp"
#include "test_result_collector.hpp"
#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"
#include "detail/test_util.hpp"

#include "test_fixture.hpp"

namespace iunit {

    using namespace detail;

    class CppTestSuite : public TestRunnable {
    protected:
        std::string _name;                          // Suite Name
        CppTestResultCollector* _collector;         
        std::vector<CppTestCase*> _testCases;       // TestCase in Suite

    public:
        CppTestSuite(const std::string& name, CppTestResultCollector* collector = NULL) 
            : TestRunnable(name),
              _collector(collector)
        { }
        
        virtual ~CppTestSuite() {
            //if(_collector != NULL) {
            //    _collector->clear();
            //}

            std::vector<CppTestCase*>::iterator ite = _testCases.begin();
            std::vector<CppTestCase*>::iterator end = _testCases.end();

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

        virtual void init() {
        }

    protected:

        virtual void runImpl(TestResult* suiteResult) {
                std::vector<CppTestCase*>::iterator test = _testCases.begin();

                // 登録されている全てのテストを実行
                // テストケース毎にテスト結果を登録
                for(; test != _testCases.end(); test++) {
                    Util::printStartTest((*test)->getName());
                    TestResult* result = new TestResult((*test)->getName());
                    try {
                        (*test)->run(result);
                    } catch (AssertException& e) {
                        suiteResult->add(result);
                        Util::printEndTest((*test)->getName(), false);
                        break;
                    }
                    suiteResult->add(result);
                    Util::printEndTest((*test)->getName(), result->isSuccess());
                }
        }
    };

};
#endif /* end of include guard */
