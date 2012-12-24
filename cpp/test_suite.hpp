
#ifndef IUNIT_CPP_TEST_SUITE_HPP
#define IUNIT_CPP_TEST_SUITE_HPP

#include "test_case.hpp"
#include "test_result_collector.hpp"
#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"

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
        void start() {
            init();
            TestResult* suiteResult = new TestResult(getName());
            std::cout << "[ RUN      ] " << getName() << std::endl;
            run(suiteResult);
            if( suiteResult->isSuccess() ) {
                std::cout << "[       OK ] " << getName() << std::endl;
            } else {
                std::cout << "[  FAILED  ] " << getName() << std::endl;
            }
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

                for(; test != _testCases.end(); test++) {
                    std::cout << "[ RUN      ] " << (*test)->getName() << std::endl;
                    TestResult* result = new TestResult((*test)->getName());
                    try {
                        (*test)->run(result);
                    } catch (AssertException& e) {
                        suiteResult->add(result);
                        std::cout << "[  FAILED  ] " << (*test)->getName() << std::endl;
                        break;
                    }
                    suiteResult->add(result);
                    
                    if( result->isSuccess() ) {
                        std::cout << "[       OK ] " << (*test)->getName() << std::endl;
                    } else {
                        std::cout << "[  FAILED  ] " << (*test)->getName() << std::endl;
                    }
                    //result->set((*test)->getName(), (*test)->getSuccessCount(), (*test)->getFailedCount());
                }


        }
    };

};
#endif /* end of include guard */
