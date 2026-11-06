#pragma once
#include "IG2Object.h"
#include "OgreTimer.h"

class Bomb : public IG2Object
{
public:
	const std::string BOMB_MESH = "sphere.mesh";
	const float MAX_SCALE = 1.1;
	const float MIN_SCALE = 0.9;
	const float SCALE_TIME = 0.7; // time between max scale and min scale
	const Vector3 ORIGINAL_SCALE = Vector3{ 0.21, 0.21, 0.21 };

	Bomb(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	~Bomb();

	void update(double dt);
private:
	Ogre::Timer* _timer = nullptr;
	float _stepDuration = SCALE_TIME;

	AnimationState* _scaleAnimation = nullptr;

	void addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, float turnAngle, Vector3 move, Vector3 scale, float step);
};