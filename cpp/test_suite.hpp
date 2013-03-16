
#ifndef IUNIT_CPP_TEST_SUITE_HPP
#define IUNIT_CPP_TEST_SUITE_HPP

#include <exception>
#include <string>
#include <vector>

#include "test_result_collector.hpp"

#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"
#include "detail/test_util.hpp"
#include "detail/test_runner.hpp"
#include "detail/test_exception_protector.hpp"
#include "detail/test_fixture_env.hpp"


namespace iunit {
    class TestFixture;

    using namespace detail;
    class CppTestSuite : public TestRunnable {
    protected:
        std::string _name;                          // Suite Name
        CppTestResultCollector& _collector;         
        std::vector<TestRunnable*> _testCases;       // TestCase in Suite

    public:
        CppTestSuite(const std::string& name, CppTestResultCollector& collector, TestFixture* fixture = NULL) 
            : TestRunnable(name, fixture),
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
        void start() {
            // 全体のテスト結果を登録用変数を用意して
            // テストの実行
            // コレクタにテスト結果を渡して終了

            init();
            TestResult* suiteResult = new TestResult(getName());
            ready(suiteResult);
            if(_config.isPrintPath()) {
                printTestPath(NULL);
                return;
            }

            if(!_config.isSkipTest(getFullPath())) {
                run(suiteResult);
            }

            _collector.addResult(suiteResult);
        }

        virtual void addTest(TestRunnable* test) {
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
                setParentPath("");
                runner->run(this, suiteResult, _testCases, &protector);
            } catch (AssertException& e){
                // nop
            } catch (std::exception& e) {
                std::cout << "!!! Catch StdException !!!" << std::endl;
                suiteResult->addMessage("!!! Catch StdException !!!" );
                util::printException(e);
            } catch (...) {
                std::cout << "!!! Catch POD or other Exception !!!" << std::endl;
                suiteResult->addMessage("!!! Catch POD or other Exception !!!" );
            }

            delete runner;
        }

        virtual void printTestPath(TestRunnable* parent) {
            std::cout << getFullPath() << std::endl;
            TestRunnable::PrintTestPathFunctor functor(this);
            std::for_each(_testCases.begin(), _testCases.end(), functor);
        }
    };

};
#endif /* end of include guard */
