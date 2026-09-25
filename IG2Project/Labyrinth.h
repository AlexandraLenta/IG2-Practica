#pragma once
#include "IG2Object.h"

class Player;
class Block;

class Labyrinth :
    public IG2Object
{
private:
    std::vector<std::vector<Block*>> _blocks;

public:
    static constexpr char WALL_BLOCK = 'x';
    static constexpr char EMPTY_BLOCK = 'o';
    static constexpr float BLOCK_SIZE = 15; 

    enum BlockType {
        EMPTY,
        WALL
    };

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

    ~Labyrinth();

    void movePlayer(Player* player, Real time);

private:
    int _numRows, _numCols;

    void createLabyrinth(string fileName);
    Block* createBlock(Vector3 pos, BlockType type);

    Vector3 getCubeResizeScale(IG2Object* cube);

    Block* getBlock(Vector3 position);
    void stepForward(Player* player, Real time);
    bool blockCenterReached(Vector3 difference, Vector3 direction);

    Vector3 getPositionRelativeToLabyrinth(Vector3 pos);
};