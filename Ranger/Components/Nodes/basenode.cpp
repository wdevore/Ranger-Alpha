//
// Created by William DeVore on 3/24/16.
//

#include "basenode.h"

namespace Ranger {
    int BaseNode::_tagGen{INITIAL_START_TAG};

    int BaseNode::genTag() {
        return _tagGen++;
    }

    BaseNode::BaseNode() {
        initialize();
    }

    BaseNode::~BaseNode() {
        std::cout << "BaseNode::~BaseNode " << std::endl;
    }

    bool BaseNode::initialize() {
        _parent = nullptr;
        _running = false;
        //! By default all new nodes are dirty.
        _transformDirty = _inverseDirty = true;
        _tag = -1;
        _exited = false;
        return true;
    }

    //---------------------------------------------------------------------
    // Properties
    //---------------------------------------------------------------------
    void BaseNode::bbox(const Rectangle<float>& bbox) {
        _bbox.set(bbox);
    }

    void BaseNode::aabbox(const Rectangle<float>& bbox) {

    }

    bool BaseNode::intersects(const Rectangle<float> &aabbox) {
        return _aabbox.contains(aabbox);
    }

    void BaseNode::markDirty() {
        // Only mark Nodes that DON'T manage their own transforms.
        if (_managedTransform)
            return;
        _transformDirty = _inverseDirty = true;
    }

    //---------------------------------------------------------------------
    // Rotation
    //---------------------------------------------------------------------
    void BaseNode::rotate(float radians) {
        _rotation = radians;
        _transformDirty = true;
    }

    void BaseNode::rotateAsDegrees(float degrees) {
        _rotation = Math::toRadians(degrees);
        _transformDirty = true;
    }

    void BaseNode::rotateBy(float radians) {
        _rotation += radians;
        _transformDirty = true;
    }

    //---------------------------------------------------------------------
    // Position
    //---------------------------------------------------------------------
    void BaseNode::position(const Vector3<float>& v) {
        _position.set(v);
        _transformDirty = true;
    }

    void BaseNode::position(float x, float y, float z) {
        _position.set(x, y, z);
        _transformDirty = true;
    }

    void BaseNode::px(float x) {
        _position.x = x;
        _transformDirty = true;
    }

    void BaseNode::py(float y) {
        _position.y = y;
        _transformDirty = true;
    }

    void BaseNode::moveBy(const Vector3<float> &delta) {
        _position.add(delta);
        _transformDirty = true;
    }

    void BaseNode::moveBy(float dx, float dy) {
        _position.add(dx, dy, 0.0f);
        _transformDirty = true;
    }

    //---------------------------------------------------------------------
    // Scale
    //---------------------------------------------------------------------
    void BaseNode::scale(const Vector3<float> &v) {
        _scale.scale(v);
        _transformDirty = true;
    }

    void BaseNode::scale(float s) {
        _scale.scale(s);
        _transformDirty = true;
    }

    void BaseNode::scale(float sx, float sy) {
        _scale.scale(sx, sy, 1.0f);
        _transformDirty = true;
    }

    void BaseNode::scaleTo(float s) {
        _scale.set(s, s, 1.0f);
        _transformDirty = true;
    }

    void BaseNode::scaleTo(float sx, float sy) {
        _scale.set(sx, sy, 1.0f);
        _transformDirty = true;
    }

    void BaseNode::scaleBy(float dx, float dy) {
        _scale.scale(_scale.x * dx, _scale.y * dy, 1.0f);
        _transformDirty = true;
    }


}