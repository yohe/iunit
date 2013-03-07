
#include <iostream>
#include <test_case.hpp>
#include <test_suite.hpp>
#include <test_text_outputter.hpp>
#include <test_junit_outputter.hpp>
#include <test_macros.hpp>
#include <test_config.hpp>

#include <fstream>

using namespace iunit;

class SampleTest2 : public CppTestCase {
public:
    SampleTest2() : CppTestCase("SampleTest2") {
    }

    virtual void setup() {
        //std::cout << _name << "-Setup" << std::endl;
    }
    virtual void teardown() {
        //std::cout << _name << "-Teardown" << std::endl;
    }
    
    int value() const {
        return 2;
    }

    void test_1() {
        IUNIT_MESSAGE( "Test 1 Start" );
        IUNIT_EQ(value(), 2);
        IUNIT_ASSERT_EQ(value(), 2);
        IUNIT_NE(value(), 3);
        IUNIT_ASSERT_NE(value(), 3);
        int* a = new int(1);
        IUNIT_MESSAGE("int* a = new int(1)");
        IUNIT_NULL(NULL);
        IUNIT_ASSERT_NULL(NULL);
        IUNIT_NOT_NULL(a);
        IUNIT_ASSERT_NOT_NULL(a);
        sleep(2);
        delete a;
    }
    void test_2() {
        IUNIT_MESSAGE( "Test 2 Start" );
        IUNIT_LE(2, 2)
        IUNIT_LT(2, 1)
        IUNIT_GE(2, 2)
        IUNIT_GT(2, 3)
        IUNIT_ASSERT_LE(2, 1)
        IUNIT_ASSERT_LT(2, 1)
        IUNIT_ASSERT_GE(2, 3)
        IUNIT_ASSERT_GT(2, 3)
        sleep(1);
    }
    void test_3() {
        IUNIT_MESSAGE( "Test 3 Start" );
    }
    
    virtual void init() {
        IUNIT_ADD_TEST( SampleTest2, test_1 );
        IUNIT_ADD_TEST( SampleTest2, test_2 );
        IUNIT_ADD_TEST( SampleTest2, test_3 );
        //addTest(this, &SampleTest::test_plus , "SampleTest::test_plus" );
    }
};

class SampleTest : public CppTestCase {
    int value;
public:
    SampleTest() : CppTestCase("SampleTest") {
    }

    virtual void setup() {
        //std::cout << _name << "-Setup" << std::endl;
        value = 5;
    }
    virtual void teardown() {
        //std::cout << _name << "-Teardown" << std::endl;
        value = 0;
    }

    void plus(int x) {
        value += x;
    }
    void minus(int x) {
        value -= x;
    }

    void test_plus() {
        IUNIT_MESSAGE( "Test Plus Start" );
        IUNIT_EQ(value, 5);
        plus(1);
        IUNIT_EQ(value, 6);
    }
    void test_minus() {
        IUNIT_MESSAGE( "Test minus Start" );
        IUNIT_EQ(value, 5);
        minus(1);
        IUNIT_EQ(value, 4);
    }
    
    virtual void init() {
        IUNIT_ADD_TEST( SampleTest, test_plus );
        IUNIT_ADD_TEST( SampleTest, test_minus );
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
    TestConfig config;
    config.init(argc, argv);
    CppTestResultCollector collector;
    CppTestSuite suite("TestSuite", &collector);
    suite.addTest(new SampleTest());
    suite.addTest(new SampleTest2());
    suite.config(config);
    suite.start();

    //original test suite
    //SampleSuite sampleSuite("SampleSuite", &collector);
    //sampleSuite.start();

    std::ofstream xml_ofs("result.xml");
    std::ofstream ofs("result.txt");
    TextOutputter outputter(ofs);
    JUnitOutputter outputter2(xml_ofs);
    collector.write(&outputter2);
    collector.write(&outputter);
    return (collector.isSuccessful() ? 0 : -1);
}

