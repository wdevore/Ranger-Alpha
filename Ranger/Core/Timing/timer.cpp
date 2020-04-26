//
// Created by William DeVore on 10/22/15.
//

#include <ostream>
#include <iostream>
#include <iomanip>
#include "timer.h"
#include "scheduler.h"
#include "../../Extensions/math.h"

namespace Ranger {
    const int Timer::REPEAT_FOREVER = -1;

    Timer::Timer()
//    : _target(nullptr)
    {

    }

    Timer::Timer(UpdateTargetWPtr target, bool paused)
            : _target(target),
              _paused(paused)
    {
        if (target.expired()) {
            throw std::invalid_argument("A valid UpdateTarget is required.");
        }

        UpdateTargetSPtr spTarget(_target);
        _id = spTarget->getId();

        _runForever = true;
        _repeatCount = 0;
        _targetGone = false;
    }

    Timer::Timer(UpdateTargetWPtr target, double interval, int repeat, bool paused)
    : _target(target),
      _interval(interval),
      _repeatCount(repeat),
      _paused(paused)
    {
        if (target.expired()) {
            throw std::invalid_argument("A valid UpdateTarget is required.");
        }

        UpdateTargetSPtr spTarget(_target);
        _id = spTarget->getId();

        _runForever = repeat == Timer::REPEAT_FOREVER;
        _targetGone = false;
    }

    Timer::~Timer() {
        std::cout << "Timer::~Timer: " << _id << std::endl;
    }

    void Timer::setTarget(UpdateTargetWPtr target, bool paused) {

        if (target.expired()) {
            throw std::invalid_argument("A valid UpdateTarget is required.");
        }

        _paused = paused;
        _target = target;
        UpdateTargetSPtr spTarget = _target.lock();
        _id = spTarget->getId();

        _runForever = true;
        _targetGone = false;
    }

    void Timer::arm() {
        _elapsed = 0.0;
        _expired = false;
        _intervalCount = 0;
        _paused = false;
    }

    void Timer::disarm() {
        _paused = true;
    }

    void Timer::changeInterval(double interval) {
        _interval = interval;
        arm();
    }

    void Timer::changeRepeats(int count) {
        _repeatCount = count;
        _runForever = _repeatCount == Timer::REPEAT_FOREVER;
        arm();
    }

    //! delay in milliseconds
    void Timer::armWithDelay(double delay) {
        _useDelay = true;
        _delay = delay;
        _delayComplete = false;
        arm();
    }

    void Timer::update(double dt) {
        if (_paused || _expired)
            return;

        _elapsed += dt;
        //std::cout << "Timer: elapsed " << "id: " << _id << ", " << std::showpoint << std::setprecision(16) << _elapsed << ", " << _intervalCount << std::endl;

        if (_useDelay && !_delayComplete) {
            if (_elapsed >= _delay) {
                // Delay completed change state.
                //std::cout << "Timer: delay complete" << "id: " << _id << ", " << _elapsed << ", " << _interval << std::endl;
                _delayComplete = true;
                arm();  // Now arm the timer.
            }
            return;
        }

        // ------------------------------------------------------------------
        // Update Target
        // ------------------------------------------------------------------
        if (!_target.expired()) {
            //UpdateTargetSPtr spTarget(_target);

            UpdateTargetSPtr spTarget = _target.lock();
            spTarget->update(_elapsed);
        }
        else {
            _targetGone = true;
            return;
        }

        if (_runForever) {
            //standard timer usage
            if (_elapsed >= _interval) {
                //std::cout << "Timer: runforever, elapsed " << "id: " << _id << ", " << _elapsed << std::endl;
                _elapsed = 0.0;
            }

            return;
        }

        if ((_interval - _elapsed) < Math::Epsilon) {
        //if (_elapsed >= _interval) {
            //std::cout << "Timer: _intervalCount " << "id: " << _id << ", " << _elapsed << ", " << _intervalCount << std::endl;
            //std::cout << "Timer: _interval " << "id: " << _id << ", " << _interval << std::endl;
            //std::cout << "Timer: " << "callback count: " << _callbackCount << std::endl;
            //std::cout << "Timer: " << "_repeatCount count: " << _repeatCount << std::endl;
            _elapsed = 0.0;
            _intervalCount++;
        }

        if (_intervalCount > _repeatCount) {
            _expired = true;
            //std::cout << "Timer: " << "timer expired: " << _id << std::endl;
            //std::cout << "Timer: " << "callback count: " << _callbackCount << std::endl;
            return;
        }
        _callbackCount++;

    }

    //! toString()
    std::ostream& operator<<(std::ostream &os, const Timer &t) {
        return os << "Timer: " <<
                "Id= " << t._id <<
                ", interval= " << t._interval <<
                ", delay= " << t._delay <<
                ", paused= " << t._paused <<
                ", expired= " << t._expired <<
                ", runforever= " << t._runForever <<
                ", repeat= " << t._repeatCount;
    }

}
