#pragma once
#include "IG2Object.h"

class Player :
    public IG2Object
{
public:
    Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp = 10, int l = 3, int pts = 0);

    float getSpeed();
    void setSpeed(float sp);

private:
    int _life;
    int _points;
    float _speed;
    Vector3 _currDir;
    Vector3 _pendingDir;
};

