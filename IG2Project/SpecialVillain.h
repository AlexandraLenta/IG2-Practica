#pragma once
#include "Villain.h"
class SpecialVillain :
	public Villain
{
public:
	SpecialVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);


protected:
	void setup() override;

	Vector3 calculateNodeBoxSize(Ogre::SceneNode* node);
};