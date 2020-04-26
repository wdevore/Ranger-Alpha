//
// Created by William DeVore on 3/24/16.
//

#ifndef RANGERBETA_BASENODE_H
#define RANGERBETA_BASENODE_H


#include "../../Extensions/rectangle.h"
#include "../../Core/Timing/timing_target.h"
#include "../../Extensions/matrix4.h"

namespace Ranger {
    class BaseNode : public TimingTarget {

    public:
        BaseNode();

        virtual ~BaseNode();

        virtual bool initialize();

        static int genTag();

        // ====================================================================
        // Properties
        // ====================================================================
        bool running() { return _running; }

        virtual const Rectangle<float> &bbox() const {
            return _bbox;
        }

        virtual void bbox(const Rectangle<float> &bbox);

        virtual const Rectangle<float> &aabbox() const {
            return _aabbox;
        }

        virtual void aabbox(const Rectangle<float> &aabbox);

        const std::string &name() const {
            return _name;
        }

        void name(const std::string &_name) {
            BaseNode::_name = _name;
        }

        int tag() const {
            return _tag;
        }

        void tag(int _tag) {
            BaseNode::_tag = _tag;
        }

        //! Default to whatever the current visibility is.
        /*!
         * BaseNode supplies a default behavior of reflecting
         * the current state which means you don't need an actual Rectangle
         * to calculate that.
         */
        virtual bool isVisible() { return visible(); }

        bool visible() const {
            return _visible;
        }

        void visible(bool _visible) {
            BaseNode::_visible = _visible;
        }

        bool exited() const {
            return _exited;
        }

        virtual void markDirty();

        bool cleanUp() const {
            return _cleanup;
        }

        bool intersects(const Rectangle<float> &aabbox);

        /*!
         * Override this method to provide collision checks against other
         * [Node]s.
         * Each [Node] should supply its own check. For example, a Circle shaped
         * node may do a radius check, where as a Square shaped [Node] would
         * may perform a bounding box check.
         *
         * Default behaviour is AABBox check.
         */
        virtual bool intersects(BaseNodeSPtr node) { return intersects(_aabbox); }

        //---------------------------------------------------------------------
        // Rotation
        //---------------------------------------------------------------------
        void rotate(float radians);
        void rotateAsDegrees(float degrees);
        float rotate() const {
            return _rotation;
        }
        float rotateAsDegrees() const {
            return Math::toDegrees(_rotation);
        }
        void rotateBy(float radians);

        //---------------------------------------------------------------------
        // Position
        //---------------------------------------------------------------------
        void position(const Vector3<float>& v);
        void position(float x, float y, float z = 0.0f);
        const Vector3<float>& position() const {
            return _position;
        }
        void px(float x);
        void py(float y);
        float px() const {
            return _position.x;
        }
        float py() const {
            return _position.y;
        }
        void moveBy(const Vector3<float>& delta);
        void moveBy(float dx, float dy);

        //---------------------------------------------------------------------
        // Scale
        //---------------------------------------------------------------------
        void scale(const Vector3<float>& v);
        void scale(float s);
        void scale(float sx, float sy);
        void scaleTo(float s);
        void scaleTo(float sx, float sy);
        const Vector3<float>& scale() const {
            return _scale;
        }
        float sx() const {
            return _scale.x;
        }
        float sy() const {
            return _scale.y;
        }
        void scaleBy(float dx, float dy);

        //---------------------------------------------------------------------
        // Events
        //---------------------------------------------------------------------
        //! The prior to a Node entering onto the stage. The Node should
        // prepare itself for entering the stage.
        void onBegin() {
//            _isTransitionFinished = false;
            _running = true; // mark running before resumeTiming
        }

        //! The Node is now entering the stage.
        void onEntering() {
//            _isTransitionFinished = true;
        }

        //! The Node has finished entering. The Node signals when it has done so.
        // The event in response to the signal. The Node should clean itself up if
        //
        void onEnterComplete() {
//            _isTransitionFinished = true;
        }

        //! The Node signals when it wants to exit the stage. This event is sent
        // in response to the signal.
        void onBeginExit() {

        }

        void onExitTransition() {

        }

        void onExit() {
            _running = false;
            _exited = true;
            //pauseTiming();
        }

        void clean() {

        }

    protected:
        /*!
         * An Axis-aligned bounding box (AABBox).
         */
        Rectangle<float> _aabbox;

        // Local bbox
        Rectangle<float> _bbox;

        std::string _name{"NoName"};

        SchedulerSPtr scheduler{nullptr};

        // TODO seperate this into a special node of type Transition.
        bool _isTransitionFinished = true;

        bool _running{false};
        //bool _paused{false};
        bool _exited = false;

        /*!
         * If this [Node] is invisible then the [draw] method is not called.
         */
        bool _visible{true};

        // The parent should have a weak_ptr to the child.
        // A parent will never disappear on a child, hence, the parent pointer will
        // always be valid as long as the child exists. You can't have a child
        // without a parent.
        BaseNodeSPtr _parent{nullptr};

        /*!
         * [tag]s are used to identify [BaseNode]s by Ids. They can both be
         * handy for developement or for finding [BaseNode]s.
         *
         * Ex:
         * static const int TAG_PLAYER = 1;
         * node1.tag = TAG_PLAYER;
         * node2.tag = TAG_MONSTER;
         * node3.tag = TAG_BOSS;
         */
        int _tag{-1};

        //! A default tag assigned if one isn't assigned explicitly.
        /*!
         * This field is auto incremented starting at
         */
        static int _tagGen;

        //---------------------------------------------------------------------
        // Transforms
        //---------------------------------------------------------------------
        //! Optimization flags to track transforms
        bool _transformDirty{true};
        bool _inverseDirty{true};

        // Does this [Node] manage its own transform matrix.
        // Zoom nodes are a good example.
        bool _managedTransform{false};

        Matrix4<float> _transform;
        Matrix4<float> _invTransform;

        // Discrete transform properties
        Vector3<float> _position;
        float _rotation{0};
        Vector3<float> _scale;

        bool _cleanup{true};
    };
}

#endif //RANGERBETA_BASENODE_H
