#include "EmptyBlock.h"

EmptyBlock::EmptyBlock() : Block() {
	_canPassThrough = true;
}

EmptyBlock::EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng) {
	_canPassThrough = true;
}

EmptyBlock::EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
	_canPassThrough = true;
}