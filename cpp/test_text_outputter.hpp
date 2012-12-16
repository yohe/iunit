
#ifndef IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP
#define IUNIT_CPP_TEST_TEXT_OUTPUTTER_HPP

#include <fstream>
#include "detail/test_outputter.hpp"

namespace iunit {

    using namespace detail;

    class TextOutputter : public TestOutputter {
    public:
        TextOutputter(std::ofstream& ofs) : _ofs(ofs) {}

        virtual void start(TestResult* result = NULL) {
        }

        virtual void write(TestResult* result) {
        }

        virtual void end(TestResult* result = NULL) {
        }

    private:
        std::ofstream& _ofs;
    };

};

#endif /* end of include guard */

