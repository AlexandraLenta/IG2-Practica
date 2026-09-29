#include "BreakableBlock.h"

BreakableBlock::BreakableBlock() : Block() {
	_canPassThrough = false;
}

BreakableBlock::BreakableBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, MESH_NAME) {
	_canPassThrough = false;
}

BreakableBlock::BreakableBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
	_canPassThrough = false;
}

void BreakableBlock::breakBlock() {
	setVisible(false);
	_canPassThrough = true;
}