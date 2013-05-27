#ifndef IUNIT_CPP_DETAIL_TEST_OUTPUTTER_HPP
#define IUNIT_CPP_DETAIL_TEST_OUTPUTTER_HPP

#include "detail/test_result.hpp"


namespace iunit {
    namespace detail {
        
        class TestOutputter {
        public:
            TestOutputter() {}
            virtual ~TestOutputter() {}

            void write(const std::vector<TestResult*>& rootResult) {

                // 書き込みの開始を宣言し、
                // 全てのテスト結果を出力
                // 完了後、書き込み終了を宣言
                start();
                std::vector<TestResult*>::const_iterator ite = rootResult.begin();
                std::vector<TestResult*>::const_iterator endIte = rootResult.end();
                std::vector<TestResult*>::const_iterator lastIte = rootResult.end();
                lastIte--;
                for(; ite != endIte; ite++) {
                    output(*ite, ite == lastIte);
                }
                end();
            }

        private:
            virtual void output(TestResult* result, bool isLast) {
                // テスト結果が自信のみである場合は、書き込み
                if(result->_results.empty()) {
                    write(result);
                    return;
                }

                // 複数のテスト結果で構成されている場合は、書き込み開始を宣言
                // 自身に含まれる全てのテスト結果を出力
                start(result, isLast);
                std::vector<TestResult*>::iterator ite = result->_results.begin();
                std::vector<TestResult*>::iterator endIte = result->_results.end();
                std::vector<TestResult*>::iterator lastIte = result->_results.end();
                lastIte--;
                for(; ite != endIte; ite++) {
                    output(*ite, ite == lastIte);
                }
                end(result);

            }
            virtual void start(TestResult* result = NULL, bool last = false) = 0;
            virtual void end(TestResult* result = NULL) = 0;
            virtual void write(TestResult* result) = 0;
        };
    }
}

#endif /* end of include guard */
