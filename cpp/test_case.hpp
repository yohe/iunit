
#ifndef CPP_TEST_CASE_HPP
#define CPP_TEST_CASE_HPP

#include <string>
#include <vector>
#include "detail/test_caller.hpp"

#define TO_STRING(T) #T

namespace iunit {

    using namespace detail;

    class CppTestCase : public TestRunnable {
    private:
        std::vector<TestMethod*> _testMethods;
        std::vector<TestRunnable*> _children;

    protected:
        virtual void run(CppTestResultCollector* collector) {
            clear();
            init();
            setup();

            //try {
                std::vector<TestMethod*>::iterator ite = _testMethods.begin();
                std::vector<TestMethod*>::iterator end = _testMethods.end();
                for(; ite != end; ite++) {
                    (*ite)->call();
                }

                std::vector<TestRunnable*>::iterator ite2 = _children.begin();
                std::vector<TestRunnable*>::iterator end2 = _children.begin();
                for(; ite2 != end2; ite2++) {
                    (*ite2)->run(collector);
                }
            //} catch (TestException& e) {

            //}

            teardown();
        }
        
    public:
        CppTestCase() { }
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

        template <class T>
        void addTest(T* instance, void (T::*method)(), std::string name);
        virtual void addTest(TestRunnable* test);
        
        virtual TestRunnable* getTest() { return this; }

        virtual void setup() = 0;
        virtual void teardown() = 0;
        virtual void init() = 0;
    };

    template<class T>
    void CppTestCase::addTest(T* instance, void (T::*method)(), std::string name) {
        std::cout << name << std::endl;
        TestMethod* testMethod = new TestMethod(instance, method);
        _testMethods.push_back(testMethod);
    }
    
    void CppTestCase::addTest(TestRunnable* test) {
        _children.push_back(test);
    }
};

#endif /* end of include guard */
