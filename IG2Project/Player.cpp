#include "Player.h"

Player::Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp, int l, int pts) : IG2Object(initPos, node, sceneMng, mesh), _speed(sp), _life(l), _points(pts) {

}

float Player::getSpeed() {
	return _speed;
}

void Player::setSpeed(float sp) {
	_speed = sp;
}

Vector3 Player::getNextDirVector() {
    Vector3 newDirVector = Vector3::ZERO;

    if (_direction == RIGHT)
        newDirVector = Vector3::UNIT_X;
    else if (_direction == LEFT)
        newDirVector = Vector3::NEGATIVE_UNIT_X;
    else if (_direction == DOWN)
        newDirVector = Vector3::UNIT_Z;
    else if (_direction == UP)
        newDirVector = Vector3::NEGATIVE_UNIT_Z;
    return newDirVector;
}

bool Player::isDirectionModified() {
    return getGridOrientation() != getNextDirVector();
}

Quaternion Player::getQuaternionForNewDirection() {
    Vector3 newDirVector = getNextDirVector();
    Quaternion q = getOrientation().getRotationTo(newDirVector);
    return q;
}

void Player::rotateToNewDirection() {
    rotate(getQuaternionForNewDirection());
}

bool Player::is180Turn() {
    // if parallel, is 180 turn
    if (getGridOrientation().crossProduct(getNextDirVector()) == Vector3::ZERO) {
        return true;
    }

    return false;
}

void Player::movePlayer(Real time) {
    move(getGridOrientation() * getSpeed() * time);
}