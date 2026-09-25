#include "WallBlock.h"

WallBlock::WallBlock() : Block() {
	_canPassThrough = false;
}

WallBlock::WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng) {
	_canPassThrough = false;
}

WallBlock::WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
	_canPassThrough = false;
}