//
// Created by William DeVore on 10/21/15.
//

#include <iostream>
#include <sstream>
#include <algorithm>

#include "scheduler.h"

namespace Ranger {
    //Scheduler::Scheduler(Scheduler const &aRef) = delete ;

//    Scheduler::Scheduler() {
////        // Note: call-site for constructors of unique_ptr(s).
////        //_testTimer = std::unique_ptr<Timer>(std::make_shared<Timer>(nullptr, 5000, false, 3)));
////        //_testTimer->arm();
//    }

//    Scheduler::~Scheduler() {
//        // Note: call-site for destructors of unique_ptr(s).
//    }

    void Scheduler::initialize() {
//        for (int i = 0; i < TIMER_POOL_SIZE; i++) {
//            std::unique_ptr<Timer> t = make_unique<Timer>();
//            _timerPool.add(std::move(t));
//        }
    }

    void Scheduler::unScheduleAll() {
        std::cout << "Scheduler: " << "unscheduling all targets." << std::endl;
        _highPriorityTargets.clear();
        _normalPriorityTargets.clear();
        _updateTargets.clear();
    }

    /**
     * @param dt delta in milliseconds.
     */
    void Scheduler::update(double dt) {
        if (_timeScale != 1.0) {
            dt *= _timeScale;
        }

        // Update targets from lowest to highest priority.
        for(const auto& target : _highPriorityTargets) {
            if (!target->isPaused())
                target->update(dt);
        }

        for(const auto& target : _normalPriorityTargets) {
            if (!target->isPaused())
                target->update(dt);
        }

        for(const auto& target : _updateTargets) {
            if (!target->isPaused())
                target->update(dt);
        }
    }

    /*!
     * The smaller value for [TimingTarget.priority] the higher priority,
     * meaning they will be updated first before progressing to the lower priority
     * [TimingTarget]s (aka higher priority values).
     *
     * Scheduling a @see TimingTarget here means it will be called forever which also
     * means it will never be added back to the [ObjectPool].
     */
    void Scheduler::scheduleTimingTarget(SharedTimingTarget target) {
        // Check normals first as they are the most abundant.
        auto it = std::find(_normalPriorityTargets.begin(), _normalPriorityTargets.end(), target);

        bool scheduled = false;
        if (it == _normalPriorityTargets.end()) {
            // The target wasn't found in the normal list, how about the highs.
            it = std::find(_highPriorityTargets.begin(), _highPriorityTargets.end(), target);
            if (it == _highPriorityTargets.end()) {
                // It wasn't found in the highs either. This means it hasn't been scheduled yet.
            }
            else
                scheduled = true;
        }

        if (scheduled) {
            std::cout << "Scheduler: " << "target with priority [" << target->getPriority() << "] already scheduled." << std::endl;
            return;
        }

        // What collection is the Target destine for.
        if (target->getPriority() < 0) {
            _highPriorityTargets.insert(target);
            // Resort
            //_highPriorityTargets.sort((TimingTarget a, TimingTarget b) => a.priority.compareTo(b.priority));
        }
        else if (target->getPriority() == SchedulePriority::NORMAL_PRIORITY) {
            _normalPriorityTargets.insert(target);
        }
    }

    void Scheduler::unScheduleTimingTarget(SharedTimingTarget target) {
        if (target->getPriority() < 0) {
            _highPriorityTargets.erase(target);
        }
        else if (target->getPriority() == SchedulePriority::NORMAL_PRIORITY) {
            if (!_normalPriorityTargets.empty()) {
                unsigned long count = _normalPriorityTargets.erase(target);
                if (count == 0) {
                    std::stringstream ss;
                    ss << __FILE__ << "::" << __FUNCTION__ << ": TimingTarget {" << target->getId() << "} " <<
                    "not found." << std::endl;
                    std::cout << ss.str();
                }
            }
        }
    }

    void Scheduler::pauseTimingTargetsByPriority(int priority) {
        if (priority < 0) {
            std::for_each(_highPriorityTargets.begin(), _highPriorityTargets.end(),
                          [priority](const SharedTimingTarget& tt) { if (priority == tt->getPriority()) tt->pause(); });
        }
        else if (priority == SchedulePriority::NORMAL_PRIORITY) {
            std::for_each(_normalPriorityTargets.begin(), _normalPriorityTargets.end(),
                          [priority](const SharedTimingTarget& tt) { if (priority == tt->getPriority()) tt->pause(); });
        }
    }

    void Scheduler::resumeTimingTargetsByPriority(int priority) {
        if (priority < 0) {
            std::for_each(_highPriorityTargets.begin(), _highPriorityTargets.end(),
                          [priority](const SharedTimingTarget& tt) { if (priority == tt->getPriority()) tt->resume(); });
        }
        else if (priority == SchedulePriority::NORMAL_PRIORITY) {
            std::for_each(_normalPriorityTargets.begin(), _normalPriorityTargets.end(),
                          [priority](const SharedTimingTarget& tt) { if (priority == tt->getPriority()) tt->resume(); });
        }
    }

    bool Scheduler::PrioritySortCriterion::operator()(SharedTimingTarget p1, SharedTimingTarget p2) const {
        return p1->getPriority() <= p2->getPriority();
    }

