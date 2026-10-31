#pragma once
#include "IG2Object.h"

class AnimatedSinbad : public IG2Object
{
public:
    static constexpr std::string_view MESH = "Sinbad.mesh";
    const std::string SWORD_MESH = "sword.mesh";
    const Real DURATION = 21;
    const int KEYFRAMES = 8;

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    AnimatedSinbad(Vector3 initPos, Real moveLength, SceneNode* node, SceneManager* sceneMng);

    void update(double dt);

private:
    Animation* _animation;
    AnimationState* _animState;
    NodeAnimationTrack* _track;

    Real _movLength;

    float _durStep = DURATION / KEYFRAMES;

    void addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, Quaternion turnAngle, Vector3 move, float stepNr);
    void createAnimation();
};
