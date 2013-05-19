
#ifndef IUNIT_CPP_TEST_CONFIG_HPP
#define IUNIT_CPP_TEST_CONFIG_HPP

#include <string>
#include <cstdlib>
#include <ctime>

#include "detail/test_util.hpp"

class PrintString {
public:
    void operator()(std::string str) {
        std::cout << str << std::endl;
    }
};

namespace iunit {
    class TestConfig {
        bool _shuffling;
        int _repeateCount;
        bool _useFilter;
        bool _printTestPath;
        std::set<std::string> _excludeFilter;
        std::set<std::string> _includeFilter;

        void error(const char* exe) {
            printUsage(exe);
            exit(1);
        }

        bool isExclude(const std::string& path) {
            return isContainerPath(path, _excludeFilter.begin(), _excludeFilter.end(), false);
        }
        bool isInclude(const std::string& path) {
            return isContainerPath(path, _includeFilter.begin(), _includeFilter.end(), true);
        }

        template <typename Iterator>
        bool isContainerPath(std::string path, Iterator begin, Iterator end, bool include) {
            path.append(1, '/');
            Iterator ite = begin;
            for(; ite != end; ++ite ) {
                std::string filter = *ite;
                if(filter.at(filter.length()-1) != '/') {
                    filter.append(1, '/');
                }

                if(path == filter) {
                    return true;
                }
                if(path.find(filter) == 0) {
                    return true;
                }
                if(include && (filter.find(path) == 0)) {
                    return true;
                }
            }
            return false;
        }

    public:
        TestConfig() :
            _shuffling(false),
            _repeateCount(1),
            _useFilter(false),
            _printTestPath(false)
        {
        }

        bool init(int argc, char const* argv[]) {
            srand((unsigned int)time(NULL));
            if( argc == 1 ) {
                return true;
            }
            for(int i=1; i < argc; ++i) {
                std::string str(argv[i]);
                if( str == "--shuffle" ) {
                    _shuffling = true;
                    continue;
                }
                if( str.find("--repeat", 0, 8) != std::string::npos ) {
                    size_t pos = str.find("=");
                    std::string count = str.substr(pos+1);
                    char* endptr = 0;
                    int value = std::strtol(count.c_str(), &endptr, 10);
                    if(!endptr || value <= 0) {
                        error(argv[0]);
                    }
                    _repeateCount = value;
                    continue;
                }
                if( str.find("--exclude", 0, 8) != std::string::npos ) {
                    _useFilter = true;
                    size_t pos = str.find("=");
                    if(pos == std::string::npos) {
                        error(argv[0]);
                    }
                    _excludeFilter = detail::util::splitFilter(str.substr(pos+1));
                    //PrintString printer;
                    //std::for_each(_filter.begin(), _filter.end(), printer);
                    continue;
                }
                if( str.find("--include", 0, 8) != std::string::npos ) {
                    _useFilter = true;
                    size_t pos = str.find("=");
                    if(pos == std::string::npos) {
                        error(argv[0]);
                    }
                    _includeFilter = detail::util::splitFilter(str.substr(pos+1));
                    //PrintString printer;
                    //std::for_each(_filter.begin(), _filter.end(), printer);
                    continue;
                }
                if( str == "--print-path" ) {
                    _printTestPath = true;
                    continue;
                }
                if(str == "--help" || str == "-h" ) {
                    printUsage(argv[0]);
                    exit(0);
                }
                error(argv[0]);
            }

            return true;
        }
        
        void printUsage(const char* exe) const {
            std::string name(exe);
            name = name.substr(name.rfind("/")+1);
            std::cout << "Usage: " << name << " [Option]" << std::endl;
            //std::cout << std::endl;
            std::cout << "Option:" << std::endl;
            std::cout << "   --exclude=testPath"<< std::endl;
            std::cout << "        You can specify the test path that you want to exclude." << std::endl;
            std::cout << "        Exclusion target can specify multiple by the comma separated." << std::endl;
            std::cout << "        TestPath : /Suite name/Test name/Test name/...[,/Suite name/Test name/..." << std::endl;
            std::cout << "   --include=testPath"<< std::endl;
            std::cout << "        You can specify the test path that you want to include always." << std::endl;
            std::cout << "        This test is executed, even if you specified to exclude it." << std::endl;
            std::cout << "        Inclusion target can specify multiple by the comma separated." << std::endl;
            std::cout << "        TestPath : /Suite name/Test name/Test name/...[,/Suite name/Test name/..." << std::endl;
            //std::cout << std::endl;
            std::cout << "   --print-path"<< std::endl;
            std::cout << "        Show the test path." << std::endl;
            //std::cout << std::endl;
            std::cout << "   --repeat=count"<< std::endl;
            std::cout << "        Repeat a specified number of times.\n";
            //std::cout << std::endl;
            std::cout << "   --shuffle"<< std::endl;
            std::cout << "        Shuffle is performed as follows:\n"
                      << "          1. Execute any one test case "
                                       "that is included a test suite.\n"
                      << "          2. Executed test case execute the test function"
                                       " or test case that\n"
                      << "             is included in oneself in the random order."
                      << std::endl;
            //std::cout << std::endl;
            std::cout << "   --help -h"<< std::endl;
            std::cout << "        Display Usage. " << std::endl;
            std::cout << std::endl;
        }

        bool isShuffling() const {
            return _shuffling;
        }
        int repeateCount() const {
            return _repeateCount;
        }
        bool isUseFilter() const {
            return _useFilter;
        }
        bool isPrintPath() const {
            return _printTestPath;
        }
        bool isSkipTest(const std::string& path) {
            if(isExclude(path)) {
                return !isInclude(path);
            }
            std::cout << path << " is not skip." << std::endl;
            return false;
        }
    };
};

#endif /* end of include guard */
