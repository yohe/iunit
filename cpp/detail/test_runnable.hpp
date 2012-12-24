
#ifndef IUNIT_CPP_DETAIL_TEST_RUNNABLE_HPP
#define IUNIT_CPP_DETAIL_TEST_RUNNABLE_HPP

#include <string>
#include <vector>

#include "test_result_collector.hpp"
#include "test_fixture.hpp"

#include "detail/test_exception.hpp"
#include "detail/test_result.hpp"

namespace iunit {
    namespace detail {
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

            void ready(TestResult* current) {
                _result = current;
            } 
            TestResult* currentResult() {
                return _result;
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
            virtual void run(TestResult* result) {
                runImpl(result);
            }
        protected:

            virtual void runImpl(TestResult* result) = 0;

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
            TestResult* _result;

            virtual void setup() {
                _fixture->setup();
            }
            virtual void teardown() {
                _fixture->teardown();
            }
            virtual void init() = 0;
        };
    };
};

#endif /* end of include guard */
