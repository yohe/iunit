
#ifndef IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP

#include <ostream>
#include "detail/test_outputter.hpp"

namespace iunit {

    using namespace detail;

    class TextOutputter : public TestOutputter {
    public:
        TextOutputter(std::ostream& os) : _os(os), _indentCount(0) {}

        virtual void start(TestResult* result = NULL) {
            if(result == NULL) {
                return;
            }

            std::string indent;
            for(int i = 0; i < _indentCount; ++i) {
                indent += "  ";
            }
            
            _os << " ";
            if(result->isSuccess()) {
                _os << " ";
            } else {
                _os << "X";
            }
            _os << indent << " " << result->testName() << std::endl;

            _indentCount++;
        }

        virtual void write(TestResult* result) {
            std::string indent;
            for(int i = 0; i < _indentCount; ++i) {
                indent += "  ";
            }

            _os << " ";
            if(result->isSuccess()) {
                _os << " ";
            } else {
                _os << "X";
            }
            _os << indent << " " << result->testMethodName() << std::endl;

            std::string message = result->message();
            std::string messageIndent = indent+indent+ "   ";
            indentMessage(message, messageIndent);
            _os << messageIndent << message << std::endl;
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

