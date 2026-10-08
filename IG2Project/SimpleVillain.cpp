#include "SimpleVillain.h"

SimpleVillain::SimpleVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp, int l) : Villain(initPos, node, sceneMng, sp, l) {
	setup();
}

void SimpleVillain::setup() {
	// Creates a new entity with the mesh and attach the entity
	entity = mSM->createEntity("ogrehead.mesh");
	mNode->attachObject(entity);
	this->setPosition(initialPosition);
}