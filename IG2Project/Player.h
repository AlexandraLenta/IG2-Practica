#pragma once
#include "Character.h"

class Player :
    public Character
{
public:
    Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp = 10, int l = 3, int pts = 0);
    int getPoints();
    void setPoints(int p);

    Ogre::Vector3 chooseDirection() override;
private:
    int _points;
};