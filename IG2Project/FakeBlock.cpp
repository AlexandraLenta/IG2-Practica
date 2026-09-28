#include "FakeBlock.h"

FakeBlock::FakeBlock() : Block() {
	_canPassThrough = true;
}

FakeBlock::FakeBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng, MESH_NAME) {
	_canPassThrough = true;
}

FakeBlock::FakeBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
	_canPassThrough = true;
}