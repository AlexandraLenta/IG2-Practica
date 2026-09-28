#pragma once
#include "Block.h"

class BreakableBlock :
    public Block
{
public:
    /**
     * Constructor without parameters.
     */
    BreakableBlock();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    BreakableBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param mesh Mesh that is applied to this element.
     */
    BreakableBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
};