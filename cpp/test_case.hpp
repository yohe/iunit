
#ifndef IUNIT_CPP_TEST_CASE_HPP
#define IUNIT_CPP_TEST_CASE_HPP

#include <string>
#include <vector>
#include <iomanip>

#include "detail/test_runnable.hpp"
#include "detail/test_runner.hpp"
#include "detail/test_method.hpp"
#include "detail/test_result.hpp"
#include "detail/test_exception_protector.hpp"


namespace iunit {

    using namespace detail;

    class CppTestCase : public TestRunnable {
    private:
        std::vector<TestRunnable*> _testMethods;
        std::vector<TestRunnable*> _children;

    protected:
    public:
        CppTestCase(const std::string& name, TestFixture* fixture = NULL) 
            : TestRunnable(name, fixture)
        {
        }
        virtual ~CppTestCase() { clear(); }

        void clear();

        template <class T>
        void addTest(T* instance, void (T::*method)(),
                     std::string className, std::string methodName) {
            TestMethod* testMethod = new TestMethod(instance, method,
                                                    className, methodName);
            _testMethods.push_back(testMethod);
        }
        virtual void addTest(CppTestCase* test) {
            _children.push_back(test);
        }

        virtual TestRunnable* getTest() { return this; }

    protected:
        virtual void runImpl(TestResult* testCaseResult);

        virtual void printTestPath(TestRunnable* parent) {
            init();
            setParentPath(parent->getFullPath());
            std::cout << getFullPath() << std::endl;
            TestRunnable::PrintTestPathFunctor functor(this);
            std::for_each(_testMethods.begin(), _testMethods.end(), functor);
            std::for_each(_children.begin(), _children.end(), functor);
        }

    };

    inline void CppTestCase::clear() {
        std::vector<TestRunnable*>::iterator ite = _testMethods.begin();
        std::vector<TestRunnable*>::iterator end = _testMethods.end();
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

    inline void CppTestCase::runImpl(TestResult* testCaseResult) {
        clear();
        init();
        
        //if(_config.isPrintPath()) {
        //    printTestPath(testCaseResult);
        //    return;
        //}

        bool shuffle = _config.isShuffling();
        TestRunner* runner = 0;
        if(shuffle) {
            runner = new ShuffleRunner(&_config);
        } else {
            // TestCase doesn't repeat.
            runner = new RepeatableRunner(&_config, 1);
        }

        NonProtector nonProtector;
        runner->run(this, testCaseResult, _testMethods, &nonProtector);

        ErrorProtector errorProtector;
        runner->run(this, testCaseResult, _children, &errorProtector);
    }
    
};

#endif /* end of include guard */
