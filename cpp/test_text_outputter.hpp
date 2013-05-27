
#ifndef IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP

#include <ostream>
#include "detail/test_outputter.hpp"

namespace iunit {

    class TextOutputter : public detail::TestOutputter {
    public:
        TextOutputter(std::ostream& os) : _os(os), _indentCount(0) {
            _os.precision(3);
            _os << std::fixed;
        }

        virtual void start(detail::TestResult* result = NULL, bool last = false) {
            if(result == NULL) {
                return;
            }

            std::string indent = "";
            for(int i = 0; i < _indentCount; ++i) {
                indent += "    ";
            }
            indent += " ";
            
            if(result->isSuccess()) {
                _os << "[O]";
            } else {
                _os << "[X]";
            }
            
            _os << " " << indent << result->testName() << " : " 
                << result->getRunTime() << "[ms]"<< std::endl;

            _indentCount++;
        }

        virtual void write(detail::TestResult* result) {
            std::string indent = "";
            for(int i = 0; i < _indentCount; ++i) {
                if(i == (_indentCount-1)) {
                    indent += "    ";
                } else {
                    indent += "    ";
                }
            }
            indent += " ";

            if(result->isSuccess()) {
                _os << "[O]";
            } else {
                _os << "[X]";
            }

            _os << " " << indent << result->testName() << " : "
                << result->getRunTime() << "[ms]"<< std::endl;

            std::string messageIndent = indent+indent+ " >  ";
            std::string message = result->message();
            indentMessage(message, messageIndent);
            _os << message << std::endl;

            if(!result->isSuccess()) {
                _os << messageIndent << "[Exception]" << std::endl;
                std::string exception = result->exceptionMessage();
                indentMessage(exception, messageIndent);
                _os << exception << std::endl;
            }
        }

        virtual void end(detail::TestResult* result = NULL) {
            _indentCount--;
            if(result == NULL) {
                return;
            }
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

#endif /* end of include guard */

