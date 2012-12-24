#ifndef IUNIT_CPP_TEST_RESULT_COLLECTOR_HPP
#define IUNIT_CPP_TEST_RESULT_COLLECTOR_HPP

#include <vector>
#include "detail/test_result.hpp"
#include "detail/test_outputter.hpp"

namespace iunit {

    using namespace detail;

    class CppTestResultCollector {
    protected:
        std::vector<TestResult*> _rootResult;
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
            std::vector<TestResult*>::iterator ite = _rootResult.begin();
            for(; ite != _rootResult.end(); ite++) {
                delete *ite;
            }
            _rootResult.clear();
        }

        virtual void addResult(TestResult* ret) {
            _isSuccess &= ret->isSuccess();
            _rootResult.push_back(ret);
        }
        
        virtual bool isSuccessful() const {
            return _isSuccess;
        }

        virtual void write(TestOutputter* outputter) {
            outputter->start();
            std::vector<TestResult*>::iterator ite = _rootResult.begin();
            std::vector<TestResult*>::iterator end = _rootResult.end();
            for(; ite != end; ite++) {
                output(outputter, *ite);
            }
            outputter->end();
        }
        
        virtual size_t size() const {
            return _rootResult.size();
        }

    protected:
        virtual void output(TestOutputter* outputter, TestResult* result) {
            if(result->_results.empty()) {
                outputter->write(result);
                return;
            }

            outputter->start(result);
            std::vector<TestResult*>::iterator ite = result->_results.begin();
            std::vector<TestResult*>::iterator end = result->_results.end();
            for(; ite != end; ite++) {
                output(outputter, *ite);
            }
            outputter->end(result);

        }
    };

};

#endif /* end of include guard */
