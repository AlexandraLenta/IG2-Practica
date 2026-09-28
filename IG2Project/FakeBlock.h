#pragma once
#include "Block.h"
class FakeBlock :
    public Block
{
public:
    /**
     * Constructor without parameters.
     */
    FakeBlock();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    FakeBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param mesh Mesh that is applied to this element.
     */
    FakeBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
};

