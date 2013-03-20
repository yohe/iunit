
#ifndef IUNIT_CPP_DETAIL_TEST_UTIL_HPP
#define IUNIT_CPP_DETAIL_TEST_UTIL_HPP

#include <string>
#include <iostream>
#include <ostream>
#include <set>

#include "detail/test_exception.hpp"
#include "detail/test_timer.hpp"
#include "detail/test_result.hpp"

#define DEFAULT_COLOR "\x1b[39m"
#define RUN_TEST_COLOR "\x1b[32m"
#define SUCCESS_TEST_COLOR "\x1b[32m"
#define FAILED_TEST_COLOR "\x1b[31m"
#define EXCEPTION_MESSAGE_COLOR "\x1b[33m"

namespace iunit {
    namespace detail {
        
        namespace util {
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
            static void printException(const char* exception) {
                std::cout << EXCEPTION_MESSAGE_COLOR << exception
                          << DEFAULT_COLOR << std::endl;
            }

            class TestReporter {
                TestResult* _result;
                CountUpTimer watch;
            public:
                TestReporter(TestResult* result) : _result(result) {
                    printStartTest(_result->testName());
                    watch.set();
                }
                ~TestReporter() {
                    printEndTest(_result->testName(), _result->isSuccess());
                    _result->setRunTime(watch.elapsed());
                }
            };

            class TeeStream {
                std::ostream& _os1;
                std::ostream& _os2;
            public:
                TeeStream(std::ostream& os1, std::ostream& os2) :
                    _os1(os1), _os2(os2)
                {
                }
                
                TeeStream& operator<< (bool val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (short val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (unsigned short val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (int val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (unsigned int val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (long val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (unsigned long val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (float val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (double val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (long double val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (void* val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator << (const char* val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (std::streambuf* val) {
                    _os1 << val;
                    _os2 << val;
                    return *this;
                }
                TeeStream& operator<< (std::ostream& (*pf)(std::ostream&)) {
                    (*pf)(_os1);
                    (*pf)(_os2);
                    return *this;
                }
                TeeStream& operator<< (std::ios& (*pf)(std::ios&)) {
                    (*pf)(_os1);
                    (*pf)(_os2);
                    return *this;
                }
                TeeStream& operator<< (std::ios_base& (*pf)(std::ios_base&)) {
                    (*pf)(_os1);
                    (*pf)(_os2);
                    return *this;
                }
            };
            
            std::set<std::string> splitFilter(const std::string& filterString) {
                std::set<std::string> filterSet;
                std::string tmp(filterString);
                size_t pos = tmp.find(",");
                while(pos != std::string::npos) {
                    std::string filter = tmp.substr(0, pos);
                    filter = filter.erase(0, filter.find_first_not_of(" "));
                    filter = filter.erase(filter.find_last_not_of(" ")+1);
                    tmp = tmp.erase(0, pos+1);
                    if(filter.at(filter.size()-1) == '/') {
                        filter.erase(filter.size()-1);
                    }
                    filterSet.insert(filter);
                    
                    pos = tmp.find(",");
                }
                if(tmp.size() != 0) {
                    tmp = tmp.erase(0, tmp.find_first_not_of(" "));
                    tmp = tmp.erase(tmp.find_last_not_of(" ")+1);
                    if(tmp.at(tmp.size()-1) == '/') {
                        tmp.erase(tmp.size()-1);
                    }
                    filterSet.insert(tmp);
                }
                return filterSet;
            }
        }
    }
}

#endif /* end of include guard */

