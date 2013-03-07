#ifndef IUNIT_CPP_DETAIL_TEST_RESULT_HPP
#define IUNIT_CPP_DETAIL_TEST_RESULT_HPP

#include <vector>
#include <string>
#include <sstream>
#include <ostream>

//#include "detail/test_outputter.hpp"

namespace iunit {
    namespace detail {
        class TestResult {
        public:
            TestResult(const std::string& testName) :
                _testName(testName),
                _success(0),
                _failed(0)
            {
            }
            
            virtual ~TestResult() {
                std::vector<TestResult*>::iterator ite = _results.begin();
                std::vector<TestResult*>::iterator end = _results.end();

                for(; ite != end; ++ite) {
                    delete *ite;
                }

                _results.clear();
            }
            
            bool isSuccess() const {
                if(_failed == 0) {
                    return true;
                }
                return false;
            }
            
            void add(TestResult* child) {
                _success+=child->_success;
                _failed+=child->_failed;
                _results.push_back(child);
            }
            
            std::string testName() const {
                return _testName;
            }
            
            double getRunTime() const {
                return _runTime;
            }

            void set(const std::string& name, size_t success, size_t failed) {
                _testName = name;
                _success += success;
                _failed += failed;
            }

            void setRunTime(double time) {
                _runTime = time;
            }

            std::ostream& getOstream() {
                return _oss;
            }
            
            void addMessage(const std::string& str) {
                if(_oss.tellp() != 0) {
                    _oss << std::endl;
                }
                _oss << str;
            }
            
            const std::string message() {
                return _oss.str();
            }

            std::string _testName;
            size_t _success;
            size_t _failed;
            std::vector<TestResult*> _results;
            std::ostringstream _oss;
            double _runTime;
            
            void printOn( std::ostream& os ) {
                os << "Name = " << _testName << " success = " << _success
                   << " failed = " << _failed << std::endl;
            }
        };
    };
};

#endif /* end of include guard */

