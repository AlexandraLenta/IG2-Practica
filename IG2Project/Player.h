#pragma once
#include "IG2Object.h"

class Player :
    public IG2Object
{
public:
    enum Directions {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    Player(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp = 10, int l = 3, int pts = 0);

    float getSpeed();
    void setSpeed(float sp);

    void setNewDir(Directions dir) {
        _direction = dir;
    }

    Ogre::Vector3 getNextDirVector();
    bool isDirectionModified();
    Ogre::Quaternion getQuaternionForNewDirection();
    void rotateToNewDirection();
    bool is180Turn();

    void movePlayer(Real time);

private:
    int _life;
    int _points;
    float _speed;

    Directions _direction = DOWN;
};

