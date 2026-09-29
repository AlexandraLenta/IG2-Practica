#include "InvisibleBlock.h"

InvisibleBlock::InvisibleBlock() : Block() {
	init();
}

InvisibleBlock::InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, MESH_NAME) {
	init();
}

InvisibleBlock::InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
	init();
}

void InvisibleBlock::init() {
	_canPassThrough = false;
	setVisible(_isVisible);
	_timer = Ogre::Timer::Timer();
}

void InvisibleBlock::update(Real time) {
	if (_timer.getMilliseconds() >= INVISIBLE_TIMER * 1000) {
		_timer.reset();
		_isVisible = !_isVisible;
		setVisible(_isVisible);
	}
}