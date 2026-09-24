#include "Player.h"

Player::Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp, int l, int pts) : IG2Object(initPos, node, sceneMng, mesh), _speed(sp), _life(l), _points(pts), _currDir({ 0, 0, 0 }), _pendingDir(_currDir) {

}

float Player::getSpeed() {
	return _speed;
}

void Player::setSpeed(float sp) {
	_speed = sp;
}