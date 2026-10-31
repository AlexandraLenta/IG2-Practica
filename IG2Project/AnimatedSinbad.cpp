#include "AnimatedSinbad.h"
#include "OgreKeyFrame.h"

AnimatedSinbad::AnimatedSinbad(Vector3 initPos, Real moveLength, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng, MESH.data()), _movLength(moveLength) {
    createAnimation();

    _animState = mSM->createAnimationState("sinbad_intro");
    _animState->setLoop(true);
    _animState->setEnabled(true);
}

void AnimatedSinbad::update(double dt) {
    _animState->addTime(dt);
}

void AnimatedSinbad::createAnimation() {
    _animation = mSM->createAnimation("sinbad_intro", DURATION);

    _animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    
    _track = _animation->createNodeTrack(0);
    
    _track->setAssociatedNode(mNode);
    
    // center + start dancing
    addKeyFrame(_track, getOrientation().getRotationTo(Vector3::UNIT_Z), initialPosition, 0);

    // turn
    addKeyFrame(_track, getOrientation().getRotationTo(Vector3::UNIT_X), initialPosition, 0.25);

    // move far right & grab swords
    addKeyFrame(_track, Quaternion::IDENTITY, Vector3::UNIT_X * _movLength, 2);
    
    // turn 180
    addKeyFrame(_track, getOrientation().getRotationTo(Vector3::NEGATIVE_UNIT_X), Vector3::ZERO, 2.25);

    // move far left
    addKeyFrame(_track, Quaternion::IDENTITY, Vector3::NEGATIVE_UNIT_X * _movLength * 2, 4);

    // turn 180
    addKeyFrame(_track, getOrientation().getRotationTo(Vector3::UNIT_X), Vector3::ZERO, 4.25);

    // to center + drop swords + dance
    addKeyFrame(_track, getOrientation().getRotationTo(Vector3::UNIT_Z), Vector3::UNIT_X * _movLength, 7);
}

void AnimatedSinbad::addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, Quaternion turnAngle, Vector3 move, float stepNr) {
    TransformKeyFrame* kf = nodeAnimationTrack->createNodeKeyFrame(_durStep * stepNr);

    Vector3 finPos = getPosition() + move;

    kf->setTranslate(finPos);

    kf->setRotation(turnAngle);
}