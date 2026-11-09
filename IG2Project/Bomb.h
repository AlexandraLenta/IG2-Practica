#pragma once
#include "IG2Object.h"
#include "OgreTimer.h"
#include <functional>

class Bomb : public IG2Object
{
public:
	const std::string BOMB_MESH = "sphere.mesh";
	const std::string FUSE_MESH = "cube.mesh";
	const float SCALE_TIME = 0.7; // time between max scale and min scale
	const int FUSE_STEPS = 1;
	
	const Vector3 ORIGINAL_SCALE = Vector3{ 0.21, 0.21, 0.21 };
	const Vector3 FUSE_SCALE = Vector3{ 0.02, 0.1, 0.02 };

	Bomb(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int index, float explodeTime = 5, float maxScale = 1.1, float minScale = 0.9);

	~Bomb();

	void initExplosion();

	void setExplodeCallback(std::function<void()> func);

	void update(double dt);
private:
	int _idx;
	Ogre::Timer* _timer = nullptr;
	float _scaleStepDuration = SCALE_TIME;
	float _fuseStepDuration = _explodeTime / FUSE_STEPS;
	
	float _explodeTime;
	float _minScale, _maxScale;

	AnimationState* _scaleAnimation = nullptr;
	AnimationState* _fuseAnimation = nullptr;

	Ogre::Entity* _fuseEntity = nullptr;
	Ogre::SceneNode* _fuseNode = nullptr;
	
	Ogre::ParticleSystem* _fuseParticleSys = nullptr;
	Ogre::SceneNode* _fuseParticleNode = nullptr;

	bool _hasExploded = false;

	std::function<void()> _callback;

	void createBomb();
	void createScaleAnimation();
	void createParticleSys();
	void createFuseAnimation();

	void endExplosion();

	void addKeyFrame(NodeAnimationTrack* nodeAnimationTrack, float turnAngle, Vector3 move, Vector3 scale, float step, float stepDuration);
};