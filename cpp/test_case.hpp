
#ifndef IUNIT_CPP_TEST_CASE_HPP
#define IUNIT_CPP_TEST_CASE_HPP

#include <string>
#include <vector>
#include <iomanip>
#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"
#include "detail/test_result.hpp"

namespace iunit {

    using namespace detail;

    class CppTestCase : public TestRunnable {
    private:
        std::vector<TestMethod*> _testMethods;
        std::vector<TestRunnable*> _children;
        TestResult* _currentResult;

    protected:
    public:
        CppTestCase(const std::string& name) 
            : TestRunnable(name),
              _currentResult(NULL)
        {
        }
        virtual ~CppTestCase() { clear(); }
        
        void clear();

        template <class T>
        void addTest(T* instance, void (T::*method)(), std::string name);
        virtual void addTest(CppTestCase* test);
        
        virtual TestRunnable* getTest() { return this; }
        
    protected:
        virtual void runImpl(TestResult* testCaseResult);
        
        //TestResult& getResult() {
        //    return *_result;
        //}

    };

    template<class T>
    void CppTestCase::addTest(T* instance, void (T::*method)(), std::string name) {
        TestMethod* testMethod = new TestMethod(instance, method, name);
        _testMethods.push_back(testMethod);
    }
    
    void CppTestCase::addTest(CppTestCase* test) {
        _children.push_back(test);
    }
    
    void CppTestCase::clear() {
        std::vector<TestMethod*>::iterator ite = _testMethods.begin();
        std::vector<TestMethod*>::iterator end = _testMethods.end();
        for(; ite != end; ite++) {
            delete *ite;
        }
        _testMethods.clear();
        std::vector<TestRunnable*>::iterator ite2 = _children.begin();
        std::vector<TestRunnable*>::iterator end2 = _children.begin();
        for(; ite2 != end2; ite2++) {
            delete (*ite2);
        }
        _children.clear();
    }

    void CppTestCase::runImpl(TestResult* testCaseResult) {
        clear();
        init();
        setup();

        std::vector<TestMethod*>::iterator ite = _testMethods.begin();
        std::vector<TestMethod*>::iterator end = _testMethods.end();
        for(; ite != end; ite++) {
            //TestResult* result = new TestResult((*ite)->methodName());
            TestResult* methodResult = new TestResult((*ite)->getName());
            try {
                (*ite)->run(methodResult);
                testCaseResult->add(methodResult);
            } catch (ErrorException& e) {
                testCaseResult->add(methodResult);
                break;
            } catch (AssertException& e) {
                testCaseResult->add(methodResult);
                throw e;
            }
        }
        //result->set(getName(), this->getSuccessCount(), this->getFailedCount());

        std::vector<TestRunnable*>::iterator ite2 = _children.begin();
        std::vector<TestRunnable*>::iterator end2 = _children.begin();
        for(; ite2 != end2; ite2++) {
            TestResult* childResult = new TestResult((*ite2)->getName());
            try {
                std::cout << "[ RUN      ] " << getName() << std::endl;
                (*ite2)->run(childResult);
                std::cout << "[       OK ] " << getName() << std::endl;
                testCaseResult->add(childResult);
                //result->set((*test)->getName(), (*test)->getSuccessCount(), (*test)->getFailedCount());
            } catch (AssertException& e) {
                std::cout << "[  FAILED  ] " << getName() << std::endl;
                testCaseResult->add(childResult);
                //result->set((*test)->getName(), (*test)->getSuccessCount(), (*test)->getFailedCount());
                // TODO Result
                continue;;
            }
        }

        teardown();
    }
};

#endif /* end of include guard */
