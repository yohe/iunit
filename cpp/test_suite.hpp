
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

    class CppTestSuite : public detail::TestRunnable {
    protected:
        std::string _name;                          // Suite Name
        CppTestResultCollector& _collector;         
        std::vector<detail::TestRunnable*> _testCases;       // TestCase in Suite

    public:
        CppTestSuite(const std::string& name, CppTestResultCollector& collector, TestFixture* fixture = NULL) 
            : detail::TestRunnable(name, fixture),
            _collector(collector)
        { }

        virtual ~CppTestSuite() {
            std::vector<detail::TestRunnable*>::iterator ite = _testCases.begin();
            std::vector<detail::TestRunnable*>::iterator end = _testCases.end();

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
            detail::TestResult* suiteResult = new detail::TestResult(getName());
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

        virtual void addTest(detail::TestRunnable* test) {
            _testCases.push_back(test);
        }

    protected:
        virtual void init() {
        }

        virtual void runImpl(detail::TestResult* suiteResult) {
            int repeat = 1;
            bool shuffle = _config.isShuffling();
            repeat = _config.repeateCount();

            detail::TestRunner* runner = 0;
            if(shuffle) {
                runner = new detail::RepeatableShuffleRunner(&_config, repeat);
            } else {
                runner = new detail::RepeatableRunner(&_config, repeat);
            }

            detail::ErrorProtector protector;
            try {
                setParentPath("");
                runner->run(this, suiteResult, _testCases, &protector);
            } catch (detail::AssertException& e){
                // nop
            } catch (std::exception& e) {
                std::cout << "!!! Catch StdException !!!" << std::endl;
                suiteResult->addMessage("!!! Catch StdException !!!" );
                detail::util::printException(e);
            } catch (...) {
                std::cout << "!!! Catch POD or other Exception !!!" << std::endl;
                suiteResult->addMessage("!!! Catch POD or other Exception !!!" );
            }

            delete runner;
        }

        virtual void printTestPath(detail::TestRunnable* parent) {
            std::cout << getFullPath() << std::endl;
            detail::TestRunnable::PrintTestPathFunctor functor(this);
            std::for_each(_testCases.begin(), _testCases.end(), functor);
        }
    };

};
#endif /* end of include guard */
