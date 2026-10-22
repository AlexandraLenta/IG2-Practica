#include "Villain.h"
Villain::Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp, int l) : Character(initPos, node, sceneMng, sp, l) {
}

void Villain::update(Real time) {
	// TODO: update logic
}

Vector3 Villain::chooseDirection(const Labyrinth& l) {
	return Vector3::UNIT_X;
}