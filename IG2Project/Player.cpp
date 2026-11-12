#include "Player.h"
#include "Labyrinth.h"
#include "Block.h"

Player::Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp, int l, int pts) : Character(initPos, node, sceneMng, mesh, sp, l), _points(pts) {
    _walkAnimStates.push_back(entity->getAnimationState("RunBase"));
    _walkAnimStates.push_back(entity->getAnimationState("RunTop"));

    for (auto* s : _walkAnimStates) {
        s->setEnabled(true);
    }
}

int Player::getPoints() {
    return _points;
}

void Player::setPoints(int p) {
    _points = p;
}

Vector3 Player::chooseDirection() {
    return getNextDirVector();
}

void Player::update(Real dt) {
    for (auto* s : _walkAnimStates) {
        s->addTime(dt);
    }
}