    // ##########################################################################
    // UpdateTargets
    // ##########################################################################
    void Scheduler::scheduleUpdateTarget(UpdateTargetSPtr target, bool autoArm) {
        // Lamba style
        //auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(),
        //                       [&target] (const std::unique_ptr<Timer>& t) { return t->getId() == target.getId(); });

        // Formal class style
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));

        if (it == _updateTargets.end()) {
            //std::unique_ptr<Timer> t = std::unique_ptr<Timer>(new Timer(target));
            //std::unique_ptr<Timer> t = make_unique<Timer>(std::make_shared(target));
            std::unique_ptr<Timer> timer = std::unique_ptr<Timer>(new Timer(target));
            //SmartObjectPool<Timer>::ptr_type timer = _timerPool.acquire();
            timer->setTarget(target);
            //std::unique_ptr<Timer> t = std::unique_ptr<Timer>(new Timer(target));

            if (autoArm)
                timer->arm();

            _updateTargets.push_back(std::move(timer));
            //_updateTargets.push_back(timer);
        }
        else {
            std::cout << "Scheduler: " << "UpdateTarget ["<< target->getId() << "] already scheduled." << std::endl;
        }
    }

    void Scheduler::scheduleUpdateTarget(UpdateTargetSPtr target, double interval, int repeatCount, bool autoArm) {
        // Lamba style
        //auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(),
        //                       [&target] (const std::unique_ptr<Timer>& t) { return t->getId() == target.getId(); });

        // Formal class style
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));

        if (it == _updateTargets.end()) {
            //std::unique_ptr<Timer> t = std::unique_ptr<Timer>(new Timer(target, interval));
            //std::unique_ptr<Timer> t = make_unique<Timer>(target, interval);
            std::unique_ptr<Timer> timer = std::unique_ptr<Timer>(new Timer(target));
            //SmartObjectPool<Timer>::ptr_type timer = _timerPool.acquire();

            timer->changeInterval(interval);
            timer->changeRepeats(repeatCount);

            if (autoArm)
                timer->arm();

            _updateTargets.push_back(std::move(timer));
        }
        else {
            Timer* timer = it->get();
            timer->changeInterval(interval);
            timer->changeRepeats(repeatCount);
            std::cout << "Scheduler: " << "UpdateTarget ["<< target->getId() << "] already scheduled, changing interval and count." << std::endl;
        }
    }

    bool Scheduler::TimerUnaryPredicate::operator()(const std::unique_ptr<Timer>& t) {
        return t->getId() == uta->getId();
    }

    void Scheduler::unscheduleUpdateTarget(UpdateTargetSPtr target) {
        auto it = std::remove_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));
        if (it == _updateTargets.end()) {
            std::cout << "Scheduler: " << "Couldn't find UpdateTarget ["<< target->getId() << "] to remove." << std::endl;
        }
    }

    void Scheduler::armUpdateTarget(UpdateTargetSPtr target) {
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));
        if (it != _updateTargets.end()) {
            Timer* timer = it->get();
            timer->arm();
        }
    }

    void Scheduler::changeUpdateTargetInterval(UpdateTargetSPtr target, double interval) {
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));
        if (it != _updateTargets.end()) {
            Timer* timer = it->get();
            std::cout << "Scheduler: " << "changing UpdateTarget ["<< target->getId() << "] interval." << std::endl;
            timer->changeInterval(interval);
        }
    }

    void Scheduler::changeUpdateTargetRepeat(UpdateTargetSPtr target, int count) {
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));
        if (it != _updateTargets.end()) {
            Timer* timer = it->get();
            std::cout << "Scheduler: " << "changing UpdateTarget ["<< target->getId() << "] repeat count." << std::endl;
            timer->changeRepeats(count);
        }
    }

    void Scheduler::disarmUpdateTarget(UpdateTargetSPtr target) {
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));
        if (it != _updateTargets.end()) {
            Timer* timer = it->get();
            timer->disarm();
        }
    }

    Timer const* Scheduler::getUpdateTargetTimer(UpdateTargetSPtr target) {
        auto it = std::find_if(_updateTargets.begin(), _updateTargets.end(), TimerUnaryPredicate(target));
        if (it != _updateTargets.end()) {
            Timer* timer = it->get();
            return dynamic_cast<Timer const*>(timer);
        }
        return nullptr;
    }

    std::string Scheduler::toString(UpdateTargetSPtr target) {
        Timer const* timer = getUpdateTargetTimer(target);
        std::stringstream ss;

        if (!timer) {
            ss << __FILE__ << "::" << __FUNCTION__ << ": UpdateTarget {" << target->getId() << "} doesn't have a Timer associated. Perhaps it wasn't scheduled.";
            throw std::invalid_argument(ss.str());
        }

        ss << *timer;
        return ss.str();
    }

    //! toString()
    std::ostream& operator<<(std::ostream &os, const Scheduler &t) {
        return os << "Scheduler: " <<
                "HighPriority(s)= " << t._highPriorityTargets.size() <<
                ", NormalPriority(s)= " << t._normalPriorityTargets.size() <<
                ", UpdateTarget(s)= " << t._updateTargets.size();
    }

}
