#include "Block.h"
Block::Block() : IG2Object() {
}

Block::Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {
}

Block::Block(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh) {
}

bool Block::canPassThrough() {
	return _canPassThrough;
}