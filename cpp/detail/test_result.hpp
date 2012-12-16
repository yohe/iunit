#ifndef IUNIT_CPP_DETAIL_TEST_RESULT_HPP
#define IUNIT_CPP_DETAIL_TEST_RESULT_HPP

namespace iunit {
    namespace detail {
        class TestResult {
        public:
            TestResult() : _name(""), _success(0), _failed(0)
            {
            }
            
            bool isSuccess() const {
                return true;
            }
            
            void add(TestResult* child) {
            }

            void set(const std::string& name, size_t success, size_t failed) {
            }

            std::string _name;
            size_t _success;
            size_t _failed;
        };
    };
};

#endif /* end of include guard */

