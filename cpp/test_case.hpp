
#ifndef IUNIT_CPP_TEST_CASE_HPP
#define IUNIT_CPP_TEST_CASE_HPP

#include <string>
#include <vector>
#include <iomanip>
#include "detail/test_caller.hpp"
#include "detail/test_exception.hpp"

namespace iunit {

    using namespace detail;

    class CppTestCase : public TestRunnable {
    private:
        std::vector<TestMethod*> _testMethods;
        std::vector<TestRunnable*> _children;

    protected:
    public:
        CppTestCase(const std::string& name) 
            : TestRunnable(name)
        {
        }
        virtual ~CppTestCase() { clear(); }
        
        void clear() {
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
        
        virtual void run(TestResult* parentResult) {
            clear();
            init();
            setup();

            TestResult* result = new TestResult();
            std::vector<TestMethod*>::iterator ite = _testMethods.begin();
            std::vector<TestMethod*>::iterator end = _testMethods.end();
            for(; ite != end; ite++) {
                std::cout << "    ----" << std::endl;
                std::cout << "    " << (*ite)->getName() << " execute." << std::endl;
                try {
                    (*ite)->call();
                } catch (ErrorException& e) {
                    // TODO Result
                    return;
                }
                std::cout << "    Success!" << std::endl;
            }

            std::vector<TestRunnable*>::iterator ite2 = _children.begin();
            std::vector<TestRunnable*>::iterator end2 = _children.begin();
            for(; ite2 != end2; ite2++) {
                try {
                    (*ite2)->run(result);
                } catch (ErrorException& e) {
                    // TODO Result
                    continue;;
                }
            }
            
            parentResult->add(result);

            teardown();
        }
        

        template <class T>
        void addTest(T* instance, void (T::*method)(), std::string name);
        virtual void addTest(CppTestCase* test);
        
        virtual TestRunnable* getTest() { return this; }

    };

    template<class T>
    void CppTestCase::addTest(T* instance, void (T::*method)(), std::string name) {
        TestMethod* testMethod = new TestMethod(instance, method, name);
        _testMethods.push_back(testMethod);
    }
    
    void CppTestCase::addTest(CppTestCase* test) {
        _children.push_back(test);
    }
};

#endif /* end of include guard */
