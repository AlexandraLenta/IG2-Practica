#include "AnimatedSinbad.h"

AnimatedSinbad::AnimatedSinbad(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {
	entity = sceneMng->createEntity(MESH);
    mNode->attachObject(entity);
    this->setPosition(initialPosition);
    mNode->setInitialState();

    createAnimation();
}

void AnimatedSinbad::createAnimation() {
    _animation = mSM->createAnimation("sinbad_intro", DURATION);

    _animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    
    _track = _animation->createNodeTrack(0);
    
    _track->setAssociatedNode(mNode);
    
    addKeyFrame();
}

void AnimatedSinbad::addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, double turnAngle, double newPos) {
 
}