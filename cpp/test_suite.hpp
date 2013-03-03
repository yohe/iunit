
#ifndef IUNIT_CPP_TEST_SUITE_HPP
#define IUNIT_CPP_TEST_SUITE_HPP

#include <exception>
#include <string>
#include <vector>

#include "test_case.hpp"
#include "test_config.hpp"
#include "test_result_collector.hpp"
#include "test_fixture.hpp"

#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"
#include "detail/test_util.hpp"
#include "detail/test_runner.hpp"
#include "detail/test_exception_protector.hpp"


namespace iunit {

    using namespace detail;

    class CppTestSuite : public TestRunnable {
    protected:
        std::string _name;                          // Suite Name
        CppTestResultCollector* _collector;         
        std::vector<TestRunnable*> _testCases;       // TestCase in Suite

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
            ready(suiteResult);

            Util::printStartTest(getName());
            run(suiteResult);
            Util::printEndTest(getName(), suiteResult->isSuccess());

            _collector->addResult(suiteResult);
        }

        virtual void addTest(CppTestCase* test) {
            _testCases.push_back(test);
        }

    protected:
        virtual void init() {
        }

        virtual void runImpl(TestResult* suiteResult) {
            
            int repeat = 1;
            bool shuffle = _config.isShuffling();
            repeat = _config.repeateCount();

            TestRunner* runner = 0;
            if(shuffle) {
                runner = new RepeatableShuffleRunner(&_config, repeat);
            } else {
                runner = new RepeatableRunner(&_config, repeat);
            }

            ErrorProtector protector;
            try {
                runner->run(this, suiteResult, _testCases, &protector);
            } catch (AssertException& e){
                std::cout << "!!! Catch AssertException !!!" << std::endl;
                Util::printException(e);
            } catch (std::exception& e) {
                std::cout << "!!! Catch StdException !!!" << std::endl;
                Util::printException(e);
            } catch (...) {
                std::cout << "!!! Catch POD Exception !!!" << std::endl;
            }

            delete runner;
        }
    };

};
#endif /* end of include guard */
