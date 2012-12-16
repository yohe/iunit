#ifndef CPP_TEST_MACROS_HPP
#define CPP_TEST_MACROS_HPP

#define ADD_TEST(method) \
    addTest(this, &method, #method)

#endif /* end of include guard */
