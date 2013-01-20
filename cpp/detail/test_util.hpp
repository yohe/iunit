
#ifndef IUNIT_CPP_DETAIL_TEST_UTIL_HPP
#define IUNIT_CPP_DETAIL_TEST_UTIL_HPP

#include <string>
#include <iostream>

namespace iunit {
    namespace detail {
        
        class Util {
        public:
            static void printStartTest(const std::string& name) {
                std::cout << "[ RUN      ] " << name << std::endl;
            }
            static void printEndTest(const std::string& name, bool success) {
                if( success ) {
                    std::cout << "[       OK ] " << name << std::endl;
                } else {
                    std::cout << "[  FAILED  ] " << name << std::endl;
                }
            }
        };

    };
};

#endif /* end of include guard */

