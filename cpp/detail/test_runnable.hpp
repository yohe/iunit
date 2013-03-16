
#ifndef IUNIT_CPP_DETAIL_TEST_RUNNABLE_HPP
#define IUNIT_CPP_DETAIL_TEST_RUNNABLE_HPP

#include <string>
#include <vector>

#include "test_fixture.hpp"
#include "test_config.hpp"

#include "detail/test_util.hpp"

namespace iunit {
    namespace detail {
        class TestRunnable {
            friend class FixtureConstructor;
        public:
            TestRunnable(const std::string& name, TestFixture* fixture = NULL) :
                _success(0),
                _failed(0),
                _name(name),
                _result(NULL)
            {
                _fixture = fixture;
            }
            virtual ~TestRunnable() {
            }

            void config(TestConfig& config){
                _config = config;
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
                util::TestReporter reporter(result);
                runImpl(result);
            }
            
            void setParentPath(const std::string& path) {
                _parentPath = path;
            }
            const std::string getFullPath() const {
                return _parentPath + "/" + _name;
            }
            class PrintTestPathFunctor {
                TestRunnable* _parent;
            public:
                PrintTestPathFunctor(TestRunnable* parent) : _parent(parent) {}
                void operator()(TestRunnable* test) {
                    test->printTestPath(_parent);
                }
            };
        protected:

            virtual void runImpl(TestResult* result) = 0;

            virtual void success() {
                ++_success;
            }
            virtual void failed() {
                ++_failed;
            }

            virtual void printTestPath(TestRunnable* parent) {
            }

            size_t _success;
            size_t _failed;
            std::string _name;
            TestFixture* _fixture;
            TestResult* _result;
            TestConfig _config;
            std::string _parentPath;

            virtual void setup() {
                if(_fixture)
                    _fixture->setup();
            }
            virtual void teardown() {
                if(_fixture)
                    _fixture->teardown();
            }
            virtual void init() = 0;
        };
        
    }
}

#endif /* end of include guard */
