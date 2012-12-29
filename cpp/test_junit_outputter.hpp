
#ifndef IUNIT_CPP_TEST_JUNIT_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_JUNIT_OUTPUTTER_HPP

#include <cassert>
#include <fstream>
#include "test_text_outputter.hpp"

namespace iunit {

    using namespace detail;

    class JUnitOutputter : public TextOutputter {
    public:
        JUnitOutputter(std::ostream& os) : TextOutputter(os), _index(0) {}

        virtual void start(TestResult* result = NULL) {
            assert(_indentCount < 2);

            if(result == NULL) {
                _os << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
                return;
            }
            if(_indentCount == 0) {
                _os << "<testsuites>" << std::endl;
            } else {
                std::string iso_timestamp = "0";

                std::string indent;
                for(int i = 0; i < _indentCount; ++i) {
                    indent += "  ";
                }
                _os << indent 
                    << "<testsuite tests=\"" << result->testName()
                    << "\" failures=\"" << 0
                    << "\" errors=\"" << result->_failed
                    << "\" name=\"" << result->testName()
                    << "\" time=\"" << 0
                    << "\" timestamp=\"" << iso_timestamp
                    << "\" hostname=\""
                    << "\" package=\""
                    << "\" id=\"" << _index << "\" >" << std::endl;

                _os << indent << indent << "<properties />" << std::endl;

                _index++;
            }

            _indentCount++;
        }

        virtual void write(TestResult* result) {

            std::string indent;
            for(int i = 0; i < _indentCount; ++i) {
                indent += "  ";
            }

            _os << indent
                << "<testcase name=\"" << result->testMethodName()
                << "\" classname=\"" << result->testName()
                << "\" time=\"" << 0 << "\">" << std::endl;

            if(!result->isSuccess()) {
                _os  << indent << "  <failure message=\""
                     << result->message() << "\" type=\"\"/>"
                     << std::endl;
            }
            _os << indent << "</testcase>" << std::endl;
        }

        virtual void end(TestResult* result = NULL) {
            if(result == NULL) {
                _os << std::endl;
                return;
            }

            _indentCount--;

            if(_indentCount == 0) {
                _os << "</testsuites>" << std::endl;
            } else {
                std::string indent;
                for(int i = 0; i < _indentCount; ++i) {
                    indent += "  ";
                }

                _os << indent << indent << "<system-out />" << std::endl;
                _os << indent << indent << "<system-err />" << std::endl;
                _os << indent << "</testsuite>" << std::endl;
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

    private:
        int _index;
    };

};

#endif /* end of include guard */

