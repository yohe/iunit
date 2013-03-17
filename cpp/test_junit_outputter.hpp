
#ifndef IUNIT_CPP_TEST_JUNIT_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_JUNIT_OUTPUTTER_HPP

#include <cassert>
#include <fstream>
#include "test_text_outputter.hpp"

namespace iunit {

    class JUnitOutputter : public TextOutputter {
    public:
        JUnitOutputter(std::ostream& os) : TextOutputter(os), _index(0) {
            _os.precision(3);
            _os << std::fixed;
        }

        virtual void start(detail::TestResult* result = NULL, bool last = false) {
            assert(_indentCount < 2);

            if(result == NULL) {
                _os << "<?xml version='1.0' encoding='UTF-8'?>" << std::endl;
                return;
            }
            if(_indentCount == 0) {
                _os << "<testsuites name=\"" << result->_testName << "\">" << std::endl;
            } else {

                std::string indent;
                for(int i = 0; i < _indentCount; ++i) {
                    indent += "  ";
                }
                size_t tests = result->_success + result->_failed;
                _os << indent 
                    << "<testsuite tests=\"" << tests
                    << "\" errors=\"" << result->_failed
                    << "\" name=\"" << result->testName()
                    << "\" time=\"" << result->getRunTime()
                    << "\" id=\"" << _index << "\" >" << std::endl;

                _os << indent << indent << "<properties />" << std::endl;

                _index++;
            }

            _indentCount++;
        }

        virtual void write(detail::TestResult* result) {

            std::string indent;
            for(int i = 0; i < _indentCount; ++i) {
                indent += "  ";
            }

            size_t p = result->testName().find(":");
            std::string className = result->testName().substr(0, p);
            std::string methodName = result->testName().substr(p+2);
            _os << indent
                << "<testcase "
                << "classname=\"" << className
                << "\" name=\"" << methodName
                << "\" time=\"" << result->getRunTime()
                << "\">" << std::endl;

            if(!result->isSuccess()) {
                _os  << indent << "  <failure message=\""
                     << result->_exceptionMessage
                     << "\" type=\"\">"
                     << std::endl;
                //_os << result->message() << std::endl;
                _os << indent << "  </failure>" << std::endl;
            }
                _os << indent << indent << "<system-out>" << std::endl;
                _os << result->message() << std::endl;
                _os << indent << indent << "<system-out />" << std::endl;
                _os << indent << indent << "<system-err />" << std::endl;
            _os << indent << "</testcase>" << std::endl;
        }

        virtual void end(detail::TestResult* result = NULL) {
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

