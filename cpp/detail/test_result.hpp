#ifndef IUNIT_CPP_DETAIL_TEST_RESULT_HPP
#define IUNIT_CPP_DETAIL_TEST_RESULT_HPP

#include <vector>
#include <string>
#include <sstream>
#include <ostream>

#include "detail/test_exception.hpp"

namespace iunit {
    namespace detail {
        class TestResult {
        public:
            TestResult(const std::string& testName) :
                _testName(testName),
                _success(0),
                _failed(0),
                _checkTotal(0),
                _runTime(0),
                _errFile(""),
                _errLine(0)
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
                _checkTotal+=child->_checkTotal;
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
                if(_oss.str().length() != 0) {
                    _oss << std::endl;
                }
                _oss << str;
            }
            void setException(const std::string& exception) {
                _exceptionMessage = exception;
            }
            
            const std::string message() {
                return _oss.str();
            }
            const std::string exceptionMessage() {
                return _exceptionMessage;
            }

            void printOn( std::ostream& os ) {
                os << "Name = " << _testName << " success = " << _success
                   << " failed = " << _failed << std::endl;
            }

            void setErrorFilename(std::string filename) {
                _errFile = filename;
            }
            std::string getErrorFilename() const {
                return _errFile;
            }
            void setErrorLine(size_t line) {
                _errLine = line;
            }
            size_t getErrorLine() const {
                return _errLine;
            }
            
            std::string _testName;
            size_t _success;
            size_t _failed;
            size_t _checkTotal;
            std::vector<TestResult*> _results;
            std::ostringstream _oss;
            std::string _exceptionMessage;
            double _runTime;
            std::string _errFile;
            size_t _errLine;
            
        };
    }
}

#endif /* end of include guard */

