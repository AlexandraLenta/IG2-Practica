#pragma once
#include "IG2Object.h"
class WallBlock :
    public IG2Object
{
public:
    /**
     * Constructor without parameters.
     */
    WallBlock();

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     */
    WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

    /**
     * Constructor.
     * @param initPos Initial position for this element.
     * @param node Scene node for this element.
     * @param sceneMng Scene manager.
     * @param mesh Mesh that is applied to this element.
     */
    WallBlock(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, String mesh);
};

