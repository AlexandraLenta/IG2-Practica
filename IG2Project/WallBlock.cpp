#include "WallBlock.h"

WallBlock::WallBlock() : IG2Object() {
}

WallBlock::WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : IG2Object(initPos, node, sceneMng) {
}

WallBlock::WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : IG2Object(initPos, node, sceneMng, mesh) {
}