#include "InvisibleBlock.h"

InvisibleBlock::InvisibleBlock() : Block() {
	_canPassThrough = false;
	setVisible(_isVisible);
}

InvisibleBlock::InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng) {
	_canPassThrough = false;
	setVisible(_isVisible);
}

InvisibleBlock::InvisibleBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
	_canPassThrough = false;
	setVisible(_isVisible);
}

void InvisibleBlock::update(Real time) {
	_timer += time;
	if (_timer >= INVISIBLE_TIMER) {
		_timer = 0.0f;
		_isVisible != _isVisible;
		setVisible(_isVisible);
	}
}