#pragma once
#include "IG2Object.h"

class Player :
    public IG2Object
{
public:
    Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp = 10, int l = 3, int pts = 0);
private:
    int life;
    int points;
    float speed;
    Vector3 currDir;
    Vector3 pendingDir;
};

