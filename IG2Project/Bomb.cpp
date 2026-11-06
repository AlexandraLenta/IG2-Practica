#include "Bomb.h"
#include "OgreKeyFrame.h"

Bomb::Bomb(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {
    // Creates a new entity with the mesh and attach the entity
    entity = sceneMng->createEntity(BOMB_MESH);
    mNode->attachObject(entity);
    mNode->setScale(ORIGINAL_SCALE);
    mNode->setInitialState();

    _timer = new Ogre::Timer();

    Animation* anim = mSM->createAnimation("bomb_scale", SCALE_TIME * 2.f);

    NodeAnimationTrack* track = anim->createNodeTrack(0);

    track->setAssociatedNode(mNode);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale(), 0);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale() * MAX_SCALE, 0.5);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale() * MIN_SCALE, 1.5);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale(), 2);

    _scaleAnimation = mSM->createAnimationState("bomb_scale");

    _scaleAnimation->setLoop(true);
    _scaleAnimation->setEnabled(true);
}

Bomb::~Bomb() {
    delete _timer;
    _timer = nullptr;

    mSM->destroyAnimation("bomb_scale");
    mSM->destroyAnimationState("bomb_scale");
}

void Bomb::update(double dt) {
    _scaleAnimation->addTime(dt);
    if (_timer->getMilliseconds() >= SCALE_TIME * 1000) {

    }
}

void Bomb::addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, float turnAngle, Vector3 move, Vector3 scale, float step) {
    TransformKeyFrame* kf = nodeAnimationTrack->createNodeKeyFrame(_stepDuration * step);

    kf->setTranslate(move);
    kf->setRotation(Quaternion(Degree(turnAngle), Vector3::UNIT_Y));
    kf->setScale(scale);
}