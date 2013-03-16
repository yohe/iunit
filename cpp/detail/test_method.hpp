
#ifndef IUNIT_CPP_DETAIL_TEST_METHOD_HPP
#define IUNIT_CPP_DETAIL_TEST_METHOD_HPP

#include <string>
#include <vector>
#include <iostream>

#include "detail/test_result.hpp"
#include "detail/test_runnable.hpp"
#include "detail/test_util.hpp"

namespace iunit {
    namespace detail {

        class TestMethod : public TestRunnable {
        public:
            struct _TestMethod_base {
                _TestMethod_base() {}
                virtual ~_TestMethod_base() {}

                virtual void call(TestResult* result) const = 0;
            };

            template <class T>
            struct _TestMethod : public _TestMethod_base {
                T* _instance;
                void (T::*_method)();

                _TestMethod(T* instance, void (T::*method)()) 
                    : _instance(instance),
                      _method(method)
                {
                }
                virtual void call(TestResult* result) const {
                    _instance->ready(result);
                    (_instance->*_method)();
                }
            };
            
            template <class T>
            TestMethod(T* instance, void (T::*method)(), std::string className, std::string methodName) :
                TestRunnable( methodName ),
                _className(className),
                _methodName(methodName)
            {
                _methodObj = new _TestMethod<T>(instance, method);
            }

            virtual ~TestMethod() {
                delete _methodObj;
            }
            
            virtual std::string className() {
                return _className;
            }
            virtual std::string methodName() {
                return _methodName;
            }
            
            virtual std::string testName() const {
                std::string test = _className + "::" + _methodName;
                return test;
            }
            
            virtual std::string getName() const {
                return testName();
            }
            
        protected:

            virtual void runImpl(TestResult* result) {
                std::string test = testName();
                try {
                    _methodObj->call(result);
                    result->set(test, 1, 0);
                } catch (ErrorException& e) {
                    e.setTestName(test);
                    util::printException(e);
                    result->setException(e);
                    result->set(test, 0, 1);
                    throw;
                } catch (AssertException& e) {
                    e.setTestName(test);
                    util::printException(e);
                    result->setException(e);
                    result->set(test, 0, 1);
                    throw;
                }
            }

            virtual void init() {
            }
            
            virtual void printTestPath(TestRunnable* parent) {
                setParentPath(parent->getFullPath());
                std::cout << getFullPath() << std::endl;
            }

        private:
            _TestMethod_base* _methodObj;
            std::string _className;
            std::string _methodName;
        };

    };
};

#endif /* end of include guard */
