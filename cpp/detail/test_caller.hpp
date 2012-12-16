
#ifndef IUNIT_CPP_DETAIL_TEST_CALLER_HPP
#define IUNIT_CPP_DETAIL_TEST_CALLER_HPP

#include <string>
#include <vector>

#include "test_result_collector.hpp"
#include "test_fixture.hpp"

#include "detail/test_result.hpp"

namespace iunit {
    namespace detail {
        class NullFixture : public TestFixture {
        public:
            NullFixture() {}
            virtual void setup() {}
            virtual void teardown() {}
        };

        class TestRunnable {
        public:
            TestRunnable(const std::string name) :
                _success(0),
                _failed(0),
                _name(name)
            {
                _fixture = new NullFixture();
            }

            TestRunnable(const std::string name, TestFixture* fixture) :
                _success(0),
                _failed(0),
                _name(name)
            {
                _fixture = fixture;
            }
            virtual ~TestRunnable() {
                delete _fixture;
            }

            virtual bool isSuccessful() const {
                return _failed == 0;
            }
            virtual size_t getSuccessCount() const {
                return _success;
            }
            virtual size_t getFailedCount() const {
                return _failed;
            }
            virtual std::string getName() const {
                return _name;
            }
            virtual void run(TestResult* parentResult) = 0;
        protected:
            virtual void success() {
                ++_success;
            }
            virtual void failed() {
                ++_failed;
            }

            size_t _success;
            size_t _failed;
            std::string _name;
            TestFixture* _fixture;

            virtual void setup() {
                _fixture->setup();
            }
            virtual void teardown() {
                _fixture->teardown();
            }
            virtual void init() = 0;
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
            TestMethod(T* instance, void (T::*method)(), std::string name)
            {
                _methodObj = new _TestMethod<T>(instance, method);
                _name = name;
            }

            virtual ~TestMethod() {
                delete _methodObj;
            }

            void call() {
                _methodObj->call();
            }
            
            std::string getName() const { return _name; }

        private:
            _TestMethod_base* _methodObj;
            std::string _name;
        };

    };
};

#endif /* end of include guard */
