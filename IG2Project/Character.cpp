#include "Character.h"

Character::Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp, int l) : IG2Object(initPos, node, sceneMng, mesh), _speed(sp), _life(l) {

}

Character::Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp, int l) : IG2Object(initPos, node, sceneMng), _speed(sp), _life(l) {

}

float Character::getSpeed() {
    return _speed;
}

void Character::setSpeed(float sp) {
    _speed = sp;
}

int Character::getLife() {
    return _life;
}

void Character::setLife(int l) {
    _life = l;
}


Vector3 Character::getNextDirVector() {
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

bool Character::isDirectionModified() {
    return getGridOrientation() != getNextDirVector();
}

Quaternion Character::getQuaternionForNewDirection() {
    Vector3 newDirVector = getNextDirVector();
    Quaternion q = getOrientation().getRotationTo(newDirVector);
    return q;
}

void Character::rotateToNewDirection() {
    rotate(getQuaternionForNewDirection());
}

bool Character::is180Turn() {
    // if parallel, is 180 turn
    if (getGridOrientation().crossProduct(getNextDirVector()) == Vector3::ZERO) {
        return true;
    }

    return false;
}

void Character::moveCharacter(Real time) {
    move(getGridOrientation() * getSpeed() * time);
}

void Character::update(Real time) {}