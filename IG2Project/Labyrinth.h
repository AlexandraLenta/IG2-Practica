#pragma once
#include "IG2Object.h"

#include <vector>
#include <istream>

class Player;
class Block;
class IG2Project;

class Labyrinth :
    public IG2Object
{
private:
    std::vector<std::vector<Block*>> _blocks;

public:
    static constexpr char WALL_BLOCK = 'x';
    static constexpr char EMPTY_BLOCK = 'o';
    static constexpr char INVISIBLE_BLOCK = 'i';
    static constexpr char FAKE_BLOCK = 'f';
    static constexpr char BREAKABLE_BLOCK = 'b';
    static constexpr char HERO = 'h';
    static constexpr float BLOCK_SIZE = 15; 

    enum BlockType {
        EMPTY,
        WALL,
        INVISIBLE,
        FAKE,
        BREAKABLE
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
    Labyrinth(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, std::istream& input, IG2Project* ig2);

    ~Labyrinth();

    void updateLabyrinth(Real time);
    void movePlayer(Player* player, Real time);

private:
    int _numRows, _numCols; 
    Vector3 _labyrinthOrigin;


    /// <summary>
    /// Creates the labyrinth structure.
    /// </summary>
    /// <param name="input">The input stream to read the structure from.</param>
    /// <param name="ig2">Pointer to the project. Used to create player within scene.</param>
    void createLabyrinth(std::istream& input, IG2Project* ig2);

    /// <summary>
    /// Creates a block of a given size.
    /// </summary>
    /// <param name="pos">Position of block.</param>
    /// <param name="type">The type of the block.</param>
    /// <returns>Pointer to the block object.</returns>
    Block* createBlock(Vector3 pos, BlockType type);

    Vector3 getCubeResizeScale(IG2Object* cube);

    /// <summary>
    /// Get the block corresponding to given position.
    /// </summary>
    /// <param name="position">The position to check.</param>
    /// <returns>Pointer to the block object in given position.</returns>
    Block* getBlock(Vector3 position);

    /// <summary>
    /// Check if the player has reached the center of the block.
    /// </summary>
    /// <param name="difference">The difference between the center of the block and the player's position.</param>
    /// <param name="direction">The direction in which the player is heading.</param>
    /// <returns></returns>
    bool blockCenterReached(Vector3 difference, Vector3 direction);
};