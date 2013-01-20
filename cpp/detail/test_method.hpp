
#ifndef IUNIT_CPP_DETAIL_TEST_METHOD_HPP
#define IUNIT_CPP_DETAIL_TEST_METHOD_HPP

#include <string>
#include <vector>
#include <iostream>

#include "test_fixture.hpp"
#include "test_result_collector.hpp"
#include "detail/test_result.hpp"
#include "detail/test_runnable.hpp"

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
                TestRunnable( className ),
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
            
            virtual std::string testName() {
                std::string test = _className + "::" + _methodName;
                return test;
            }
            
        protected:

            virtual void runImpl(TestResult* result) {
                std::string test = testName();
                try {
                    std::cout << "[ RUN      ] " << test << std::endl;
                    _methodObj->call(result);
                    std::cout << "[       OK ] " << test << std::endl;
                    result->set(_className, 1, 0);
                } catch (ErrorException& e) {
                    std::cout << "[  FAILED  ] ## Error  --> " << test << std::endl;
                    e.setTestName(test);
                    std::cout << e.what() << std::endl;
                    result->addMessage(e.what());
                    result->set(_className, 0, 1);
                    throw e;
                } catch (AssertException& e) {
                    std::cout << "[  FAILED  ] ## Assert --> " << test << std::endl;
                    e.setTestName(test);
                    std::cout << e.what() << std::endl;
                    result->addMessage(e.what());
                    result->set(_className, 0, 1);
                    throw e;
                }
            }

            virtual void init() {
            }

        private:
            _TestMethod_base* _methodObj;
            std::string _className;
            std::string _methodName;
        };

    };
};

#endif /* end of include guard */
