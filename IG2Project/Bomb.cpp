#include "Bomb.h"
#include "OgreKeyFrame.h"
#include "OgreMaterialManager.h"
#include "OgreParticleSystem.h"

Bomb::Bomb(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int index, float explodeTime, float maxScale, float minScale)
    : IG2Object(initPos, node, sceneMng), _explodeTime(explodeTime), _minScale(minScale), _maxScale(maxScale), _idx(index) {
    createBomb();

    mNode->setInitialState();

    _timer = new Ogre::Timer();

    createScaleAnimation();

    createParticleSys();

    createFuseAnimation();

    setVisible(false);
}

void Bomb::createBomb() {
    // Creates a new entity with the mesh and attach the entity
    entity = mSM->createEntity(BOMB_MESH);
    entity->setMaterialName("game/bombBody");

    mNode->attachObject(entity);
    mNode->setScale(ORIGINAL_SCALE);

    _fuseEntity = mSM->createEntity(FUSE_MESH);
    _fuseEntity->setMaterialName("game/bombFuse");

    _fuseNode = mNode->createChildSceneNode(Vector3{ 0, 120, 0 });
    _fuseNode->attachObject(_fuseEntity);
    _fuseNode->setInheritScale(false);
    _fuseNode->setScale(FUSE_SCALE * ORIGINAL_SCALE);

}

void Bomb::createScaleAnimation() {
    Animation* anim = mSM->createAnimation(Ogre::String("bomb_scale" + _idx), SCALE_TIME * 2.f);

    NodeAnimationTrack* track = anim->createNodeTrack(0);

    track->setAssociatedNode(mNode);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale(), 0, _scaleStepDuration);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale() * _maxScale, 0.5, _scaleStepDuration);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale() * _minScale, 1.5, _scaleStepDuration);

    addKeyFrame(track, 0, Vector3::ZERO, mNode->getInitialScale(), 2, _scaleStepDuration);

    _scaleAnimation = mSM->createAnimationState(Ogre::String("bomb_scale" + _idx));

    _scaleAnimation->setLoop(true);
    _scaleAnimation->setEnabled(false);
}

void Bomb::createParticleSys() {
    _fuseParticleSys = mSM->createParticleSystem(Ogre::String("fuse" + _idx), "game/fuseParticle");

    _fuseParticleNode = _fuseNode->createChildSceneNode(Vector3{ 0, 90, 0 });
    _fuseParticleNode->setInheritScale(false);
    _fuseParticleNode->attachObject(_fuseParticleSys);
    _fuseParticleNode->setInitialState();
    _fuseParticleSys->setEmitting(true);
}

void Bomb::createFuseAnimation() {
    Animation* anim = mSM->createAnimation(Ogre::String("fuse_descend" + _idx), _explodeTime);

    NodeAnimationTrack* track = anim->createNodeTrack(0);

    track->setAssociatedNode(_fuseParticleNode);

    addKeyFrame(track, 0, Vector3::ZERO, _fuseParticleNode->getInitialScale(), 0, _fuseStepDuration);

    addKeyFrame(track, 0, Vector3{0, -200, 0}, _fuseParticleNode->getInitialScale(), 1, _explodeTime);

    _fuseAnimation = mSM->createAnimationState(Ogre::String("fuse_descend" + _idx));

    _fuseAnimation->setLoop(false);
    _fuseAnimation->setEnabled(false);
}

Bomb::~Bomb() {
    delete _timer;
    _timer = nullptr;

    mSM->destroyAnimation(Ogre::String("bomb_scale" + _idx));
    mSM->destroyAnimationState(Ogre::String("bomb_scale" + _idx));

    mSM->destroyAnimation(Ogre::String("fuse_descend" + _idx));
    mSM->destroyAnimationState(Ogre::String("fuse_descend" + _idx));

    _scaleAnimation = nullptr;
    _fuseAnimation = nullptr;

    mSM->destroyParticleSystem(Ogre::String("fuse" + _idx));

    _fuseParticleSys = nullptr;
}

void Bomb::update(double dt) {
    _scaleAnimation->addTime(dt);
    _fuseAnimation->addTime(dt);

    if (_fuseAnimation->getTimePosition() >= _explodeTime) {
        endExplosion();
    }
}

void Bomb::addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, float turnAngle, Vector3 move, Vector3 scale, float step, float stepDuration) {
    TransformKeyFrame* kf = nodeAnimationTrack->createNodeKeyFrame(stepDuration * step);

    kf->setTranslate(move);
    kf->setRotation(Quaternion(Degree(turnAngle), Vector3::UNIT_Y));
    kf->setScale(scale);
}

void Bomb::initExplosion() {
    setVisible(true);
    mNode->setInitialState();
    _fuseParticleSys->setEmitting(true);

    //std::cout << getPosition() << '\n';

    _scaleAnimation->setEnabled(true);
    _fuseAnimation->setEnabled(true);
    _fuseAnimation->setTimePosition(0);
}

void Bomb::endExplosion() {
    setVisible(false);

    _fuseParticleSys->setEmitting(false);

    _scaleAnimation->setEnabled(false);
    _fuseAnimation->setEnabled(false);

    _callback();
}

void Bomb::setExplodeCallback(std::function<void()> func) {
    _callback = func;
}