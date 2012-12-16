#ifndef IUNIT_CPP_TEST_FIXTURE_HPP
#define IUNIT_CPP_TEST_FIXTURE_HPP

namespace iunit {
    class TestFixture {
    public:
        TestFixture() {}
        virtual ~TestFixture() {}
        virtual void setup() = 0;
        virtual void teardown() = 0;
    };
};


#endif /* end of include guard */
