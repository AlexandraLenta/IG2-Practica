#pragma once
#include "Villain.h"
class SimpleVillain :
    public Villain
{
public:
    SimpleVillain(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);

private:
    void setup() override;
};

