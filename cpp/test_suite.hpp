#ifndef CPP_TEST_SUITE_HPP
#define CPP_TEST_SUITE_HPP

#include "test_case.hpp"
#include "test_result_collector.hpp"
#include "detail/test_caller.hpp"

namespace iunit {

    using namespace detail;

    class CppTestSuite : public TestRunnable {
    public:
        CppTestSuite(CppTestResultCollector* collector = NULL) 
            : _collector(collector)
        { }
        
        virtual ~CppTestSuite() {
            std::vector<TestRunnable*>::iterator ite = _testCases.begin();
            std::vector<TestRunnable*>::iterator end = _testCases.end();

            for(; ite != end; ite++) {
                delete *ite;
            }
            _testCases.clear();
        }

        virtual void run(CppTestResultCollector* collector) {
            TestResult* suiteResult = new TestResult();

            std::vector<TestRunnable*>::iterator test = _testCases.begin();
            for(; test != _testCases.end(); test++) {
                (*test)->run(_collector);
            }

            _collector->addResult(suiteResult);
        }
        void run() {
            run(_collector);
        }

        virtual void addTest(TestRunnable* test) {
            _testCases.push_back(test);
        }

    protected:
        CppTestResultCollector* _collector;
        std::vector<TestRunnable*> _testCases;
    };

};
#endif /* end of include guard */
