
#ifndef IUNIT_CPP_DETAIL_TEST_UTIL_HPP
#define IUNIT_CPP_DETAIL_TEST_UTIL_HPP

#include <string>
#include <iostream>

#include "detail/test_exception.hpp"

#define DEFAULT_COLOR "\x1b[39m"
#define RUN_TEST_COLOR "\x1b[32m"
#define SUCCESS_TEST_COLOR "\x1b[32m"
#define FAILED_TEST_COLOR "\x1b[31m"
#define EXCEPTION_MESSAGE_COLOR "\x1b[33m"

namespace iunit {
    namespace detail {
        
        class Util {
        public:
            static void printStartTest(const std::string& name) {
                std::cout << RUN_TEST_COLOR << "[ RUN      ] "
                          << DEFAULT_COLOR << name << std::endl;
            }
            static void printEndTest(const std::string& name, bool success) {
                if( success ) {
                    std::cout << SUCCESS_TEST_COLOR << "[       OK ] "
                              << DEFAULT_COLOR << name << std::endl;
                } else {
                    std::cout << FAILED_TEST_COLOR << "[  FAILED  ] "
                              << name << DEFAULT_COLOR << std::endl;
                }
            }
            static void printException(TestException& e) {
                std::cout << EXCEPTION_MESSAGE_COLOR << e.what()
                          << DEFAULT_COLOR << std::endl;
            }
            static void printException(std::exception& e) {
                std::cout << EXCEPTION_MESSAGE_COLOR << e.what()
                          << DEFAULT_COLOR << std::endl;
            }

            class PrintTestState {
                TestResult* _result;
            public:
                PrintTestState(TestResult* result) : _result(result) {
                    printStartTest(_result->testName());
                }
                ~PrintTestState() {
                    printEndTest(_result->testName(), _result->isSuccess());
                }
            };
        };

    };
};

#endif /* end of include guard */

