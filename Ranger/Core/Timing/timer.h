//
// Created by William DeVore on 10/22/15.
//

#ifndef RANGERALPHA_TIMER_H
#define RANGERALPHA_TIMER_H

#include "../../ranger.h"
#include "timing_target.h"

namespace Ranger {
    class Timer final {

    public:
        static const int REPEAT_FOREVER;

        Timer();
        Timer(UpdateTargetWPtr target, bool paused = false);
        Timer(UpdateTargetWPtr target, double interval, int repeat = Timer::REPEAT_FOREVER, bool paused = false);

        ~Timer();   // suppresses move constructor.

        //Timer(Timer& other) = delete;
        //Timer& operator=(Timer& other) = delete;

        // copy constructor
//        Timer (const Timer& t) = delete;
        // assignment operator
//        const Timer& operator= (const Timer& t)
//        { _target = t._target;
//            return *this;
//        }
//
//        Timer(Timer&& other) = default;
//        Timer& operator=(Timer&& other) = delete;

        void setTarget(UpdateTargetWPtr target, bool paused = false);

        void arm();
        void armWithDelay(double delay);
        void disarm();
        //! Changes interval and re-arms without delay.
        void changeInterval(double interval);
        //! Changes how many times the interval is repeated and re-arms without delay.
        void changeRepeats(int count);

        void update(double dt);

        bool isPaused() const {
            return _paused;
        }

        bool isTargetGone() const {
            return _targetGone;
        }

        int getId() const {
            return _id;
        }

    private:
        //! Timer identification
        int _id{0};

        //! In Frames.
        /*!
         * 1 second = 1000 milliseconds. At 60 FPS then a frame equals 1000/60 ~=16.667ms
         */
        double _interval{0.0};

        double _elapsed{0.0};

        bool _runForever{false};

        bool _useDelay{false};

        bool _paused{false};

        int _intervalCount{0};

        bool _expired{false};

        bool _targetGone{false};

        /// 0 = once, 1 = (2 x executed)
        int _repeatCount{0};

        double _delay{0.0};

        UpdateTargetWPtr _target;

        bool _delayComplete{false};

        int64_t _callbackCount{0};

        //! toString
        friend std::ostream& operator<<(std::ostream&, const Timer&);
    };

}


#endif //RANGERALPHA_TIMER_H
