
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
            TestMethod(T* instance, void (T::*method)(), std::string name) :
                TestRunnable( name )
            {
                _methodObj = new _TestMethod<T>(instance, method);
            }

            virtual ~TestMethod() {
                delete _methodObj;
            }
            
        protected:

            virtual void runImpl(TestResult* result) {
                try {
                    std::cout << "[ RUN      ] " << getName() << std::endl;
                    _methodObj->call(result);
                    std::cout << "[       OK ] " << getName() << std::endl;
                    result->set(getName(), 1, 0);
                } catch (ErrorException& e) {
                    std::cout << "[  FAILED  ] ## Error  --> " << getName() << std::endl;
                    e.setTestName(getName());
                    std::cout << e.what() << std::endl;
                    result->addMessage(e.what());
                    result->set(getName(), 0, 1);
                    throw e;
                } catch (AssertException& e) {
                    std::cout << "[  FAILED  ] ## Assert --> " << getName() << std::endl;
                    e.setTestName(getName());
                    std::cout << e.what() << std::endl;
                    result->addMessage(e.what());
                    result->set(getName(), 0, 1);
                    throw e;
                }
            }

            virtual void init() {
            }

        private:
            _TestMethod_base* _methodObj;
            std::string _name;
        };

    };
};

#endif /* end of include guard */
