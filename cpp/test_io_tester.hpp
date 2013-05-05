
#ifndef IUNIT_CPP_TEST_IO_TESTER_HPP
#define IUNIT_CPP_TEST_IO_TESTER_HPP

#include <algorithm>
#include <vector>
#include <map>
#include <string>

#include "cpp/detail/test_exception.hpp"
#include "cpp/detail/test_runnable.hpp"
#include "cpp/test_macros.hpp"

namespace iunit {

    template<typename In,
             typename Out,
             typename Functor,
             typename ExceptionType = detail::ErrorException>
    class IOPatternTester {
        typedef std::vector<std::pair<In, Out> > Spec;
        Spec _spec;
        Functor _func;
        std::string _testName;

    public:
        IOPatternTester(std::vector<std::pair<In, Out> > spec,
                        Functor func,
                        std::string testName) :
            _spec(spec),
            _func(func),
            _testName(testName)
        {
        }

        void test(detail::TestRunnable* owner, const char* file, size_t line) {
            typename Spec::iterator ite = _spec.begin();
            typename Spec::iterator end = _spec.end();

            for(size_t i=1; ite != end; ite++, i++) {
                const Out ret = _func(ite->first);
                if (ite->second != ret) {
                    owner->failed();
                    std::stringstream ss;
                    ss << ExceptionType::getExceptionType() 
                       << " :            " << _testName <<" failed. Pattern No." << i << std::endl;
                    throw ExceptionType(ss.str(), file, line);
                }
            }
        }
    };

};

#endif /* end of include guard */
