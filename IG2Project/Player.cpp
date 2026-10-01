#include "Player.h"

Player::Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp, int l, int pts) : Character(initPos, node, sceneMng, mesh, sp, l), _points(pts) {

}

int Player::getPoints() {
    return _points;
}

void Player::setPoints(int p) {
    _points = p;
}