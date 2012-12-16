
#ifndef CPP_DETAIL_TEST_CALLER_HPP
#define CPP_DETAIL_TEST_CALLER_HPP

#include <string>
#include <vector>

#include "test_result_collector.hpp"

namespace iunit {
    namespace detail {
        class TestRunnable {
        public:
            TestRunnable() {}
            virtual ~TestRunnable() {}
            virtual void run(CppTestResultCollector* collector) = 0;
        };

        class TestMethod {
        public:

            struct _TestMethod_base {
                _TestMethod_base() {}
                virtual ~_TestMethod_base() {}

                virtual void call() const = 0;
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
                virtual void call() const {
                    (_instance->*_method)();
                }
            };
            
            template <class T>
            TestMethod(T* instance, void (T::*method)())
            {
                _methodObj = new _TestMethod<T>(instance, method);
            }

            virtual ~TestMethod() {}

            void call() {
                _methodObj->call();
            }

        private:
            _TestMethod_base* _methodObj;
        };

    };
};

#endif /* end of include guard */
