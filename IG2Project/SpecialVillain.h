#pragma once
#include "Villain.h"
#include "OgreTimer.h"

class SpecialVillain :
	public Villain
{
public:
	SpecialVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);
	~SpecialVillain();

	void update(Real dt) override;
	Ogre::Vector3 chooseDirection(const Labyrinth& l) override;

protected:
	const std::string BODY_MESH = "cube.mesh";
	const std::string TOP_MESH = "sphere.mesh";
	const std::string HEAD_MESH = "DamagedHelmet.mesh";
	const std::string GUN_MESH = "fish.mesh";
	const std::string WHEEL_MESH = "Barrel.mesh";
	const std::string WHEEL_DECO_MESH = "ogrehead.mesh";
	const std::string WHEEL_DECO2_MESH = "Sword.mesh";
	const Vector3 TOP_SCALE = { 0.2, 0.15, 0.2 };
	const Vector3 HEAD_SCALE = { 60, 120, 60 };
	Vector3 GUN_SCALE = { 40, 30, 20 };

	Ogre::Timer* _timer;

	Ogre::SceneNode* _top;
	Ogre::SceneNode* _head;
	Ogre::SceneNode* _gun;
	std::vector<std::pair<Ogre::SceneNode*, int>> _wheelsSign;
	Vector3 _headBasePos;
	std::vector<Ogre::SceneNode*> _swords;

	void setup() override; 
	Ogre::SceneNode* createWheel(int id, bool left, bool front);
	Ogre::SceneNode* createPart(Ogre::SceneNode* parent, const std::string& mesh, const Vector3& scale);

	Vector3 calculateNodeBoxSize(Ogre::SceneNode* node);
};