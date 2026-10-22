#pragma once
#include "Character.h"

class Player;

class Villain :
    public Character
{
public:
    Villain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);

    void update(Real time) override;

    Vector3 chooseDirection(const Labyrinth& l) override;

protected:
    virtual void setup() = 0;

};