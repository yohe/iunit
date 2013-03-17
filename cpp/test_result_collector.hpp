#ifndef IUNIT_CPP_TEST_RESULT_COLLECTOR_HPP
#define IUNIT_CPP_TEST_RESULT_COLLECTOR_HPP

#include <vector>
#include "detail/test_outputter.hpp"

namespace iunit {

    class CppTestResultCollector {
    protected:
        std::vector<detail::TestResult*> _rootResult;
        bool _isSuccess;

    public:
        CppTestResultCollector() :
            _isSuccess(true)
        {
        }
        virtual ~CppTestResultCollector() {
            clear();
        }
        
        virtual void clear() {
            std::vector<detail::TestResult*>::iterator ite = _rootResult.begin();
            for(; ite != _rootResult.end(); ite++) {
                delete *ite;
            }
            _rootResult.clear();
        }

        virtual void addResult(detail::TestResult* ret) {
            _isSuccess &= ret->isSuccess();
            _rootResult.push_back(ret);
        }
        
        virtual bool isSuccessful() const {
            return _isSuccess;
        }

        virtual void write(detail::TestOutputter* outputter) {
            outputter->write(_rootResult);
        }
        
        virtual size_t size() const {
            return _rootResult.size();
        }

    protected:
    };

};

#endif /* end of include guard */
