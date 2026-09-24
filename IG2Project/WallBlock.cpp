#include "WallBlock.h"

WallBlock::WallBlock() : Block() {
}

WallBlock::WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng) : Block(initPos, node, sceneMng) {
}

WallBlock::WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh) : Block(initPos, node, sceneMng, mesh) {
}