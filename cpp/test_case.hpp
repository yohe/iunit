
#ifndef IUNIT_CPP_TEST_CASE_HPP
#define IUNIT_CPP_TEST_CASE_HPP

#include <string>
#include <vector>
#include <iomanip>
#include "detail/test_runnable.hpp"
#include "detail/test_method.hpp"
#include "detail/test_exception.hpp"
#include "detail/test_result.hpp"
#include "detail/test_util.hpp"

#include "test_fixture.hpp"

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
        void addTest(T* instance, void (T::*method)(), std::string className, std::string methodName);
        virtual void addTest(CppTestCase* test);

        virtual TestRunnable* getTest() { return this; }

    protected:
        virtual void runImpl(TestResult* testCaseResult);
    };

    template<class T>
    void CppTestCase::addTest(T* instance, void (T::*method)(), std::string className, std::string methodName) {
        TestMethod* testMethod = new TestMethod(instance, method, className, methodName);
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

        // 登録されているテスト関数を全て実行
        // テスト関数毎にテスト結果を登録
        // ErrorException はテスト関数の終了のみ
        // AssertException は テストケース自体を終了
        std::vector<TestMethod*>::iterator ite = _testMethods.begin();
        std::vector<TestMethod*>::iterator end = _testMethods.end();
        for(; ite != end; ite++) {
            TestResult* methodResult = new TestResult((*ite)->className(), (*ite)->methodName());
            try {
                (*ite)->run(methodResult);
                testCaseResult->add(methodResult);
            } catch (ErrorException& e) {
                testCaseResult->add(methodResult);
            } catch (AssertException& e) {
                testCaseResult->add(methodResult);
                throw e;
            }
        }

        // テストケースが複数のテストケースで構成されている場合
        std::vector<TestRunnable*>::iterator ite2 = _children.begin();
        std::vector<TestRunnable*>::iterator end2 = _children.end();
        for(; ite2 != end2; ite2++) {
            TestResult* childResult = new TestResult((*ite2)->getName());
            try {
                Util::printStartTest(getName());
                (*ite2)->run(childResult);
                Util::printEndTest(getName(), true);
                testCaseResult->add(childResult);
            } catch (AssertException& e) {
                Util::printEndTest(getName(), false);
                testCaseResult->add(childResult);
                continue;
            }
        }

        teardown();
    }
};

#endif /* end of include guard */
