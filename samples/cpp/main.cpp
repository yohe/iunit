
#include <iostream>
#include <test_case.hpp>
#include <test_suite.hpp>
#include <test_text_outputter.hpp>
#include <test_macros.hpp>

#include <fstream>

using namespace iunit;

class SampleTest : public CppTestCase {
public:
    SampleTest() : CppTestCase("Sample") {
    }

    virtual void setup() {}
    virtual void teardown() {}

    void test_plus() {
        IUNIT_MESSAGE( "Test Plus" );
    }
    void test_minus() {
    }
    
    virtual void init() {
        IUNIT_ADD_TEST( SampleTest::test_plus );
        IUNIT_ADD_TEST( SampleTest::test_minus );
        //addTest(this, &SampleTest::test_plus , "SampleTest::test_plus" );
    }
};


int main(int argc, char const* argv[])
{
    CppTestResultCollector collector;
    CppTestSuite suite("TestSuite", &collector);
    suite.addTest(new SampleTest());
    suite.run();

    std::ofstream ofs("result.txt");
    TextOutputter outputter(ofs);
    collector.write(&outputter);
    return collector.isSuccessful();
}

