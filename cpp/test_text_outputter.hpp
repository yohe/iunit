
#ifndef IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP

#include <ostream>
#include "detail/test_outputter.hpp"

namespace iunit {

    using namespace detail;

    class TextOutputter : public TestOutputter {
    public:
        TextOutputter(std::ostream& os) : _os(os), _indentCount(0) {
            _os.precision(3);
            _os << std::fixed;
        }

        virtual void start(TestResult* result = NULL, bool last = false) {
            if(result == NULL) {
                return;
            }

            std::string indent = "";
            for(int i = 0; i < _indentCount; ++i) {
                if(i==0) {
                    indent += "    ";
                } else {
                    indent += "  ";
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

            _indentCount++;
        }

        virtual void write(TestResult* result) {
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

            if(result->isSuccess()) {
                // nop
            } else {
                std::string message = result->message();
                std::string messageIndent = indent+indent+ " >  ";
                indentMessage(message, messageIndent);
                _os << messageIndent << message << std::endl;
            }
        }

        virtual void end(TestResult* result = NULL) {
            _indentCount--;
            if(result == NULL) {
                return;
            }

            std::string indent;
            for(int i = 0; i < _indentCount; ++i) {
                indent += "  ";
            }
        }
    protected:
        virtual void indentMessage(std::string& message, const std::string& indent) {
            size_t pos = message.find('\n');
            while( pos != std::string::npos) {
                message.insert(pos+1, indent);
                pos = message.find('\n', pos+1+indent.size());
            }
        }

        std::ostream& _os;
        int _indentCount;
    };

};

#endif /* end of include guard */

