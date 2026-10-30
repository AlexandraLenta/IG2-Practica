#pragma once
#include "IG2Object.h"

class AnimatedSinbad : IG2Object
{
public:
    const std::string MESH = "Sinbad.mesh";
    const std::string SWORD_MESH = "sword.mesh";
    const float DURATION = 21;

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    AnimatedSinbad(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    void update(double dt);

private:
    Animation* _animation;
    NodeAnimationTrack* _track;

    void addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, double turnAngle, double newPos);
    void createAnimation();
};

