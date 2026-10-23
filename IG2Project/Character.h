#pragma once

#include "IG2Object.h"

class Labyrinth;

class Character : public IG2Object
{
public:
    enum Directions {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, float sp = 10, int l = 3);
    Character(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh, float sp = 10, int l = 3);

    float getSpeed();
    void setSpeed(float sp);

    int getLife();
    void setLife(int l);

    /// <summary>
    /// Removes 1 from the character's life AND calls hurt or death callback.
    /// </summary>
    void hurt();

    void setNewDir(Directions dir) {
        _direction = dir;
    }

    void setNewDir(Vector2 dir);

    Ogre::Vector3 getNextDirVector();
    bool isDirectionModified();
    Ogre::Quaternion getQuaternionForNewDirection();
    void rotateToNewDirection();
    bool is180Turn();

    void moveCharacter(Real time);
    virtual void update(Real time);

    void setLabyrinth(Labyrinth* l) {
        _labyrinth = l;
    }

    virtual Ogre::Vector3 chooseDirection() = 0;

protected:
    int _life;
    float _speed;

    Directions _direction = DOWN;

    Labyrinth* _labyrinth = nullptr;
};