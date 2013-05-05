
#include <iostream>
#include <test_suite.hpp>
#include <test_case.hpp>
#include <test_text_outputter.hpp>
#include <test_junit_outputter.hpp>
#include <test_macros.hpp>
#include <test_config.hpp>
#include <test_io_tester.hpp>

#include <fstream>
#include <exception>

using namespace iunit;

class SampleFixture : public TestFixture {
public:
    virtual void setup() {
        std::cout << "SampleTest2Fixture::setup()" << std::endl;
    }
    virtual void teardown() {
        std::cout << "SampleTest2Fixture::teardown()" << std::endl;
    }
};
class SampleTest2 : public CppTestCase {
public:
    SampleTest2(SampleFixture* fixture) : CppTestCase("SampleTest2", fixture) {
    }

    int value() const {
        return 2;
    }
    void throwException() const throw (std::exception){
        throw std::exception();
    }

    void test_1() {
        IUNIT_MESSAGE( "Test 1 Start" );
        int* a = new int(1);
        IUNIT_EQ(2, value());
        IUNIT_ASSERT_EQ(2, value());
        IUNIT_NE(3, value());
        IUNIT_ASSERT_NE(value(), 3);
        IUNIT_MESSAGE("int* a = new int(1)");
        IUNIT_NULL(NULL);
        IUNIT_ASSERT_NULL(NULL);
        IUNIT_NOT_NULL(a);
        IUNIT_ASSERT_NOT_NULL(a);
        delete a;
    }
    void test_2() {
        IUNIT_MESSAGE( "Test 2 Start" );
        IUNIT_LE(2, value());
        IUNIT_LT(2, value()-1);
        IUNIT_GE(2, value());
        IUNIT_GT(2, value()+1);
        IUNIT_ASSERT_LE(2, 2);
        IUNIT_ASSERT_LT(2, 1);
        IUNIT_ASSERT_GE(2, 2);
        IUNIT_ASSERT_GT(2, 3);
    }
    void test_3() {
        IUNIT_MESSAGE( "Test 3 Start" );
        IUNIT_TRUE( 1==2 );
        IUNIT_FALSE( 1==2 );
        IUNIT_ASSERT_TRUE( 1==1 );
        IUNIT_ASSERT_FALSE( 1==2 );
    }
    void test_4() {
        IUNIT_MESSAGE( "Test 4 Start" );
        IUNIT_THROW(throwException(), std::exception);
        IUNIT_NO_THROW(value());
        IUNIT_ASSERT_THROW(throwException(), std::exception);
        IUNIT_ASSERT_NO_THROW(value());
        //IUNIT_NO_THROW(throwException());
        //IUNIT_THROW(value(), std::exception);
        //IUNIT_ASSERT_NO_THROW(throwException());
        //IUNIT_ASSERT_THROW(value(), std::exception);
        //IUNIT_TEST(a)_Should_EQ((int*)0);
        //IUNIT_TEST(a)_Should_NE((int*)0);
        //IUNIT_TEST(a)_Should_THROW((int*)0);
        //IUNIT_TEST(a)_Should_NOT_THROW((int*)0);

    }
    
    virtual void init() {
        IUNIT_ADD_TEST( SampleTest2, test_1 );
        IUNIT_ADD_TEST( SampleTest2, test_2 );
        IUNIT_ADD_TEST( SampleTest2, test_3 );
        IUNIT_ADD_TEST( SampleTest2, test_4 );
        //addTest(this, &SampleTest::test_plus , "SampleTest::test_plus" );
    }
};

class SampleTest : public CppTestCase {
    int value;

public:
    SampleTest() : CppTestCase("SampleTest") {
        value = 0;
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
    void test_pattern() {
        IUNIT_MESSAGE( "Test pattern Start" );

        PatternData data;
        std::vector<std::pair<PatternData, bool> > spec;
        data.x = 1; data.y = 1, data.z = 1;
        spec.push_back(std::pair<PatternData, bool>(data, true));
        data.x = 1; data.y = 1, data.z = 2;
        spec.push_back(std::pair<PatternData, bool>(data, false));
        data.x = 1; data.y = 2, data.z = 1;
        spec.push_back(std::pair<PatternData, bool>(data, false));
        data.x = 1; data.y = 2, data.z = 2;
        spec.push_back(std::pair<PatternData, bool>(data, false));
        XyzFunctor func(this);
        IOPatternTester<PatternData, bool, XyzFunctor> tester(spec, func, "XyzPatternTest");
        IUNIT_PATTERN_TESTER(tester);

        sleep(2);
    }

    bool xyz(int x, int y, int z) {
        if(x == y && x == z) {
            return true;
        } else {
            return false;
        }
    }

    virtual void init() {
        IUNIT_ADD_TEST( SampleTest, test_plus );
        IUNIT_ADD_TEST( SampleTest, test_minus );
        IUNIT_ADD_TEST( SampleTest, test_pattern );
    }
private:
    struct PatternData {
        int x;
        int y;
        int z;
    };
    class XyzFunctor {
        SampleTest* _obj;
    public:
        XyzFunctor(SampleTest* obj) : _obj(obj) {}
        bool operator()(PatternData p) {
            std::stringstream ss;
            ss << "X = " << p.x << ", Y = " << p.y << ", Z = " << p.z;
            IUNIT_MESSAGE_OUTSIDE_TEST(_obj, ss.str());
            return _obj->xyz(p.x, p.y, p.z);
        }
    };
};

class SuiteFixture : public TestFixture {
public:
    virtual void setup() {
        std::cout << "SuiteFixture::setup()" << std::endl;
    }
    virtual void teardown() {
        std::cout << "SuiteFixture::teardown()" << std::endl;
    }
};
class SampleSuite : public CppTestSuite {
public:
    SampleSuite(const std::string& name, CppTestResultCollector& collector) 
        : CppTestSuite(name, collector, NULL)
    {
    }
protected:
    virtual void init() {
        addTest(new SampleTest());
    }
};

int main(int argc, char const* argv[])
{
    TestConfig config;
    SuiteFixture fixture;
    config.init(argc, argv);
    CppTestResultCollector collector;
    CppTestSuite suite("TestSuite", collector, &fixture);
    suite.addTest(new SampleTest());
    
    SampleFixture sampleFixture;
    suite.addTest(new SampleTest2(&sampleFixture));
    suite.config(config);
    suite.start();

    //original test suite
    //SampleSuite sampleSuite("SampleSuite", &collector);
    //sampleSuite.start();

    std::ofstream xml_ofs("result.xml");
    std::ofstream ofs("result.txt");
    TextOutputter outputter(ofs);
    JUnitOutputter outputter2(xml_ofs);
    collector.write(&outputter);
    collector.write(&outputter2);
    return (collector.isSuccessful() ? 0 : -1);
}

