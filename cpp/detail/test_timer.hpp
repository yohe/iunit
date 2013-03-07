#ifndef IUNIT_CPP_DETAIL_TEST_TIMER_HPP
#define IUNIT_CPP_DETAIL_TEST_TIMER_HPP

#include <sys/time.h>

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

        private:

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
                return now() - _setTime;
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
