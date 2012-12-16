
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
            if(_collector != NULL) {
                _collector->clear();
            }

            std::vector<CppTestCase*>::iterator ite = _testCases.begin();
            std::vector<CppTestCase*>::iterator end = _testCases.end();

            for(; ite != end; ite++) {
                delete *ite;
            }
            _testCases.clear();
        }
        void run() {
            init();
            std::cout << getName() << " start. " << std::endl;
            TestResult* suiteResult = new TestResult();
            run(suiteResult);
            std::cout << std::endl;
            _collector->addResult(suiteResult);
        }

        virtual void addTest(CppTestCase* test) {
            _testCases.push_back(test);
        }

        virtual void init() {}

    protected:

        virtual void run(TestResult* parentResult) {
            try {
                std::vector<CppTestCase*>::iterator test = _testCases.begin();

                TestResult* result = new TestResult();
                for(; test != _testCases.end(); test++) {
                    std::cout << "  " << (*test)->getName() << std::endl;
                    (*test)->run(result);
                    if((*test)->isSuccessful()) {
                        std::cout << "  Success!" << std::endl;
                    } else {
                        std::cout << "  Failed!" << std::endl;
                    }
                    result->set((*test)->getName(), (*test)->getSuccessCount(), (*test)->getFailedCount());

                    parentResult->add(result);
                }

                if(result->isSuccess()) {
                    std::cout << "Success!" << std::endl;
                } else {
                    std::cout << "Failed!" << std::endl;
                }
            } catch (AssertException& e) {
                TestResult* childResult = new TestResult();
                parentResult->add(childResult);
            }

        }

        std::string _name;
        CppTestResultCollector* _collector;
        std::vector<CppTestCase*> _testCases;
    };

};
#endif /* end of include guard */
