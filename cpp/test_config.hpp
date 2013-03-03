
#ifndef IUNIT_CPP_TEST_CONFIG_HPP
#define IUNIT_CPP_TEST_CONFIG_HPP

#include <string>
#include <cstdlib>
#include <ctime>


namespace iunit {
    class TestConfig {
        bool _shuffling;
        int _repeateCount;
        bool _useFilter;
    public:
        TestConfig() :
            _shuffling(false),
            _repeateCount(1),
            _useFilter(false)
        {
        }

        bool init(int argc, char const* argv[]) {
            srand((unsigned int)time(NULL));
            if( argc == 1 ) {
                return true;
            }
            for(int i=1; i < argc; ++i) {
                std::string str(argv[i]);
                if( str.find("-shuffle") != std::string::npos ) {
                    _shuffling = true;
                    continue;
                }
                if( str.find("-repeat") != std::string::npos ) {
                    size_t pos = str.find("=");
                    std::string count = str.substr(pos+1);
                    char* endptr = 0;
                    int value = std::strtol(count.c_str(), &endptr, 10);
                    if(!endptr || value <= 0) {
                        printUsage(argv[0]);
                        exit(1);
                    }
                    _repeateCount = value;
                    continue;
                }
                if( str.find("-filter") != std::string::npos ) {
                    _useFilter = true;
                    continue;
                }
                printUsage(argv[0]);
                exit(1);
            }

            return true;
        }
        
        void printUsage(const char* exe) const {
            std::cout << exe << " [option]" << std::endl;
            std::cout << std::endl;
            std::cout << "Option:" << std::endl;
            std::cout << "   -shuffle"<< std::endl;
            std::cout << "        Shuffle is performed as follows:\n"
                      << "          1. Execute any one test case "
                                       "that is included a test suite.\n"
                      << "          2. Executed test case execute the test function"
                                       " or test case that\n"
                      << "             is included in oneself in the random order."
                      << std::endl;
            std::cout << std::endl;
            std::cout << "   -repeat=count"<< std::endl;
            std::cout << "        Repeat a specified number of times.\n";
            std::cout << std::endl;
            std::cout << "   -filter=testPath"<< std::endl;
            std::cout << "       not support" << std::endl;
            std::cout << std::endl;
        }

        bool isShuffling() const {
            return _shuffling;
        }
        int repeateCount() const {
            return _repeateCount;
        }
        bool useFilter() const {
            return _useFilter;
        }
    };
};

#endif /* end of include guard */
