#pragma once
#include "IG2Object.h"
class Labyrinth :
    public IG2Object
{
private:
    std::vector<IG2Object*> _blocks;

public:
    static constexpr char WALL_BLOCK = 'x';
    static constexpr char EMPTY_BLOCK = 'o';
    static constexpr float BLOCK_SIZE = 20; 

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
    void createWallBlock(Vector3 pos);
    void createEmptyBlock(Vector3 pos);

    Vector3 getCubeScale(IG2Object* cube);
};