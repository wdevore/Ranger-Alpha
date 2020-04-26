//
// Created by William DeVore on 10/21/15.
//

#ifndef RANGERALPHA_TIMINGTARGET_H
#define RANGERALPHA_TIMINGTARGET_H

#include "update_target.h"
#include "../../ranger.h"

namespace Ranger {
    //! Interface for timing targets.
    class TimingTarget : public UpdateTarget {
    public:
        bool isPaused() const {
            return _paused;
        }

        void pause() {
            _paused = true;
        }

        void resume() {
            _paused = false;
        }

        int getPriority() const {
            return _priority;
        }

        void setPriority(int priority) {
            _priority = priority;
        }

        void setToNormalPriority() {
            _priority = SchedulePriority::NORMAL_PRIORITY;
        }

        //~TimingTarget() { std::cout << "~TimingTarget" << std::endl;}

    protected:
        //! The smaller the value the "higher" the priority.
        /*!
         * This means your target will be updated before more positive values.
         */
        int _priority = SchedulePriority::NORMAL_PRIORITY;

        //! Is this TimingTarget paused.
        bool _paused = false;
    };

}


#endif //RANGERALPHA_TIMINGTARGET_H
