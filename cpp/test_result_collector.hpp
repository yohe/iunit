#ifndef IUNIT_CPP_TEST_RESULT_COLLECTOR_HPP
#define IUNIT_CPP_TEST_RESULT_COLLECTOR_HPP

#include <vector>
#include "detail/test_result.hpp"
#include "detail/test_outputter.hpp"

namespace iunit {

    using namespace detail;

    class CppTestResultCollector {
    public:
        CppTestResultCollector() :
            _isSuccess(true)
        {
        }
        virtual ~CppTestResultCollector() {
            clear();
        }
        
        virtual void clear() {
            std::vector<TestResult*>::iterator ite = _testResult.begin();
            for(; ite != _testResult.end(); ite++) {
                delete *ite;
            }
            _testResult.clear();
        }

        virtual void addResult(TestResult* ret) {
            _isSuccess &= ret->isSuccess();
            _testResult.push_back(ret);
        }
        
        virtual bool isSuccessful() const {
            return _isSuccess;
        }

        virtual void write(TestOutputter* outputter) {
        }
        
        virtual size_t size() const {
            return _testResult.size();
        }
    protected:
        std::vector<TestResult*> _testResult;
        bool _isSuccess;
    };

};

#endif /* end of include guard */
