#ifndef IUNIT_CPP_TEST_SUITE_HPP
#define IUNIT_CPP_TEST_SUITE_HPP

#include "test_case.hpp"
#include "test_result_collector.hpp"
#include "detail/test_caller.hpp"
#include "detail/test_exception.hpp"

namespace iunit {

    using namespace detail;

    class CppTestSuite : public TestRunnable {
    public:
        CppTestSuite(const std::string& name, CppTestResultCollector* collector = NULL) 
            : TestRunnable(name),
              _collector(collector)
        { }
        
        virtual ~CppTestSuite() {
        }
        void run() {
            TestResult* suiteResult = new TestResult();
            run(suiteResult);
            _collector->addResult(suiteResult);
        }

        virtual void addTest(TestRunnable* test) {
            _testCases.push_back(test);
        }

        virtual void init() {}

    protected:

        void clear() {
            if(_collector != NULL) {
                _collector->clear();
            }

            std::vector<TestRunnable*>::iterator ite = _testCases.begin();
            std::vector<TestRunnable*>::iterator end = _testCases.end();

            for(; ite != end; ite++) {
                delete *ite;
            }
            _testCases.clear();
        }

        virtual void run(TestResult* parentResult) {
            clear();
            try {
                std::vector<TestRunnable*>::iterator test = _testCases.begin();

                TestResult* result = new TestResult();
                for(; test != _testCases.end(); test++) {
                    std::cout << "Execute : " << (*test)->getName() << "[" << std::endl;
                    (*test)->run(result);
                    std::cout << "]";
                    if((*test)->isSuccessful()) {
                        std::cout << " -> Success!" << std::endl;
                    } else {
                        std::cout << " -> Failed!" << std::endl;
                    }
                    result->set((*test)->getName(), (*test)->getSuccessCount(), (*test)->getFailedCount());

                    parentResult->add(result);
                }
            } catch (AssertException& e) {
                TestResult* childResult = new TestResult();
                parentResult->add(childResult);
            }
        }

        std::string _name;
        CppTestResultCollector* _collector;
        std::vector<TestRunnable*> _testCases;
    };

};
#endif /* end of include guard */
