#ifndef IUNIT_CPP_DETAIL_TEST_EXCEPTION_HPP
#define IUNIT_CPP_DETAIL_TEST_EXCEPTION_HPP

#include <string>

namespace iunit {
    namespace detail {

        class TestException {
        public:
            TestException(const std::string& message,
                          const std::string& file,
                          size_t line) : 
                _message(message),
                _file(file),
                _line(line)
            {
            }

            virtual ~TestException() {}

        protected:
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

        class WarnException : public TestException{
        public:
            WarnException (const std::string& message,
                          const std::string& file,
                          size_t line) : 
                TestException(message, file, line)
            {
            }

            virtual ~WarnException() {}
        };
    };
};

#endif /* end of include guard */
