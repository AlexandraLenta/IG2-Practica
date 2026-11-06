#include "AnimatedSinbad.h"
#include "OgreKeyFrame.h"

AnimatedSinbad::AnimatedSinbad(Vector3 initPos, Real moveLength, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng), _movLength(moveLength) {
    entity = sceneMng->createEntity(MESH.data());
    mNode->attachObject(entity);
    this->setPosition(initialPosition + Vector3{0, calculateBoxSize().y / 2.f, 0});
    mNode->setInitialState();

    _swordEntL = sceneMng->createEntity(SWORD_MESH);
    _swordEntR = sceneMng->createEntity(SWORD_MESH);

    entity->attachObjectToBone("Handle.R", _swordEntR);
    entity->attachObjectToBone("Handle.L", _swordEntL);
    _swordEntL->setVisible(false);
    _swordEntR->setVisible(false);

    createAnimation();

    _genAnimState = mSM->createAnimationState("sinbad_intro");
    _genAnimState->setLoop(true);
    _genAnimState->setEnabled(true);

    _danceAnimState = entity->getAnimationState("Dance");
    _danceAnimState->setLoop(true);
    _danceAnimState->setEnabled(true);

    _walkAnimStates.push_back(entity->getAnimationState("RunBase"));
    _walkAnimStates.push_back(entity->getAnimationState("RunTop"));

    for (auto* s : _walkAnimStates) {
        s->setEnabled(false);
        s->setLoop(true);
    }
}

AnimatedSinbad::~AnimatedSinbad() {
    if (_genAnimState)
        _genAnimState->setEnabled(false);

    mSM->destroyAnimationState("sinbad_intro");
    mSM->destroyAnimation("sinbad_intro");

    if (_swordEntL) mSM->destroyEntity(_swordEntL);
    if (_swordEntR) mSM->destroyEntity(_swordEntR);
}

void AnimatedSinbad::update(double dt) {
    _genAnimState->addTime(dt);

    // current step
    float step = _genAnimState->getTimePosition() / _durStep;
    
    bool walking = step >= _walkStartInstant && step < _danceStartInstant;
    bool swords = walking && step >= _swordAppearInstant;

    for (auto* s : _walkAnimStates) {
        s->setEnabled(walking);
        if (walking) s->addTime(dt);
    }

    _danceAnimState->setEnabled(!walking);
    if (!walking) _danceAnimState->addTime(dt);

    _swordEntL->setVisible(swords);
    _swordEntR->setVisible(swords);
}

void AnimatedSinbad::createAnimation() {
    _animation = mSM->createAnimation("sinbad_intro", DURATION);

    _animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
    
    _track = _animation->createNodeTrack(0);
    
    _track->setAssociatedNode(mNode);
    
    // center + start dancing
    addKeyFrame(_track, 0, Vector3::ZERO, 0);

    // stop dance
    addKeyFrame(_track, 0, Vector3::ZERO, 2);

    // turn
    addKeyFrame(_track, 90, Vector3::ZERO, 2.25);

    // move far right & grab swords
    addKeyFrame(_track, 90, Vector3::UNIT_X * _movLength, 3.75);
    
    // turn 180
    addKeyFrame(_track, 270, Vector3::UNIT_X * _movLength, 4.25);

    // move far left
    addKeyFrame(_track, 270, Vector3::NEGATIVE_UNIT_X * _movLength, 7.25);

    // turn 180
    addKeyFrame(_track, 450, Vector3::NEGATIVE_UNIT_X * _movLength, 7.75);

    // move to center
    addKeyFrame(_track, 450, Vector3::ZERO, 9.25);

    // turn
    addKeyFrame(_track, 360, Vector3::ZERO, 9.5);
}

void AnimatedSinbad::addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, float turnAngle, Vector3 move, float step) {
    TransformKeyFrame* kf = nodeAnimationTrack->createNodeKeyFrame(_durStep * step);

    kf->setTranslate(move);
    kf->setRotation(Quaternion(Degree(turnAngle), Vector3::UNIT_Y));
}