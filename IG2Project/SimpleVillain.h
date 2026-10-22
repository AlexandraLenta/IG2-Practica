#pragma once
#include "Villain.h"
class SimpleVillain :
    public Villain
{
public:
    SimpleVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);

    Ogre::Vector3 chooseDirection(const Labyrinth& l) override;
private:
    void setup() override;

    const std::vector<Vector2> _directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
};

