#include "EmptyBlock.h"

EmptyBlock::EmptyBlock() : Block() {
}

EmptyBlock::EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng) {
}

EmptyBlock::EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
}