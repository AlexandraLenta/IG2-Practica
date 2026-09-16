#pragma once
#include "IG2Object.h"
class Labyrinth :
    public IG2Object
{
private:
    std::vector<IG2Object> _blocks;

public:
    const char WALL_BLOCK = 'x';
    const char EMPTY_BLOCK = 'o';
    const int BLOCK_SIZE = 10; // TO CHANGE

    /**
     * Constructor without parameters.
     */
    Labyrinth();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param fileName File with labyrinth configuration
     */
    Labyrinth(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string fileName);

private:
    void createLabyrinth(string fileName);
};