//
// Created by William DeVore on 10/23/15.
//

#ifndef RANGERALPHA_UPDATETARGET_H
#define RANGERALPHA_UPDATETARGET_H

namespace Ranger {
    //! Interface for update targets.
    /*!
     * UpdateTargets are driven by Timers.
     */
    class UpdateTarget {
    public:

        UpdateTarget() { _id = GenerateTargetId(); }
        // copy constructor
        //UpdateTarget (const UpdateTarget& t) = delete;

        //! \param dt delta time in milliseconds
        virtual void update(double dt) {};

        //! Not thread safe...yet.
        static int GenerateTargetId() { return _targetGenId++; }

        int getId() const {
            return _id;
        }

    protected:
        static int _targetGenId;  // unique id.

        int _id{-1};
    };

}

#endif //RANGERALPHA_UPDATETARGET_H
