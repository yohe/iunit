
#ifndef IUNIT_CPP_TEST_COMPILER_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_COMPILER_OUTPUTTER_HPP

#include <ostream>
#include "detail/test_outputter.hpp"

namespace iunit {

    class CompilerOutputter : public detail::TestOutputter {
    public:
        CompilerOutputter(std::ostream& os) : _os(os), _indentCount(0) {
            _os.precision(3);
            _os << std::fixed;
        }

        virtual void start(detail::TestResult* result = NULL, bool last = false) {
            //if(result == NULL) {
            //    return;
            //}

            //std::string indent = "";
            //for(int i = 0; i < _indentCount; ++i) {
            //    indent += "    ";
            //}
            //indent += " ";
            //
            //if(result->isSuccess()) {
            //    _os << "[O]";
            //} else {
            //    _os << "[X]";
            //}
            //
            //_os << " " << indent << result->testName() << " : " 
            //    << result->getRunTime() << "[ms]"<< std::endl;

            //_indentCount++;
        }

        virtual void write(detail::TestResult* result) {
            if(!result->isSuccess()) {
                _os << result->getErrorFilename() << ":" << result->getErrorLine() << ": ";
                std::string exception = result->exceptionMessage();
                _os << exception << std::endl;
            }
        }

        virtual void end(detail::TestResult* result = NULL) {
            //_indentCount--;
            //if(result == NULL) {
            //    return;
            //}
        }
    protected:
        virtual void indentMessage(std::string& message, const std::string& indent) {
            message.insert(0, indent);
            size_t pos = message.find('\n');
            while( pos != std::string::npos) {
                message.insert(pos+1, indent);
                pos = message.find('\n', pos+1+indent.size());
            }
        }

        std::ostream& _os;
        int _indentCount;
    };

}


#endif
