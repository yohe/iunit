#ifndef IUNIT_CPP_DETAIL_TEST_TIMER_HPP
#define IUNIT_CPP_DETAIL_TEST_TIMER_HPP

#include <sys/time.h>
#include <string>

namespace iunit {
    namespace detail {
        class Timer {
        public:

            Timer() {}
            virtual ~Timer() {}

            double now() const {
                struct timeval t;
                gettimeofday(&t, NULL);
                return (double)t.tv_sec + ((double)t.tv_usec * 1e-6);
            }
            void now_tm(tm* timestamp) const {
                time_t rawtime;
                time(&rawtime);
                struct tm* src = NULL;
                src = localtime(&rawtime);
                copy_tm(src, timestamp);
            }

        private:
            void copy_tm(tm* src, tm* dst) const {
                dst->tm_sec = src->tm_sec;
                dst->tm_min = src->tm_min;
                dst->tm_hour = src->tm_hour;
                dst->tm_mday = src->tm_mday;
                dst->tm_mon = src->tm_mon;
                dst->tm_year = src->tm_year;
                dst->tm_wday = src->tm_wday;
                dst->tm_yday = src->tm_yday;
                dst->tm_isdst = src->tm_isdst;
            }
        };

        class CountUpTimer : public Timer {

            /**
             * カウントアップタイマ
             * set()後からの経過時間を測る機能
             */

        public:
            CountUpTimer() : Timer(){
                _setTime = 0.0;
                _pause = false;
                _pauseTime = 0.0;
            }

            /**
             * カウントアップを開始します
             */
            void set() {
                _setTime = now();
            }

            /**
             * 経過時間をミリ秒で返します
             * @return 経過時間
             */
            double elapsed() const {
                if(_pause) {
                    return _pauseTime - _setTime;
                } else {
                    return now() - _setTime;
                }
            }

            /**
             * カウントアップを一時停止します or 再開します
             * @return Pauseしていた時間間隔を返します
             */
            double pause() {
                double elapseTime = 0.0;
                if(_pause) {
                    elapseTime = (now() - _pauseTime);
                    _setTime += elapseTime;
                    return elapseTime;
                } else {
                    _pauseTime = now();
                }
                return elapseTime;
            }

            /**
             * Pause中かどうかを返します
             * @return true 停止状態 / false 動作状態
             */
            bool isPause() const {
                return _pause;
            }

        protected:
            // 設定時刻
            double _setTime;
            // 一時停止指定時間
            bool   _pause;
            double _pauseTime;
        };

    }
}

#endif
