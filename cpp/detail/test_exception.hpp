#ifndef IUNIT_CPP_DETAIL_TEST_EXCEPTION_HPP
#define IUNIT_CPP_DETAIL_TEST_EXCEPTION_HPP

#include <string>
#include <sstream>

namespace iunit {
    namespace detail {

        class TestException {
        public:
            TestException(const std::string& message,
                          const std::string& file,
                          size_t line) : 
                _testName(""),
                _message(message),
                _file(file),
                _line(line)
            {
            }

            virtual ~TestException() {}

            std::string testName() const {
                return _testName;
            }
            void setTestName(std::string testName) {
                _testName = testName;
            }
            
            std::string message() const {
                return _message;
            }

            std::string file() const {
                return _file;
            }

            size_t line() const {
                return _line;
            }
            
            const char* what() const {
                std::stringstream ss;
                ss << _file << "(" << _line << ")" << std::endl;
                ss << _message;
                return ss.str().c_str();
            }

        protected:
            std::string _testName;
            std::string _message;
            std::string _file;
            size_t _line;
        };

        class AssertException : public TestException{
        public:
            AssertException (const std::string& message,
                             const std::string& file,
                             size_t line) : 
                TestException(message, file, line)
            {
            }

            virtual ~AssertException() {}
            
            const char* what() const {
                std::stringstream ss;
                ss << "!!! Assertion !!!" << std::endl;
                ss << TestException::what();
                return ss.str().c_str();
            }
        };

        class ErrorException : public TestException{
        public:
            ErrorException (const std::string& message,
                            const std::string& file,
                            size_t line) : 
                TestException(message, file, line)
            {
            }

            virtual ~ErrorException() {}
        };

    };
};

#endif /* end of include guard */
