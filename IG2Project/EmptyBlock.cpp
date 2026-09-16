#include "EmptyBlock.h"

EmptyBlock::EmptyBlock() : IG2Object() {
}

EmptyBlock::EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {
}

EmptyBlock::EmptyBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh) {
}