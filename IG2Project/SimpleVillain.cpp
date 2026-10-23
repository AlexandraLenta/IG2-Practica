#include "SimpleVillain.h"
#include "Block.h"
#include "Labyrinth.h"
#include <random>

SimpleVillain::SimpleVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp, int l) : Villain(initPos, node, sceneMng, sp, l) {
	setup();
}

void SimpleVillain::setup() {
	// Creates a new entity with the mesh and attach the entity
	entity = mSM->createEntity("ogrehead.mesh");
	mNode->attachObject(entity);
	this->setPosition(initialPosition);
	mNode->setScale(0.1, 0.1, 0.1);
}


Ogre::Vector3 SimpleVillain::chooseDirection() {
	std::vector<Vector2> possibleNextDirs;
	const Block* b;

	for (int i = 0; i < _directions.size(); i++) {
		b = _labyrinth->getBlock(Vector2{ getPosition().x, getPosition().z } + _directions[i] * _labyrinth->BLOCK_SIZE);

		if (b != nullptr && b->canPassThrough()) {
			possibleNextDirs.push_back(_directions[i]);
			//std::cout << "block at " << _directions[i].x << ' ' << _directions[i].y << " possible!\n";
		}
	}

	if (possibleNextDirs.empty())
		return getGridOrientation();

	Vector2 newDir = _directions[rand() % possibleNextDirs.size()];
	//std::cout << newDir << '\n';

	setNewDir(newDir);
	
	return { newDir.x, 0, newDir.y };
}