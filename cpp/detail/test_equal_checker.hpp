#ifndef IUNIT_CPP_DETAIL_TEST_EQUAL_CHECKER_HPP
#define IUNIT_CPP_DETAIL_TEST_EQUAL_CHECKER_HPP

#include <functional>

namespace iunit {
    namespace detail {
        class EqualChecker {
        public:

            template<class LT>
            static bool equal(const LT& lhs, const LT& rhs) {
                std::equal_to<LT> comp;
                if(comp.operator()(lhs, rhs)) {
                    return true;
                } else {
                    return false;
                }
            }
            template<class LT>
            static bool equalNull(const LT* lhs) {
                if(lhs == (LT*)NULL) {
                    return true;
                }
                return true;
            }
        };
        
        class CheckFunctor {
        public:
            CheckFunctor(const char* actualStr, const char* filename, int line) : 
                _actualStr(actualStr), _filename(filename), _line(line)
            {
            }

            template <class T, class X>
            bool operator()(T actual, X expected) {
                if( actual == expected ) {
                    return true;
                } else {
                    return false;
                }
            }
            
            const char* _actualStr;
            const char* _filename;
            int _line;
        };
    }
}

#endif /* end of include guard */
