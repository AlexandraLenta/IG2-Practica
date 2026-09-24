#include "Player.h"

Player::Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp, int l, int pts) : IG2Object(initPos, node, sceneMng, mesh), speed(sp), life(l), points(pts), currDir({ 0, 0, 0 }), pendingDir(currDir), {

}