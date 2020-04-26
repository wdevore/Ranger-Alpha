//
// Created by William DeVore on 10/21/15.
//

#ifndef RANGERALPHA_SCHEDULER_H
#define RANGERALPHA_SCHEDULER_H

#include <list>
#include <set>
#include "../../ranger.h"
#include "update_target.h"
#include "timer.h"

//#include "../Pooling/SmartObjectPool.h"

namespace Ranger {
    /*! \class Scheduler Scheduler.h "Ranger/Timing/Scheduler.h"
     *  \brief Scheduler responsible of updating the scheduled callbacks.
     *
     * There are 2 different types of callbacks:
     * - @see TimingTarget the callback will be called every frame. You can customize the priority.
     * - @see UpdateTarget A custom target that will be called every frame, or with a custom interval of time.
     *   UpdateTargets are driven by an internal Timer object.
     */
    class Scheduler final {

    public:

        const int TIMER_POOL_SIZE = 32;

        // Our Constructor/Destructor CAN NOT be defined inline because of a unique_ptr being used.
        // The link below talks about the term call-sites.
        // @see http://binglongx.com/2012/07/27/implementation-hiding-with-c11-unique_ptr-and-shared_ptr/
        // for the reason.
        // Also, see Meyer's Effective modern C++ Item 22 which also explains why. Which includes
        // a simple solution for the cpp file using "Widget::~Widget() = default;"
        /*
         * We need to make sure that when std::unique_ptr destructs, it would be able to see the complete TimingTarget.
         * When does, for example _highPriorityTargets, destruct? It is at the time when Scheduler destructs.
         * Because we do not want Scheduler.h see the complete TimingTarget type, we have to put the destructor of
         * Scheduler in Scheduler.cpp. For our implementation hiding endeavor, the only place that has access to
         * TimingTarget destructor is anyway in Scheduler.cpp
         */
//        Scheduler();
//        ~Scheduler();
        //Scheduler(Scheduler const &aRef) = delete ;

        //Scheduler(Scheduler&& other) = delete;
        //Scheduler& operator=(Scheduler&& other) = delete;

        void initialize();

        // ##########################################################################
        // TimingTargets
        // ##########################################################################
        //! Un-schedule all targets
        /*!
         *  More detail here.
         */
        void unScheduleAll();

        void scheduleTimingTarget(SharedTimingTarget target);
        void unScheduleTimingTarget(SharedTimingTarget target);

        void pauseTimingTargetsByPriority(int priority);
        void resumeTimingTargetsByPriority(int priority);

        // ##########################################################################
        // UpdateTargets
        // ##########################################################################
        void scheduleUpdateTarget(UpdateTargetSPtr target, bool autoArm = true);
        void scheduleUpdateTarget(UpdateTargetSPtr target, double interval, int repeatCount, bool autoArm = true);

        void armUpdateTarget(UpdateTargetSPtr target);
        void disarmUpdateTarget(UpdateTargetSPtr target);
        void changeUpdateTargetInterval(UpdateTargetSPtr target, double interval);
        void changeUpdateTargetRepeat(UpdateTargetSPtr target, int count);
        void unscheduleUpdateTarget(UpdateTargetSPtr target);
        Timer const* getUpdateTargetTimer(UpdateTargetSPtr target);
        std::string toString(UpdateTargetSPtr target);

        // ##########################################################################
        // Core update
        // ##########################################################################
        //! Update all targets
        /*!
         *  \param dt time per frame in milliseconds
         */
        void update(double dt);

    private:
        //! Slow/Hyper motion control
        /*!
         * For slow motion set the value to < 1.0
         * For hyper motion set the value to > 1.0
         */
        double _timeScale = 1.0;

        // #############################################################################
        // TimingTarget types
        // #############################################################################
        // I could have used a lambda for sorting but class types are generally optimized better by the compiler.
        struct PrioritySortCriterion {
            // Again, because of the use of smart pointers the implementation must be in the
            // location where the full type specification occurs which is in the implementation file.
            // Hence, I can't have the operator defined as inline here.
            bool operator() (SharedTimingTarget p1, SharedTimingTarget p2) const;
        };

        // We don't want the Scheduler to be the owner of TimingTargets so we use
        // shared_ptr(s).
        // I chose an std::set because:
        // 1) To maintain priority ordering.
        // 2) Disallow a TimingTarget to be scheduled more than once.
        std::set<SharedTimingTarget, PrioritySortCriterion> _highPriorityTargets; // (-∞ to 0)
        std::set<SharedTimingTarget, PrioritySortCriterion> _normalPriorityTargets; // [0 to ∞)

        // #############################################################################
        // UpdateTarget types
        // #############################################################################
        // Defining a class predicate allows for reuse.
        struct TimerUnaryPredicate {
            TimerUnaryPredicate(UpdateTargetSPtr t) : uta(t) {};
            // Again Timer is only forward declared in this .h file.
            bool operator() (const std::unique_ptr<Timer>& t);

        private:
            UpdateTargetSPtr uta;
        };

        //! A pool of Timers associated with UpdateTargets
        //SmartObjectPool<Timer> _timerPool;

        std::list<std::unique_ptr<Timer>> _updateTargets;
        //std::list<SmartObjectPool<Timer>::ptr_type> _updateTargets;

        //! toString
        friend std::ostream& operator<<(std::ostream&, const Scheduler&);

    };
}


#endif //RANGERALPHA_SCHEDULER_H
