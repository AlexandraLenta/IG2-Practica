#pragma once
#include "IG2Object.h"
#include <OgreTimer.h>

class AnimatedSinbad : public IG2Object
{
public:
    static constexpr std::string_view MESH = "Sinbad.mesh";
    const std::string SWORD_MESH = "Sword.mesh";
    const double DURATION = 21;
    const int TIME_INSTANTS = 14;

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    AnimatedSinbad(Vector3 initPos, Real moveLength, SceneNode* node, SceneManager* sceneMng);
    ~AnimatedSinbad();

    void update(double dt);

private:
    Animation* _animation;
    AnimationState* _genAnimState;
    AnimationState* _danceAnimState;
    std::vector<AnimationState*> _walkAnimStates;
    NodeAnimationTrack* _track;

    Entity* _swordEntL;
    Entity* _swordEntR;

    float _danceStartInstant = 14;
    float _walkStartInstant = 2; 
    float _swordAppearInstant = 5;
    Ogre::Timer* _timer;

    Real _movLength;

    float _durStep = DURATION / TIME_INSTANTS;

    void addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, float turnAngle, Vector3 move, float step);
    void createAnimation();
};
