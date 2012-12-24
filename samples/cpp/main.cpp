
#include <iostream>
#include <test_case.hpp>
#include <test_suite.hpp>
#include <test_text_outputter.hpp>
#include <test_junit_outputter.hpp>
#include <test_macros.hpp>

#include <fstream>

using namespace iunit;

class SampleTest : public CppTestCase {
public:
    SampleTest() : CppTestCase("SampleTest") {
    }

    virtual void setup() {}
    virtual void teardown() {}
    
    int value() const {
        return 2;
    }

    void test_plus() {
        IUNIT_MESSAGE( "Test Plus" );
        IUNIT_EQ(value(), 2);
        IUNIT_ASSERT_EQ(value(), 2);
        IUNIT_WARN_EQ(value(), 2);
        IUNIT_NE(value(), 3);
        IUNIT_ASSERT_NE(value(), 3);
        IUNIT_WARN_NE(value(), 3);
        int* a = new int(1);
        IUNIT_NULL(NULL);
        IUNIT_ASSERT_NULL(NULL);
        IUNIT_WARN_NULL(NULL);
        IUNIT_NOT_NULL(a);
        IUNIT_ASSERT_NOT_NULL(a);
        IUNIT_WARN_NOT_NULL(a);
        delete a;
        
        IUNIT_LE(2, 3)
        IUNIT_LT(2, 1)
        IUNIT_GE(2, 3)
        IUNIT_GT(2, 3)
        IUNIT_ASSERT_LE(2, 1)
        IUNIT_ASSERT_LT(2, 1)
        IUNIT_ASSERT_GE(2, 3)
        IUNIT_ASSERT_GT(2, 3)
    }
    void test_minus() {
    }
    
    virtual void init() {
        IUNIT_ADD_TEST( SampleTest::test_plus );
        IUNIT_ADD_TEST( SampleTest::test_minus );
        //addTest(this, &SampleTest::test_plus , "SampleTest::test_plus" );
    }
};

class SampleSuite : public CppTestSuite {
public:
    SampleSuite(const std::string& name, CppTestResultCollector* collector = NULL) 
        : CppTestSuite(name, collector)
    {
    }
    virtual void init() {
        addTest(new SampleTest());
    }
};

int main(int argc, char const* argv[])
{
    CppTestResultCollector collector;
    CppTestSuite suite("TestSuite", &collector);
    suite.addTest(new SampleTest());
    suite.start();

    //original test suite
    //SampleSuite sampleSuite("SampleSuite", &collector);
    //sampleSuite.run();

    std::ofstream ofs("result.txt");
    TextOutputter outputter(ofs);
    JUnitOutputter outputter2(std::cout);
    collector.write(&outputter2);
    collector.write(&outputter);
    return (collector.isSuccessful() ? 0 : -1);
}

